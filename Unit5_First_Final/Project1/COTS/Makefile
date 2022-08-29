CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -mthumb
INCS = -I . -gdwarf-2
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
As = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
proj_name = Pressure_Detection_System

all: $(proj_name).bin $(proj_name).hex
	@echo "<<<<< Build is Done >>>>>"

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(proj_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld -Map=Mapfile.map $(LIBS) $(OBJ) $(AsOBJ) -o $@

$(proj_name).bin: $(proj_name).elf
	$(CC)objcopy.exe -O binary $< $@

$(proj_name).hex: $(proj_name).elf  
	$(CC)objcopy.exe -O  ihex $< $@

clean_all:
	rm *.o *.elf *.bin *.hex
	@echo "<<<<< Everything Is Cleaned >>>>>"

clean:
	rm *.elf *.bin *.hex