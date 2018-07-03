
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn -mcpu=cortex-m0
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : flash01.sram.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.bc
	rm -f *.opt.s
	rm -f *.norm.s
	rm -f *.hex
	rm -f bintoc

#---------------------------------

bintoc : bintoc.c
	gcc bintoc.c -o bintoc

flash.h : flash-bin bintoc
	./bintoc flash-bin

sram.o : sram.s
	$(ARMGNU)-as $(AOPS) sram.s -o sram.o

flash01.o : flash01.c flash.h
	$(ARMGNU)-gcc $(COPS) -mthumb -c flash01.c -o flash01.o

flash01.sram.bin : sram.ld sram.o flash01.o
	$(ARMGNU)-ld -o flash01.sram.elf -T sram.ld sram.o flash01.o
	$(ARMGNU)-objdump -D flash01.sram.elf > flash01.sram.list
	$(ARMGNU)-objcopy flash01.sram.elf flash01.sram.hex -O ihex
	$(ARMGNU)-objcopy flash01.sram.elf flash01.sram.bin -O binary



