
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn -mcpu=cortex-m0
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : uart00.bin uart00.sram.bin

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

uart00.o : uart00.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c uart00.c -o uart00.o

uart00.bin : flash.ld flash.o uart00.o
	$(ARMGNU)-ld -o uart00.elf -T flash.ld flash.o uart00.o
	$(ARMGNU)-objdump -D uart00.elf > uart00.list
	$(ARMGNU)-objcopy uart00.elf uart00.bin -O binary

uart00.sram.bin : sram.ld sram.o uart00.o
	$(ARMGNU)-ld -o uart00.sram.elf -T sram.ld sram.o uart00.o
	$(ARMGNU)-objdump -D uart00.sram.elf > uart00.sram.list
	$(ARMGNU)-objcopy uart00.sram.elf uart00.sram.hex -O ihex
	$(ARMGNU)-objcopy uart00.sram.elf uart00.sram.bin -O binary

