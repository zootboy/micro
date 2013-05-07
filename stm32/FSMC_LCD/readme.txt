/**
  @page FSMC_LCD AN2790 FSMC_LCD Readme file
  
  @verbatim
  ******************** (C) COPYRIGHT 2009 STMicroelectronics *******************
  * @file     FSMC_LCD/readme.txt 
  * @author   MCD Application Team
  * @version  V2.0.0
  * @date     04/27/2009
  * @brief    Description of the AN2790 "TFT LCD interfacing with the High-density
  *           STM32F10xxx FSMC" .
  ******************************************************************************
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
   @endverbatim

@par Example Description 

This AN describes a firmware TFT LCD interfacing with the High Density STM32F10xxx 
FSMC peripheral. The main purpose of this firmware package is to provide resources 
facilitating the development of an application using the LCD on FSMC peripheral.

The firmware interface is composed of library source files developed in order to
support LCD features, an application demo is also provided.

@par Directory contents 

- inc 
   - FSMC_LCD/inc/fonts.h           LCD fonts size definition
   - FSMC_LCD/inc/stm32f10x_conf.h  Library Configuration file
   - FSMC_LCD/inc/stm32f10x_it.h    Interrupt handlers header file
   - FSMC_LCD/inc/stm3210e_lcd.h    LCD Header file
   - FSMC_LCD/inc/fsmc_nand.h       FSMC NAND driver Header file
   - FSMC_LCD/inc/fsmc_nor.h        FSMC NOR driver Header file
   - FSMC_LCD/inc/fsmc_sram.h       FSMC SRAM driver Header file
   - FSMC_LCD/inc/main.h            Main Header file
   - FSMC_LCD/inc/menu.h            Menu Navigation Header file
   - FSMC_LCD/inc/sdcard.h          SD Card driver Header file      

- src 
   - FSMC_LCD/src/stm32f10x_it.c    Interrupt handlers
   - FSMC_LCD/src/main.c            Main program 
   - FSMC_LCD/src/fsmc_nand.c       FSMC NAND driver firmware functions
   - FSMC_LCD/src/fsmc_nor.c        FSMC NOR driver firmware functions
   - FSMC_LCD/src/fsmc_sram.c       FSMC SRAM driver firmware functions
   - FSMC_LCD/src/stm3210e_lcd.c    LCD driver firmware functions
   - FSMC_LCD/src/sdcard.c          SD Card driver firmware functions
   - FSMC_LCD/src/menu.c            Menu navigation firmware functions         

@par Hardware and Software environment  

  - This example runs on STM32F10x High-Density Devices.
  
  - This example has been tested with STMicroelectronics STM3210E-EVAL (STM32F10x 
    High-Density) evaluation board and can be easily tailored to any other 
    supported device and development board.
     
@par How to use it ? 

 - RVMDK 
    - Open the FSMC_LCD.Uv2 project
    - Rebuild all files: Project->Rebuild all target files
    - Load project image: Debug->Start/Stop Debug Session
    - Run program: Debug->Run (F5)    

 - EWARMv5 
    - Open the FSMC_LCD.eww workspace.
    - Rebuild all files: Project->Rebuild all
    - Load project image: Project->Debug
    - Run program: Debug->Go(F5)

 - RIDE 
    - Open the FSMC_LCD.rprj project.
    - Rebuild all files: Project->build project
    - Load project image: Debug->start(ctrl+D)
    - Run program: Debug->Run(ctrl+F9)  

@note
- High-density devices are STM32F101xx and STM32F103xx microcontrollers where
  the Flash memory density ranges between 256 and 512 Kbytes.               

 * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
 */
