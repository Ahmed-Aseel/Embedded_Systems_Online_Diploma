CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -mthumb
INCS = -I . -gdwarf-2 -g
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
proj_name = main

all: $(proj_name).bin
	@echo "<<<<< Build is Done >>>>>"

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(proj_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T cortexm4_linker_script.ld -Map=Mapfile.map $(LIBS) $(OBJ) $(AsOBJ) -o $@
	cp $(proj_name).elf $(proj_name).axf

$(proj_name).bin: $(proj_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin
	@echo "<<<<< Everything Clean >>>>>"

clean:
	rm *.elf *.bin