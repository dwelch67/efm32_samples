
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
    while(1)
    {
        PUT32(GPIO_PA_DOUTTGL,1<<0);
        for(ra=0;ra<0x40000;ra++) dummy(ra);
    }
}
