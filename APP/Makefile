
SRC:= $(wildcard *.c) 
SRC+= $(wildcard ../*/*/*.c)
PROJECT_NAME=SPI_Slave
OBJ=$(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

CC=avr-gcc.exe
OBJCPY=avr-objcopy.exe
FLASHER=avrdude
SIZE=avr-size.exe
ARCH=avr
MCU=atmega32
FRQ=1000000UL
# use gdwarf-2 in case of protues
CFLAGS=-mmcu=$(MCU) -Os -DF_CPU=$(FRQ) -Wall -gdwarf-2 -g 
OBJCPY_FLAGS=-j .text -j .data -O ihex 
FFLAGS=-c usbasp -p m32 -B 0.5 -U Flash:w:${PROJECT_NAME}.hex:a 
SIZE_FLAGS=--format=$(ARCH) --mcu=$(MCU)

all : $(PROJECT_NAME).hex

-include $(DEP)

$(PROJECT_NAME).hex : $(PROJECT_NAME).elf
	@$(OBJCPY) $(OBJCPY_FLAGS) $< $@
	@$(SIZE) $(SIZE_FLAGS) $(PROJECT_NAME).elf

$(PROJECT_NAME).elf: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ 

flash : $(PROJECT_NAME).hex 
	@$(FLASHER) $(FFLAGS)
	@echo flashing done

clean :
	@rm $(PROJECT_NAME).hex $(PROJECT_NAME).elf $(OBJ) $(DEP)
	@echo every thing is clean
