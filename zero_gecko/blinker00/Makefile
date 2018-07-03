
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn -mcpu=cortex-m0
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : blinker00.bin blinker00.sram.bin

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

blinker00.o : blinker00.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c blinker00.c -o blinker00.o

blinker00.bin : flash.ld flash.o blinker00.o
	$(ARMGNU)-ld -o blinker00.elf -T flash.ld flash.o blinker00.o
	$(ARMGNU)-objdump -D blinker00.elf > blinker00.list
	$(ARMGNU)-objcopy blinker00.elf blinker00.bin -O binary

blinker00.sram.bin : sram.ld sram.o blinker00.o
	$(ARMGNU)-ld -o blinker00.sram.elf -T sram.ld sram.o blinker00.o
	$(ARMGNU)-objdump -D blinker00.sram.elf > blinker00.sram.list
	$(ARMGNU)-objcopy blinker00.sram.elf blinker00.sram.hex -O ihex
	$(ARMGNU)-objcopy blinker00.sram.elf blinker00.sram.bin -O binary

