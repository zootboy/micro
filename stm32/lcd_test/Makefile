# STM32F cross-compiling makefile
#

# First thing first, settings for the programmer.
PROGDEV = /dev/ttyUSB0
PROGLOADER = stm32loader.py -ewv -p $(PROGDEV) stm.bin

ifeq ($(PREFIX),)
  PREFIX=arm-none-eabi-
endif
# Directory where the GCC cross-compiler lives. 
CCHOME = /usr
#ifeq ($(CCHOME),)
#  CCHOME = /home/hfs2/devtool/cs/arm-2011.09
#endif
ifeq ($(STMHOME),)
  STMHOME = STM32F10x_StdPeriph_Lib_V3.5.0/Libraries
endif
ifeq ($(STM_FAMILY),)
  STM_FAMILY=STM32F10X_HD
endif
DEFS = -D $(STM_FAMILY)
ifeq ($(CFLAGS),)
  CFLAGS = -mcpu=cortex-m3 -march=armv7-m -mfloat-abi=soft -mthumb -ggdb
endif
# define IDE_INCDIRS via IDE or environment to avoid including these
ifeq ($(IDE_INCDIRS),)
  ID1 = $(CCHOME)/arm-none-eabi/include
  ID2 = $(CCHOME)/lib/gcc/arm-none-eabi/4.6.3/include
  ID3 = $(STMHOME)/CMSIS/Include
  ID4 = $(STMHOME)/CMSIS/Device/ST/STM32F10x/Include
  ID5 = $(STMHOME)/CMSIS/CM3/DeviceSupport/ST/STM32F10x
  ID6 = $(STMHOME)/CMSIS/CM3/CoreSupport
  ID7 = $(STMHOME)/STM32F10x_StdPeriph_Driver/inc
  INCDIRS = -I $(ID1) -I $(ID2) -I $(ID3) -I $(ID4) -I $(ID5) -I $(ID6) -I $(ID7)
endif
# define IDE_LIBDIRS via IDE or environment to avoid including these
ifeq ($(IDE_LIBDIRS),)
  # CodeSourcery 4.6.1 lib directories
  LD1 = $(CCHOME)/arm-none-eabi/lib/thumb2
  LD2 = $(CCHOME)/lib/gcc/arm-none-eabi/4.6.3/thumb2
  # Linaro 4.6.2 lib directories
  # LD1 = $(CCHOME)/arm-none-eabi/lib/armv7-m
  # LD2 = $(CCHOME)/lib/gcc/arm-none-eabi/4.6.2/armv7-m
  LDFLAGS = -L $(LD1) -L $(LD2)
endif

CCFLAGS = $(CFLAGS) $(DEFS) $(INCDIRS)

as = $(CCHOME)/bin/$(PREFIX)as
ld = $(CCHOME)/bin/$(PREFIX)ld
cc = $(CCHOME)/bin/$(PREFIX)gcc
cp = $(CCHOME)/bin/$(PREFIX)objcopy
dump = $(CCHOME)/bin/$(PREFIX)objdump


all : stm.o
	$(cp) -O binary stm.o stm.bin
	$(cp) -O ihex stm.o stm.hex
	$(dump) -dS stm.o > stm.disassembly

program : all
	$(PROGLOADER)

stm.o : main.o sysinit.o crt0.o lcd.o uart.o circular_buf.o stm.ld
	$(ld) $(LDFLAGS) -Map map.txt -T stm.ld -o stm.o crt0.o sysinit.o main.o lcd.o uart.o circular_buf.o -lm -lc -lgcc

crt0.o : startup_stm32f10x_hd.s
	$(as) -o crt0.o startup_stm32f10x_hd.s

sysinit.o : sysinit.c
	$(cc) $(CCFLAGS) -c sysinit.c

main.o: main.c
	$(cc) $(CCFLAGS) -c main.c

lcd.o: lcd.c
	$(cc) $(CCFLAGS) -c lcd.c

uart.o: uart.c
	$(cc) $(CCFLAGS) -c uart.c

circular_buf.o: circular_buf.c
	$(cc) $(CCFLAGS) -c circular_buf.c

clean : 
	#rm crt0.o main.o stm.o sysinit.o stm.bin stm.hex stm.txt map.txt
	rm -f *.o stm.bin stm.hex stm.disassembly stm.map
