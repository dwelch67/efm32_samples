
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define CMU_BASE        0x400C8000

#define GPIO_BASE       0x40006000
#define GPIO_PA_CTRL    (GPIO_BASE+0x000)
#define GPIO_PA_MODEL   (GPIO_BASE+0x004)
#define GPIO_PA_DOUTSET (GPIO_BASE+0x010)
#define GPIO_PA_DOUTCLR (GPIO_BASE+0x014)
#define GPIO_PA_DOUTTGL (GPIO_BASE+0x018)

#define MSC_BASE        0x400C0000
#define MSC_WRITECTRL   (MSC_BASE+0x008)
#define MSC_WRITECMD    (MSC_BASE+0x00C)
#define MSC_ADDRB       (MSC_BASE+0x010)
#define MSC_WDATA       (MSC_BASE+0x018)
#define MSC_STATUS      (MSC_BASE+0x01C)

#define MSC_WRITECMD_LADDRIM    (1<<0)
#define MSC_WRITECMD_ERASEPAGE  (1<<1)
#define MSC_WRITECMD_WRITEONCE  (1<<3)

//00000000 <_start>:
//   0: 20001000    andcs   r1, r0, r0
//   4: 00000011    andeq   r0, r0, r1, lsl r0
//   8: 00000011    andeq   r0, r0, r1, lsl r0
//   c: 00000011    andeq   r0, r0, r1, lsl r0
//
//00000010 <hang>:
//  10: e7fe        b.n 10 <hang>

#define LOOP_SIZE 5
static const unsigned int loop[LOOP_SIZE]=
{
0x20001000,
0x00000011,
0x00000011,
0x00000011,
0xe7fee7fe
};

void notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    PUT32(MSC_WRITECTRL,0x01);
    PUT32(MSC_ADDRB,0x00000000);
    PUT32(MSC_WRITECMD,MSC_WRITECMD_LADDRIM);
    PUT32(MSC_WRITECMD,MSC_WRITECMD_ERASEPAGE);
    while(1)
    {
        ra=GET32(MSC_STATUS);
        if((ra&1)==0) break;
    }
    PUT32(MSC_ADDRB,0x00000000);
    PUT32(MSC_WRITECMD,MSC_WRITECMD_LADDRIM);
    for(rb=0;rb<LOOP_SIZE;rb++)
    {
        PUT32(MSC_WDATA,loop[rb]);
        PUT32(MSC_WRITECMD,MSC_WRITECMD_WRITEONCE);
        while(1)
        {
            ra=GET32(MSC_STATUS);
            if((ra&1)==0) break;
        }
    }
    PUT32(MSC_WRITECTRL,0x00);

    // blink led to indicate finished

    ra=GET32(CMU_BASE+0x44);
    ra|=1<<7; //enable GPIO
    PUT32(CMU_BASE+0x44,ra);

    ra=GET32(GPIO_PA_MODEL);
    ra&=~(0xF<<(0<<2)); //PA0
    ra|= (0x4<<(0<<2)); //PA0
    PUT32(GPIO_PA_MODEL,ra);

    PUT32(GPIO_PA_DOUTSET,1<<0);
    while(1)
    {
        PUT32(GPIO_PA_DOUTTGL,1<<0);
        for(ra=0;ra<0x40000;ra++) dummy(ra);
    }
}
