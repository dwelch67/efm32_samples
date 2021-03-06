
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

#define STK_CSR 0xE000E010
#define STK_RVR 0xE000E014
#define STK_CVR 0xE000E018
#define STK_MASK 0x00FFFFFF

int delay ( unsigned int n )
{
    unsigned int ra;

    while(n--)
    {
        while(1)
        {
            ra=GET32(STK_CSR);
            if(ra&(1<<16)) break;
        }
    }
    return(0);
}

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

    PUT32(STK_CSR,4);
    PUT32(STK_RVR,1000000-1);
    PUT32(STK_CVR,0x00000000);
    PUT32(STK_CSR,5);

    while(1)
    {
        PUT32(GPIO_PA_DOUTTGL,1<<0);
        delay(100);
    }
}
