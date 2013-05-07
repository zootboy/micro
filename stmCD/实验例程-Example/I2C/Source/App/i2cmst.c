/*****************************************************************************
 *   i2cmst.c:  main C entry file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.26  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc17xx.h"
#include "i2c.h"

extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[BUFSIZE];
extern volatile uint32_t I2CCmd, I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

/*******************************************************************************
**   Main Function  main()
*******************************************************************************/
int main (void)
{
  uint32_t i;

  SystemInit();

  if ( I2CInit( (uint32_t)I2CMASTER ) == 0 )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
  }

  /* the example used to test the I2C interface is 
  a Philips's LM75 temp sensor, as an I2C slave.
    
  the sequence to get the temp reading is:
  get device ID register,
  set configuration register,
  get temp reading
  */

  /* In order to start the I2CEngine, the all the parameters 
  must be set in advance, including I2CWriteLength, I2CReadLength,
  I2CCmd, and the I2cMasterBuffer which contains the stream
  command/data to the I2c slave device. 
  (1) If it's a I2C write only, the number of bytes to be written is 
  I2CWriteLength, I2CReadLength is zero, the content will be filled 
  in the I2CMasterBuffer. 
  (2) If it's a I2C read only, the number of bytes to be read is 
  I2CReadLength, I2CWriteLength is 0, the read value will be filled 
  in the I2CMasterBuffer. 
  (3) If it's a I2C Write/Read with repeated start, specify the 
  I2CWriteLength, fill the content of bytes to be written in 
  I2CMasterBuffer, specify the I2CReadLength, after the repeated 
  start and the device address with RD bit set, the content of the 
  reading will be filled in I2CMasterBuffer index at 
  I2CMasterBuffer[I2CWriteLength+2]. 
  
  e.g. Start, DevAddr(W), WRByte1...WRByteN, Repeated-Start, DevAddr(R), 
  RDByte1...RDByteN Stop. The content of the reading will be filled 
  after (I2CWriteLength + two devaddr) bytes. */

  /* Configure temp register before reading */
  for ( i = 0; i < BUFSIZE; i++ )	/* clear buffer */
  {
	I2CMasterBuffer[i] = 0;
  }
  I2CWriteLength = 2;
  I2CReadLength = 0;
  I2CMasterBuffer[0] = LM75_ADDR;
  I2CMasterBuffer[1] = LM75_CONFIG;
  I2CMasterBuffer[2] = 0x55;	/* configuration value, no change from 
								default */
  I2CCmd = LM75_CONFIG;
  I2CEngine(); 

  /* Get temp reading */
  for ( i = 0; i < BUFSIZE; i++ )	/* clear buffer */
  {
	I2CMasterBuffer[i] = 0;
  }
  I2CWriteLength = 1;
  I2CReadLength = 2;
  I2CMasterBuffer[0] = LM75_ADDR;
  I2CMasterBuffer[1] = LM75_TEMP;
  I2CMasterBuffer[2] = LM75_ADDR | RD_BIT;
  I2CCmd = LM75_TEMP;
  I2CEngine();

  /* The temp reading value should reside in I2CMasterBuffer byte 3, 4 */ 
  while(1);

}

/******************************************************************************
**                            End Of File
******************************************************************************/
