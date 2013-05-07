/* Captain - i2c.h */
#ifndef I2C_H
#define	I2C_H

extern uint8_t errorCode;
extern uint8_t gState;
extern uint8_t servoPos1;
extern uint8_t servoPos2;
extern uint8_t stepperCountTempL;
extern uint8_t stepperCountTempR;
extern uint8_t linearMotion;

extern uint16_t batteryADC;
extern uint16_t arcIR1;
extern uint16_t arcIR2;
extern uint16_t arcIR3;
extern uint16_t arcIR4;
extern uint16_t arcIR5;
extern uint16_t arcIR6;
extern uint16_t arcIR7;
extern uint16_t tempData;


/// Addresses for slaves ///
#define I2C_ADDR_PILOT      0b01000110
#define I2C_ADDR_COPILOT    0b01001000
#define I2C_ADDR_NAVIGATOR  0b01001010

/// I2C defines ///
#define I2C_TWBR  0x02 // 400 KHz mode.
#define I2C_TWCR  (1<<TWEN)|(1<<TWEA)|(1<<TWIE) // Enable TWI, enable ACK, enable interrupt.
#define I2C_TWSR  (1<<TWPS0) // Prescaler set to 4x.

#define BURST_COUNT 1 // Number of CO2 bursts.

uint8_t i2cMode;
uint8_t i2cByteIndex;
uint8_t dataSent;
uint8_t rxMode;

void i2cInit(void);
void i2cStart(uint8_t type);

#endif	/* I2C_H */

