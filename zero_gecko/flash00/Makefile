
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn -mcpu=cortex-m0
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : flash00.bin flash00.sram.bin

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

flash00.o : flash00.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c flash00.c -o flash00.o

flash00.bin : flash.ld flash.o 
	$(ARMGNU)-ld -o flash00.elf -T flash.ld flash.o 
	$(ARMGNU)-objdump -D flash00.elf > flash00.list
	$(ARMGNU)-objcopy flash00.elf flash00.bin -O binary

flash00.sram.bin : sram.ld sram.o flash00.o
	$(ARMGNU)-ld -o flash00.sram.elf -T sram.ld sram.o flash00.o
	$(ARMGNU)-objdump -D flash00.sram.elf > flash00.sram.list
	$(ARMGNU)-objcopy flash00.sram.elf flash00.sram.hex -O ihex
	$(ARMGNU)-objcopy flash00.sram.elf flash00.sram.bin -O binary

