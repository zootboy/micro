;*****************************************************************
;* - Description:  Device definition file for RC Calibration
;* - File:         m168.asm
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

.include "m48def.inc"
.include "Common\memoryMap.inc"

.EQU OSC_VER = 5

.include "Device specific\m8_family_pinout.inc"

.equ	TCCR0	= TCCR0B
.equ	TIFR	= TIFR0

