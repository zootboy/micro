cls
@echo off
	@ECHO *********************************************************
	@ECHO  Batch file for calibration of Atmel AVR Mega16
	@ECHO  oscillator through the ISP interface with AVRISP mkII

	@ECHO  - The internal RC is calibrated to value and accuracy 
	@ECHO    given in RC_Calibration.asm (fuses set for 8 MHz)
	@ECHO  - Programming FLASH and Fuses is performed initially.
	@ECHO  - stk500.exe -h / AVR Studio help for more options
	@ECHO  
	@ECHO  $Name$
	@ECHO  $Revision: 56 $                            
	@ECHO  $RCSfile$
	@ECHO  $Date: 2006-02-16 17:44:45 +0100 (to, 16 feb 2006) $
	@ECHO *********************************************************
	
	@ECHO ---------------------------------------------------------
	@ECHO.
	@ECHO   ** S T A R T   P R O G R A M M I N G **
	@ECHO.		
@ECHO ---------------------------------------------------------

"C:\Program Files\Atmel\AVR Tools\STK500\stk500.exe" -cUSB -I125000 -datmega16 -s -f99e4 -e -pf -if"..\rc_calib.hex"



@IF ERRORLEVEL ==1 GOTO prog_Calib_code_error
		
	@ECHO.
	@ECHO  ** Start Calibration

@ECHO ---------------------------------------------------------
"C:\Program Files\Atmel\AVR Tools\STK500\stk500.exe" -cUSB -datmega16 -Y

@IF ERRORLEVEL ==1 GOTO Calibration_error

@ECHO ---------------------------------------------------------
	@ECHO.
	@ECHO Verify that OSCCAL value is different from 0xFF.
	@ECHO Note, this test is intended to fail. If it does
	@ECHO not fail, OSCCAL equals 0xFF which is considered 
	@ECHO an error.

"C:\Program Files\Atmel\AVR Tools\STK500\stk500.exe" -cUSB -I125000 -datmega16 -ae0,0 -ve -ie0xFF_byte.hex


@IF ERRORLEVEL ==1 GOTO continue

@GOTO EEPROM_OSCCAL_value_error

:continue
		
@ECHO           ^^ Ignore Error above ^^
@ECHO.
@ECHO ---------------------------------------------------------
	@ECHO Read out new OSCCAL value from EEPROM and erase the device.
	@ECHO Program in customers code to FLASH, in this case test.hex.
	@ECHO Verify programming of customers code.
	@ECHO Program in new OSCCAL value in flash at byte addr 01FF.
	@ECHO Verify programming of new OSCCAL value in Flash.
"C:\Program Files\Atmel\AVR Tools\STK500\stk500.exe" -cUSB -I125000 -datmega16 -e -pf -vf -if"test.hex" -Z0 -Sf0x01FF

@IF ERRORLEVEL ==1 GOTO prog_customer_code_error

	@ECHO.
	@ECHO *********************************************************
	@ECHO 		P R O G R A M M I N G   O K
	@ECHO *********************************************************
	@PAUSE

@GOTO END

:prog_Calib_code_error
	@ECHO.
@ECHO ---------------------------------------------------------
	@ECHO.
	@ECHO 		E R R O R		
	@ECHO Programming calibration program to AVR failed.
	@ECHO Programming aborted.
	@PAUSE
	@GOTO END
@ECHO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


:Calibration_error
	@ECHO.
@ECHO ---------------------------------------------------------
	@ECHO.
	@ECHO 		E R R O R
	@ECHO Calibration failed.
	@ECHO Programming aborted.
	@PAUSE
	@GOTO END
@ECHO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

:EEPROM_OSCCAL_value_error
	@ECHO.
@ECHO ---------------------------------------------------------
	@ECHO.
	@ECHO 		E R R O R
	@ECHO EEPROM OSCCAL location contain an invalid value: 0xFF
	@ECHO Programming aborted.
	@PAUSE
	@GOTO END
@ECHO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

:prog_customer_code_error
	@ECHO.
@ECHO ---------------------------------------------------------
	@ECHO.
	@ECHO 		E R R O R
	@ECHO Programming main application program or OSCCAL to AVR failed.
	@ECHO Programming aborted.
	@PAUSE
	@GOTO END
@ECHO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

:END				
