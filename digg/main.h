
void display_digit(uint8_t digit, uint8_t value);
uint8_t segments(uint8_t x);

#define SEG_DCC PB7
#define SEG_DCC_PORT PORTB
#define SEG_CC1 PB1
#define SEG_CC1_PORT PORTB
#define SEG_CC2 PD0
#define SEG_CC2_PORT PORTD
#define SEG_CC3 PD4
#define SEG_CC3_PORT PORTD

#define SEG_A PB5
#define SEG_B PB4
#define SEG_C PB2
#define SEG_D PB0
#define SEG_E PB3
#define SEG_F PB6
#define SEG_G PD1
#define SEG_DP PD6

#define BUTTON PD2
#define BUTTON_PORT PORTD
#define BUTTON_PIN PIND
#define BUTTON_DDR DDRD
