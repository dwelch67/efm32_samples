
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn -mcpu=cortex-m0
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : uart01.bin uart01.sram.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.bc
	rm -f *.opt.s
	rm -f *.norm.s
	rm -f *.hex

#---------------------------------

flash.o : flash.s
	$(ARMGNU)-as $(AOPS) flash.s -o flash.o

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

uart01.o : uart01.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c uart01.c -o uart01.o

uart01.bin : flash.ld flash.o uart01.o
	$(ARMGNU)-ld -o uart01.elf -T flash.ld flash.o uart01.o
	$(ARMGNU)-objdump -D uart01.elf > uart01.list
	$(ARMGNU)-objcopy uart01.elf uart01.bin -O binary

uart01.sram.bin : sram.ld sram.o uart01.o
	$(ARMGNU)-ld -o uart01.sram.elf -T sram.ld sram.o uart01.o
	$(ARMGNU)-objdump -D uart01.sram.elf > uart01.sram.list
	$(ARMGNU)-objcopy uart01.sram.elf uart01.sram.hex -O ihex
	$(ARMGNU)-objcopy uart01.sram.elf uart01.sram.bin -O binary

