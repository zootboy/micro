;
; ATtiny2313 Internal Oscillator Calibration via Async Serial [osc_cal]
;
;
; Copyright (C) 2008 Kevin Timmerman
;
; http://www.compendiumarcana.com
;
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
;
;
; ---> Burn firmware (MiniPOV3) <---
;
; avrdude -p t2313 -c dasa -P COMx -U flash:w:osc_cal.hex
;
;
;
;
;
; DE9			ATtiny2323
;--------------------------
; 1 CD		<-
; 2 RxD		<-	3  D1
; 3 TxD		->	17 B5
; 4	DTR		->
; 5 Gnd		--	10 Gnd
; 6 DSR		<-
; 7	RTS		->
; 8	CTS		<-
; 9 RI		<-
;
;
;
;


	;.DEVICE	ATtiny2313							; This is in the include file
													;
	.INCLUDE	"tn2313def.inc"						; Register/Bit Definitions for the ATtiny2313
													;
													;
													; - Register usage
	.DEF	temp        = r16						;
	.DEF	temp2       = r17						;
	.DEF	delay_cnt   = r18						;
	.DEF	tx_data     = r19						;
	.DEF	bit_count   = r20						;
	.DEF	bit_time	= r21						;
	.DEF	cal			= r22
													;
													; - I/O Port usage
													;
	.EQU	rx_port         = PINB					; Serial data from host
	.EQU	rx_bit          = 5						;
	.EQU	tx_port         = PORTD					; Serial data to host
	.EQU	tx_bit          = 1						;
													;
													;
	.MACRO print									; Macro to print messages
	ldi		r30,low(@0<<1)							;  Get address LSB to Z register LSB
	rcall	tx_msg									;  Print it
	.ENDMACRO										;
													;
	.CSEG											; Code segment
													;
	.ORG 0											; - Interrupt Vectors
													;
	rjmp	init									;  1 0000 Reset
	rjmp	bad_int									;  2 0001 INT0
	rjmp	bad_int									;  3 0002 INT1
	rjmp	bad_int									;  4 0003 T1 Capture
	rjmp	bad_int									;  5 0004 T1 Compare A
	rjmp	bad_int									;  6 0005 T1 Overflow
	rjmp	bad_int									;  7 0006 T0 Overflow
	rjmp	bad_int									;  8 0007 UART Rx
	rjmp	bad_int									;  9 0008 UART Tx Empty
	rjmp	bad_int									; 10 0009 UART Tx Complete
	rjmp	bad_int									; 11 000A Analog Comparator
	rjmp	bad_int									; 12 000B Pin Change
	rjmp	bad_int									; 13 000C T1 Compare B
	rjmp	bad_int									; 14 000D T0 Compare A
	rjmp	bad_int									; 15 000E T0 Compare B
	rjmp	bad_int									; 16 000F USI Start
	rjmp	bad_int									; 17 0010 USI Overflow
	rjmp	bad_int									; 18 0011 EEPROM
	;rjmp	bad_int									; 19 0012 Watchdog
													;
bad_int:											; Unused interrupts
	rjmp	PC										;
													;
													;
													;
													;
init:												; --- Initialize
	ldi		temp,0b01011111							; Rx Data and DTR are inputs, all other outputs
	out		DDRB,temp								;
	ldi		temp,0b00100010							; Tx data is output, all others inputs
	out		DDRD,temp								;
	ldi		temp,0b00000000							;
	out		PORTB,temp								; Turn off all LEDs (MiniPOV3)
	out		PORTD,temp								; All other outputs off
													;
	ldi		temp,0									; Configure Timer/Counter 1
	out		TCCR1A,temp								;
	out		TCCR1C,temp								;
	ldi		temp,(1<<CS11)							; Prescale = /8 (1 uS tick @ 8 MHz)
	out		TCCR1B,temp								;
													;
	ldi		temp,0xDF								; Set stack pointer to top of RAM
	out		SPL,temp								;
													;
	ldi		r31,msg_start>>7						; Setup Z register MSB to page with messages
													;
													;
	in		cal,OSCCAL								; Get the current factory default OSCCAL
													;
	rcall	ascal									; Get async bit time
													;
	print	msg_Factory_Cal							; "Factory Cal"
													;
	rcall	report_cal								; Report the factory cal stats
													;
	rcall	crlf									; Blank line
													;
	mov		temp,cal								; Save the factory cal value
													;
	ldi		cal,0x30								; Begin testing OSCCAL at this value
													;
init_cal:											; -- Move down to starting value one step at a time
	cp		cal,temp								; Reached starting point?
	brsh	loop									; Yes...
													;
	dec		temp									; Move down one step
	out		OSCCAL,temp								;
													;
	ldi		delay_cnt,0xFF							; Wait a while
	rcall	delay									;
													;
	rjmp	init_cal								; Repeat...
													;
loop:												;
	out		OSCCAL,cal								; Set OSCCAL to test value
													;													
	rcall	ascal									; Get async bit time
													;
	rcall	report_cal								; Report OSCCAL and bit time values
													;
	inc		cal										; Increment test value
													;
	rjmp	loop									; Loop...
													;
													;
report_cal:											; --- Report OSCCAL and bit time information
	print	msg_OSCCAL								;													;
													;
	mov		temp,cal								; Send OSCCAL in hex
	rcall	send_hex_byte							;
													;
	print	msg_Time								;
													;
	mov		temp,bit_time							; Send async bit time in hex
	rcall	send_hex_byte							;
													;
	cpi		bit_time,0xCF							; Check for a bit time representing 8 MHz
	breq	osc8000									;
	cpi		bit_time,0xD0							;
	breq	osc8000									;
	cpi		bit_time,0xD1							;
	breq	osc8000									;
													;
	cpi		bit_time,0xBF							; Check for a bit time representing 7.323 MHz
	breq	osc7373									;
	cpi		bit_time,0xC0							;
	breq	osc7373									;
	cpi		bit_time,0xC1							;
	breq	osc7373									;
													;
	rjmp	crlf									; End the line and return to caller
													;
													;
osc8000:											; "8.000 MHz"
	print	msg_8000								;
mhz:												;
	print	msg_MHz									;
	rjmp	crlf									;
													;
osc7373:											; "7.373 MHz"
	print	msg_7373								;
	rjmp	mhz										;
													;
													;
													;
													;
													;
													;
													;
													; --- Async calibration
													;
													; The ASCII character 'x' is used for calibration
													;
													;              'x' == 0x78 == 01111000
													; Sent lsb first...           00011110
													; Inverted on the wire...     11100001
													; With start and stop bit... 1111000010
													;
													; Rising edge to falling edge is 4 bit times
													; Rising edge to next rising edge is 8 bit times
													;
													; Timer/counter 1 is configured for 1 uS per count
													; The measured duration is divided by 4 to get 4 uS resolution
													; 8 bits at 4 uS == 1 bit at 0.5 uS
													; The delay routine (above) has 0.5 uS granularity
													;													 
ascal:												;
sc_sb:												; Wait for start bit (first rising edge)
	sbis	rx_port,rx_bit							;
	rjmp	sc_sb									;
													;
	in		temp,TCNT1L								; Save start time
	in		temp2,TCNT1H							;
													;
sc_fe:												; Wait for falling edge
	sbic	rx_port,rx_bit							;
	rjmp	sc_fe									;

sc_et:												; Wait for [second] rising edge
	sbis	rx_port,rx_bit							;
	rjmp	sc_et									;
													;
	in		bit_time,TCNT1L							; Calculate duration
	sub		bit_time,temp							;
	in		temp,TCNT1H								;
	sbc		temp,temp2								;
													;
	lsr		temp									; Divide duration by 4
	ror		bit_time								;
	lsr		temp									;
	ror		bit_time								;
													;
	ret												; Return
													;
													;
													;
													;
crlf:												;
	ldi		tx_data,'\r'							;
	rcall	astx									;
	ldi		tx_data,'\n'							;
	rjmp	astx									;
													;
													;
send_hex_byte:										; --- Send hex byte in temp
	mov		tx_data,temp							;
	swap	tx_data									; Do upper nibble
	rcall	send_hex_nibble							;
	mov		tx_data,temp							; Do lower nibble and return
	;rjmp	send_hex_nibble							;
													;
send_hex_nibble:									; --- Send hex nibble (one hex digit)
	andi	tx_data,0x0F							; Mask off upper nibble
	cpi		tx_data,10								; Under 'A'?
	brlo	under_10								; Yes...
	subi	tx_data,'9'+1-'A'						; Adjust for gap between ASCII '9' and 'A'
under_10:											;
	subi	tx_data,-'0'							; Binary to ASCII - add '0'
	;rjmp	astx									; Tx it and return...
													;
													;
													; --- Async Serial Tx
astx:												;
	sbi		tx_port,tx_bit							; Start bit
	ldi		bit_count,9								; 9 bits to send (8 data, stop)
	mov		delay_cnt,bit_time						; Wait for bit duration
	subi	delay_cnt,4								;
	rcall	delay1									;
tx_loop:											; - Do a bit
	sec												; Shift in stop bit
	ror		tx_data									; Shift out next bit
	brcs	tx_one									; One...
	nop												; Zero
	sbi		tx_port,tx_bit							; Signal zero bit (data is inverted!)
	rjmp	tx_next									;
tx_one:												;
	cbi		tx_port,tx_bit							; Signal one bit (data is inverted!)
	rjmp	tx_next									;
tx_next:											;
	mov		delay_cnt,bit_time						;
	subi	delay_cnt,5								;
	rcall	delay1									;
	dec		bit_count								; Decrement bit count
	brne	tx_loop									; Next bit...
	ret												; Return
													;
													;
													; --- Delay in units of 0.5 uS (4 instruction cycles)
													;
delay1:												; Entry point with one more instruction cycle
	nop												;
delay:												;
	nop												;
	dec		delay_cnt								;
	brne	delay									;
	ret												;
													;
tx_msg:												; --- Print a message pointed to by Z
	lpm		tx_data,z+								; Get a char
	tst		tx_data									; Is is NULL?
	breq	end_msg									; Yes, exit...
	rcall	astx									; Send char to host
	rjmp	tx_msg									; Next char...
end_msg:											;
	ret												;
													;
													;
	.ORG	(PC+127)&~127							; Move up to next page boundry
													;
msg_start:											; Messages start here
													;
msg_Factory_Cal:									;
	.DB		"Factory Cal",'\r','\n',0				;
msg_OSCCAL:											;
	.DB		"OSCCAL: ",0,0							;
msg_Time:											;
	.DB		" Time: ",0								;
msg_8000:											;
	.DB		" == 8.000",0							;
msg_7373:											;
	.DB		" == 7.373",0							;
msg_MHz:											;
	.DB		" MHz",0,0								;
													;
													;
	.EXIT											; End of assembly code
													;
