
void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
void dummy ( unsigned int );

#define CMU_BASE        0x400C8000

#define GPIO_BASE       0x40006000

//#define GPIO_PA_CTRL    (GPIO_BASE+0x00+0x000)
//#define GPIO_PA_MODEL   (GPIO_BASE+0x00+0x004)
//#define GPIO_PA_DOUTSET (GPIO_BASE+0x00+0x010)
//#define GPIO_PA_DOUTCLR (GPIO_BASE+0x00+0x014)
//#define GPIO_PA_DOUTTGL (GPIO_BASE+0x00+0x018)

#define GPIO_PC_CTRL    (GPIO_BASE+0x48+0x000)
#define GPIO_PC_MODEL   (GPIO_BASE+0x48+0x004)
#define GPIO_PC_DOUTSET (GPIO_BASE+0x48+0x010)
#define GPIO_PC_DOUTCLR (GPIO_BASE+0x48+0x014)
#define GPIO_PC_DOUTTGL (GPIO_BASE+0x48+0x018)

#define USART1_BASE         0x4000C400
#define USART1_CTRL        (USART1_BASE + 0x000)
#define USART1_FRAME       (USART1_BASE + 0x004)
#define USART1_CMD         (USART1_BASE + 0x00C)
#define USART1_STATUS      (USART1_BASE + 0x010)
#define USART1_CLOCKDIV    (USART1_BASE + 0x014)
#define USART1_TXDATA      (USART1_BASE + 0x034)
#define USART1_ROUTE       (USART1_BASE + 0x054)

void notmain ( void )
{
    unsigned int ra;

    ra=GET32(CMU_BASE+0x44);
    ra|=1<<3; //enable USART1
    ra|=1<<7; //enable GPIO
    PUT32(CMU_BASE+0x44,ra);

    ra=GET32(GPIO_PC_MODEL);
    ra&=~(0xF<<(0<<2)); //PC0
    ra|= (0x4<<(0<<2)); //PC0
    PUT32(GPIO_PC_MODEL,ra);

    PUT32(USART1_CTRL,0x00000000);
    //PUT32(USART1_FRAME,(1<<12)|(0<<8)|(5<<0));
    PUT32(USART1_CLOCKDIV,(1688<<6));
    PUT32(USART1_ROUTE,(0<<8)|(1<<1)|(0<<0));
    PUT32(USART1_CMD,(0<<4)|(1<<2));
}

    while(1)
    {
        PUT32(USART1_TXDATA,0x55);
        for(ra=0;ra<0x80000;ra++) dummy(ra);
    }
}
