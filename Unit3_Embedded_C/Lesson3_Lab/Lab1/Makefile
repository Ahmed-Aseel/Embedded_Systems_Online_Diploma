CC = arm-none-eabi-
CFLAGS = -g -mcpu=arm926ej-s
INCS = -I .
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
proj_name = main

all: $(proj_name).bin
	@echo "<<<<< Build is Done >>>>>"

startup.o: startup.s
	$(CC)as.exe -c $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(proj_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld -Map=Mapfile.map $(LIBS) $(OBJ) $(AsOBJ) -o $@

$(proj_name).bin: $(proj_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin
	@echo "<<<<< Everything Clean >>>>>"

clean:
	rm *.elf *.bin