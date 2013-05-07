/*
Common part of the linker scripts for STR71x devices in FLASH mode
(that is, the FLASH is seen at 0)
Copyright RAISONANCE 2005
You can use, modify and distribute this file freely, but without any waranty.

The following files combined here (with some mods)
  STM32F103_512K_64K_DEF.ld
  sections_FLASH.ld
  STM32F10x_COMMON.ld

  basically, everything that referred to external memory was chopped out
  -hfs 2010-06-27
	--- Modified by Sean Greenslade for HD stm32 ---
 */

/* Memory Spaces Definitions */
/*MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 128K
}
*/
MEMORY
{
  RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 48K
  FLASH (rx) : ORIGIN = 0x8000000, LENGTH = 256K
}

/*_estack = 0x20005000;  higher address of the user mode stack */
_estack = 0x2000C000; /* higher address of the user mode stack */

/* Sections Definitions */
SECTIONS
{
    /* for Cortex devices, the beginning of the startup code is stored in the .isr_vector section, which goes to FLASH */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))            /* Startup code */
        . = ALIGN(4);
    } >FLASH     
    /* the program code is stored in the .text section, which goes to Flash */
    .text :
    {
        . = ALIGN(4);	    
        *(.text)                   /* remaining code */
        *(.text.*)                   /* remaining code */
        *(.rodata)                 /* read-only data (constants) */
        *(.rodata*)
        *(.glue_7)
        *(.glue_7t)
        . = ALIGN(4);
   	 _etext = .;
        /* This is used by the startup in order to initialize the .data section */
   	 _sidata = _etext;
    } >FLASH

    /* This is the initialized data section
    The program executes knowing that the data is in the RAM
    but the loader puts the initial values in the FLASH (inidata).
    It is one task of the startup to copy the initial values from FLASH to RAM. */
    .data  : AT ( _sidata )
    {
	    . = ALIGN(4);
        _sdata = . ; /* used by the startup to initialize the .data section */        
        *(.data)
        *(.data.*)
	    . = ALIGN(4);
   	 _edata = . ; /* used by the startup to initialize the .data section */
    } >RAM    
    /* This is the uninitialized data section */
    .bss :
    {
	    . = ALIGN(4);
        _sbss = .; /* used by the startup to initialize the .bss secion */        
        *(.bss)
        *(COMMON)        
	    . = ALIGN(4);
   	 _ebss = . ; /* used by the startup to initialize the .bss secion */
    } >RAM
}

