
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

#define TIMER0_BASE     0x40010000
#define TIMER0_CTRL     (TIMER0_BASE+0x000)
#define TIMER0_CMD      (TIMER0_BASE+0x004)
#define TIMER0_STATUS   (TIMER0_BASE+0x008)
#define TIMER0_IF       (TIMER0_BASE+0x010)
#define TIMER0_IFC      (TIMER0_BASE+0x018)
#define TIMER0_TOP      (TIMER0_BASE+0x01C)
#define TIMER0_CNT      (TIMER0_BASE+0x024)

void notmain ( void )
{
    unsigned int ra;

    ra=GET32(CMU_BASE+0x44);
    ra|=1<<7; //enable GPIO
    PUT32(CMU_BASE+0x44,ra);

    ra=GET32(GPIO_PA_MODEL);
    ra&=~(0xF<<(0<<2)); //PA0
    ra|= (0x4<<(0<<2)); //PA0
    PUT32(GPIO_PA_MODEL,ra);
    PUT32(GPIO_PA_DOUTSET,1<<0);

    ra=GET32(CMU_BASE+0x44);
    ra|=1<<0; //enable TIMER0
    PUT32(CMU_BASE+0x44,ra);

    //PUT32(TIMER0_CMD,0);
    PUT32(TIMER0_CTRL,0x08000000);
    //PUT32(TIMER0_TOP,10000-1);
    PUT32(TIMER0_CMD,1);

    while(1)
    {
        PUT32(GPIO_PA_DOUTTGL,1<<0);
        while(1)
        {
            ra=GET32(TIMER0_IF);
            if(ra&0x00000001) break;
        }
        PUT32(TIMER0_IFC,0x00000001);
    }
}
