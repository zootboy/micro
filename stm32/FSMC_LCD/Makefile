# STM32F cross-compiling makefile
#

# Directory for build files.
BUILDDIR = build

# First thing first, settings for the programmer.
PROGDEV = /dev/ttyUSB0
PROGLOADER = stm32loader.py -ewv -p $(PROGDEV) $(BUILDDIR)/stm.bin

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
  ID8 = inc
  INCDIRS = -I $(ID1) -I $(ID2) -I $(ID3) -I $(ID4) -I $(ID5) -I $(ID6) -I $(ID7) -I $(ID8)
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

# Find all source files.
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all : $(BUILDDIR)/stm.o
	$(cp) -O binary $(BUILDDIR)/stm.o $(BUILDDIR)/stm.bin
	$(cp) -O ihex $(BUILDDIR)/stm.o $(BUILDDIR)/stm.hex
	$(dump) -dS $(BUILDDIR)/stm.o > $(BUILDDIR)/stm.disassembly

program : all
	$(PROGLOADER)

$(BUILDDIR)/stm.o : $(OBJ) $(BUILDDIR)/crt0.o stm.ld
	$(ld) $(LDFLAGS) -Map $(BUILDDIR)/map.txt -T stm.ld -o $(BUILDDIR)/stm.o $(BUILDDIR)/crt0.o $(OBJ) -lm -lc -lgcc

.c.o :
	$(cc) $(CCFLAGS) -c $< -o $@

$(BUILDDIR)/crt0.o : startup_stm32f10x_hd.s
	$(as) -o $(BUILDDIR)/crt0.o startup_stm32f10x_hd.s

clean : 
	#rm crt0.o main.o stm.o sysinit.o stm.bin stm.hex stm.txt map.txt
	rm -f $(BUILDDIR)/*
