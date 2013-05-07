;*****************************************************************
;*
;* - Description:  STK500 interface definition file for RC
;*                 Calibration
;*
;* - File:         isp_STK500_interface.inc
;* - AppNote:      AVR053 - Production calibration of the
;*                          RC oscillator
;*
;* - Author:       Atmel Corporation: http://www.atmel.com
;*                 Support email: avr@atmel.com
;*
;* $Name$
;* $Revision: 56 $
;* $RCSfile$
;* $Date: 2006-02-16 17:44:45 +0100 (to, 16 feb 2006) $
;*****************************************************************


;*****************************************************************
;* Description: Interface definition file for RC Calibration
;*
;* $Revision: 56 $	
;* $Author: rksnilsberg $
;* $Date: 2006-02-16 17:44:45 +0100 (to, 16 feb 2006) $
;*
;*****************************************************************


;*****************************************************************
;*	Specify Calibration clock frequency
;*****************************************************************
.EQU	CALIB_CLOCK_FREQ	= 32623	;Calibration Clock frequency 
						;in Hz. 7.3728MHz/(2*113) CHANGE WITH CARE

;*****************************************************************
;*	Pin and port definitions
;*****************************************************************
.EQU	MISO 		= ISP_CAL_MISO
.EQU	MOSI		= ISP_CAL_MOSI

.EQU	CAL_PORT	= ISP_CAL_PORT_REG
.EQU	CAL_DDR		= ISP_CAL_DDR_REG
.EQU	CAL_PIN		= ISP_CAL_PIN_REG

;*****************************************************************
;*	Macro used to disable and enable JTAG functions as these 
;*	override IO functions. Macro contains nop if not using JTAG.
;*****************************************************************
.MACRO	OPEN_INTERFACE_ACCESS
	nop
.ENDMACRO

.MACRO	CLOSE_INTERFACE_ACCESS
	nop
.ENDMACRO
