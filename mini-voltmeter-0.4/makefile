# makefile, written by guido socher
MCU=atmega8
CC=avr-gcc
OBJCOPY=avr-objcopy
DUDECPUTYPE=m8
LOADCMD=avrdude
LOADARG=-p $(DUDECPUTYPE) -c stk500v2 -e -U flash:w:

# optimize for size:
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues
#-------------------
.PHONY: test1 all counter
all: main.hex test1.hex counter.hex
#-------------------
help: 
	@echo "Usage: make all|rdfuse|fuse"
	@echo "or to load the different programs:"
	@echo "Usage: make load|load_test1|load_counter"
	@echo "Do not forget to run once make fuse to set the fuse bytes"
#-------------------
main.hex : main.out 
	$(OBJCOPY) -R .eeprom -O ihex main.out main.hex 
	avr-size main.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
main.out : main.o analog.o 
	$(CC) $(CFLAGS) -o main.out -Wl,-Map,main.map main.o analog.o 
main.o : main.c analog.h 
	$(CC) $(CFLAGS) -Os -c main.c
#------------------
analog.o : analog.c analog.h 
	$(CC) $(CFLAGS) -Os -c analog.c
#------------------
# a counter
counter: counter.hex
#
counter.o : counter.c  
	$(CC) $(CFLAGS) -Os -c counter.c
counter.hex : counter.o 
	$(CC) $(CFLAGS) -o counter.out -Wl,-Map,counter.map counter.o 
	$(OBJCOPY) -R .eeprom -O ihex counter.out counter.hex 
	avr-size counter.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
load_counter: counter.hex
	$(LOADCMD) $(LOADARG)counter.hex
#------------------
# hardware test, led only:
test1: test1.hex
#
test1.o : test1.c  
	$(CC) $(CFLAGS) -Os -c test1.c
test1.hex : test1.o 
	$(CC) $(CFLAGS) -o test1.out -Wl,-Map,test1.map test1.o 
	$(OBJCOPY) -R .eeprom -O ihex test1.out test1.hex 
	avr-size test1.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
load_test1: test1.hex
	$(LOADCMD) $(LOADARG)test1.hex
#-------------------
load: main.hex
	$(LOADCMD) $(LOADARG)main.hex
# here is a pre-compiled version in case you have trouble with
# your development environment. It is just to get started.
load_pre: main_pre.hex
	$(LOADCMD) $(LOADARG)main_pre.hex
#
load_counter_pre: counter_pre.hex
	$(LOADCMD) $(LOADARG)counter_pre.hex
#
pre: main.hex
	cp main.hex main_pre.hex
	cp counter.hex counter_pre.hex
#-------------------
# fuse byte settings:
#  Atmel AVR ATmega8 
#  Fuse Low Byte      = 0xe1 (1MHz internal), 0xe3 (4MHz internal), 0xe4 (8MHz internal)
#  Fuse High Byte     = 0xd9 
#  Factory default is 0xe1 for low byte and 0xd9 for high byte
# Check this with make rdfuses
rdfuse:
	avrdude -p $(DUDECPUTYPE) -c stk500v2 -v -q
# use internal RC oscillator 8 Mhz
fuse:
	avrdude -p m8 -c stk500v2 -u -v -U lfuse:w:0xe4:m
#-------------------
clean:
	rm -f *.o *.map *.out test*.hex main.hex counter.hex
#-------------------
