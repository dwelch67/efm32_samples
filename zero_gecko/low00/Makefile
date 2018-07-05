
ARMGNU = arm-none-eabi
#ARMGNU = arm-linux-gnueabi

AOPS = --warn -mcpu=cortex-m0
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m0

all : low00.bin low00.sram.bin

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

low00.o : low00.c
	$(ARMGNU)-gcc $(COPS) -mthumb -c low00.c -o low00.o

low00.bin : flash.ld flash.o low00.o
	$(ARMGNU)-ld -o low00.elf -T flash.ld flash.o low00.o
	$(ARMGNU)-objdump -D low00.elf > low00.list
	$(ARMGNU)-objcopy low00.elf low00.bin -O binary

low00.sram.bin : sram.ld sram.o low00.o
	$(ARMGNU)-ld -o low00.sram.elf -T sram.ld sram.o low00.o
	$(ARMGNU)-objdump -D low00.sram.elf > low00.sram.list
	$(ARMGNU)-objcopy low00.sram.elf low00.sram.hex -O ihex
	$(ARMGNU)-objcopy low00.sram.elf low00.sram.bin -O binary

