// lcd.c - LCD control code for STM32F10x //
// Sean Greenslade, 2012                  //

/* Color LCD configuration ------------------------------------
     LCD configured as follow:
      - Data/Address MUX = Disable
      - Memory Type = SRAM
      - Data Width = 16bit
      - Write Operation = Enable
      - Extended Mode = Enable
      - Asynchronous Wait = Disable 
*/
#include "lcd.h"
#include "stm32f10x.h"
#include "stm32f10x_fsmc.h"
#include "uart.h"
#include <string.h>
#include <stdint.h>

//#define LCD_REG              (*((volatile uint32_t *) 0x64000000)) // RS = 0 
//#define LCD_RAM              (*((volatile uint32_t *) 0x64010000)) // RS = 1 

#define LCD_REG              (*((volatile uint32_t *) 0x60000000)) // RS = 0 
#define LCD_RAM              (*((volatile uint32_t *) 0x60020000)) // RS = 1 

#define write_reg(a,d)       LCD_REG=(a);LCD_RAM=(d)
#define rw_data_prepare()    LCD_REG=(34)
#define write_data(x)        LCD_RAM=(x)

/* FSMC BCRx Mask */
#define BCR_MBKEN_Set                       ((uint32_t)0x00000001)
#define BCR_MBKEN_Reset                     ((uint32_t)0x000FFFFE)
#define BCR_FACCEN_Set                      ((uint32_t)0x00000040)

/* FSMC PCRx Mask */
#define PCR_PBKEN_Set                       ((uint32_t)0x00000004)
#define PCR_PBKEN_Reset                     ((uint32_t)0x000FFFFB)
#define PCR_ECCEN_Set                       ((uint32_t)0x00000040)
#define PCR_ECCEN_Reset                     ((uint32_t)0x000FFFBF)
#define PCR_MemoryType_NAND                 ((uint32_t)0x00000008)

///////// ITOA //////////

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
	    c = s[i];
	    s[i] = s[j];
	    s[j] = c;
   	}
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {       /* generate digits in reverse order */
		s[i++] = n % 10 + '0';   /* get next digit */
	} while ((n /= 10) > 0);     /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/////// END ITOA ////////


void FSMC_NORSRAMInit(FSMC_NORSRAMInitTypeDef* FSMC_NORSRAMInitStruct)
{ 
  /* Bank1 NOR/SRAM control register configuration */ 
  FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 
            (uint32_t)FSMC_NORSRAMInitStruct->FSMC_DataAddressMux |
            FSMC_NORSRAMInitStruct->FSMC_MemoryType |
            FSMC_NORSRAMInitStruct->FSMC_MemoryDataWidth |
            FSMC_NORSRAMInitStruct->FSMC_BurstAccessMode |
            FSMC_NORSRAMInitStruct->FSMC_AsynchronousWait |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalPolarity |
            FSMC_NORSRAMInitStruct->FSMC_WrapMode |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignalActive |
            FSMC_NORSRAMInitStruct->FSMC_WriteOperation |
            FSMC_NORSRAMInitStruct->FSMC_WaitSignal |
            FSMC_NORSRAMInitStruct->FSMC_ExtendedMode |
            FSMC_NORSRAMInitStruct->FSMC_WriteBurst;

  if(FSMC_NORSRAMInitStruct->FSMC_MemoryType == FSMC_MemoryType_NOR)
  {
    FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank] |= (uint32_t)BCR_FACCEN_Set;
  }
  
  /* Bank1 NOR/SRAM timing register configuration */
  FSMC_Bank1->BTCR[FSMC_NORSRAMInitStruct->FSMC_Bank+1] = 
            (uint32_t)FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressSetupTime |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AddressHoldTime << 4) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataSetupTime << 8) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_BusTurnAroundDuration << 16) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_CLKDivision << 20) |
            (FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_DataLatency << 24) |
             FSMC_NORSRAMInitStruct->FSMC_ReadWriteTimingStruct->FSMC_AccessMode;
            
    
  /* Bank1 NOR/SRAM timing register for write configuration, if extended mode is used */
  if(FSMC_NORSRAMInitStruct->FSMC_ExtendedMode == FSMC_ExtendedMode_Enable)
  {
        FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 
              (uint32_t)FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressSetupTime |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AddressHoldTime << 4 )|
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataSetupTime << 8) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_CLKDivision << 20) |
              (FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_DataLatency << 24) |
               FSMC_NORSRAMInitStruct->FSMC_WriteTimingStruct->FSMC_AccessMode;
  }
  else
  {
    FSMC_Bank1E->BWTR[FSMC_NORSRAMInitStruct->FSMC_Bank] = 0x0FFFFFFF;
  }
}

void write_cmd(unsigned short cmd)
{
    LCD_REG = cmd;
}


unsigned short read_data(void)
{
    return LCD_RAM;
}

unsigned short read_reg(unsigned char reg_addr)
{
    unsigned short val=0;
    write_cmd(reg_addr);
    val = read_data();
    return (val);
}


void FSMC_NORSRAMCmd(uint32_t FSMC_Bank, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		/* Enable the selected NOR/SRAM Bank by setting the PBKEN bit in the BCRx register */
		FSMC_Bank1->BTCR[FSMC_Bank] |= BCR_MBKEN_Set;
	}
	else
	{
		/* Disable the selected NOR/SRAM Bank by clearing the PBKEN bit in the BCRx register */
		FSMC_Bank1->BTCR[FSMC_Bank] &= BCR_MBKEN_Reset;
	}
}


void lcdInit(void)
{
	// Enable domain clocks.
	RCC->AHBENR |= RCC_AHBENR_FSMCEN; // Memory controller.
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPEEN; // Port D,E (for control lines).
	GPIOD->CRL |= 0xB0BB00BB; // AFIO outputs for data lines. D4 = RD, D5 = WR, D7 = CS
	GPIOD->CRH |= 0xBB00BBBB; // D11 = RS
	GPIOE->CRL |= 0xB0000000;
	GPIOE->CRH |= 0xBBBBBBBB;


	// Initialize FSMC
	/*FSMC_Bank1->BTCR[0] = FSMC_BCR1_EXTMOD | FSMC_BCR1_WREN | FSMC_BCR1_MWID_0; // BCR
	FSMC_Bank1->BTCR[4] &= ~(FSMC_BTR1_ACCMOD); // BTR
	FSMC_Bank1E->BWTR[0] &= ~(FSMC_BWTR1_ACCMOD); 

	FSMC_Bank1->BTCR[0] |= FSMC_BCR1_MBKEN; // Enable memory bank.	
	*/
	///////////////////////////////////////////
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  Timing_read,Timing_write;

    /*-- FSMC Configuration -------------------------------------------------*/
    Timing_read.FSMC_AddressSetupTime = 30;             /* µØÖ·½¨Á¢Ê±¼ä  */
    Timing_read.FSMC_DataSetupTime = 30;                /* Êý¾Ý½¨Á¢Ê±¼ä  */
    Timing_read.FSMC_AccessMode = FSMC_AccessMode_A;    /* FSMC ·ÃÎÊÄ£Ê½ */

    Timing_write.FSMC_AddressSetupTime = 30;             /* µØÖ·½¨Á¢Ê±¼ä  */
    Timing_write.FSMC_DataSetupTime = 30;                /* Êý¾Ý½¨Á¢Ê±¼ä  */
    Timing_write.FSMC_AccessMode = FSMC_AccessMode_A;   /* FSMC ·ÃÎÊÄ£Ê½ */

    /* Color LCD configuration ------------------------------------
       LCD configured as follow:
          - Data/Address MUX = Disable
          - Memory Type = SRAM
          - Data Width = 16bit
          - Write Operation = Enable
          - Extended Mode = Enable
          - Asynchronous Wait = Disable */
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    //FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &Timing_read;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &Timing_write;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);
	// Correct erroneous setting.
	FSMC_Bank1->BTCR[0] &= ~(FSMC_BCR1_MTYP_0 | FSMC_BCR1_MTYP_1 | FSMC_BCR1_FACCEN | FSMC_BCR1_BURSTEN | FSMC_BCR1_WRAPMOD | FSMC_BCR1_WAITCFG);
	(*((uint32_t *)(0xa0000000))) = 0x00005011;
	(*((uint32_t *)(0xa0000004))) = 0x00100813;
	(*((uint32_t *)(0xa0000104))) = 0x00100813;
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);

	///////////////////////////////////////////

    delay(3000);

	// power supply setting
    // set R07h at 0021h (GON=1,DTE=0,D[1:0]=01)
    write_reg(0x0007,0x0021);
    // set R00h at 0001h (OSCEN=1)
	/*write_reg(0x0000,0x0001);
    // set R07h at 0023h (GON=1,DTE=0,D[1:0]=11)
    write_reg(0x0007,0x0023);
    // set R10h at 0000h (Exit sleep mode)
    write_reg(0x0010,0x0000);
    // Wait 30ms
    delay(3000);
    // set R07h at 0033h (GON=1,DTE=1,D[1:0]=11)
    write_reg(0x0007,0x0033);
    // Entry mode setting (R11h)
    // R11H Entry mode
    // vsmode DFM1 DFM0 TRANS OEDef WMode DMode1 DMode0 TY1 TY0 ID1 ID0 AM LG2 LG2 LG0
    //   0     1    1     0     0     0     0      0     0   1   1   1  *   0   0   0
    write_reg(0x0011,0x6070);
    // LCD driver AC setting (R02h)
    write_reg(0x0002,0x0600);
	// power control 1
	// DCT3 DCT2 DCT1 DCT0 BT2 BT1 BT0 0 DC3 DC2 DC1 DC0 AP2 AP1 AP0 0
	// 1     0    1    0    1   0   0  0  1   0   1   0   0   1   0  0
	// DCT[3:0] fosc/4 BT[2:0]  DC{3:0] fosc/4
	write_reg(0x0003,0x0804);//0xA8A4
	write_reg(0x000C,0x0000);//
	write_reg(0x000D,0x0808);// 0x080C --> 0x0808
	// power control 4
	// 0 0 VCOMG VDV4 VDV3 VDV2 VDV1 VDV0 0 0 0 0 0 0 0 0
	// 0 0   1    0    1    0    1    1   0 0 0 0 0 0 0 0
	write_reg(0x000E,0x2900);
	write_reg(0x001E,0x00B8);
	write_reg(0x0001,0x2B3F);//Çý¶¯Êä³ö¿ØÖÆ320*240  0x6B3F
	write_reg(0x0010,0x0000);
	write_reg(0x0005,0x0000);
	write_reg(0x0006,0x0000);
	write_reg(0x0016,0xEF1C);
	write_reg(0x0017,0x0003);
	write_reg(0x0007,0x0233);//0x0233
	write_reg(0x000B,0x0000|(3<<6));
	write_reg(0x000F,0x0000);//É¨Ãè¿ªÊ¼µØÖ·
	write_reg(0x0041,0x0000);
	write_reg(0x0042,0x0000);
    write_reg(0x0048,0x0000);
	write_reg(0x0049,0x013F);
	write_reg(0x004A,0x0000);
	write_reg(0x004B,0x0000);
	write_reg(0x0044,0xEF00);
	write_reg(0x0045,0x0000);
	write_reg(0x0046,0x013F);
	write_reg(0x0030,0x0707);
	write_reg(0x0031,0x0204);
	write_reg(0x0032,0x0204);
	write_reg(0x0033,0x0502);
	write_reg(0x0034,0x0507);
	write_reg(0x0035,0x0204);
	write_reg(0x0036,0x0204);
	write_reg(0x0037,0x0502);
	write_reg(0x003A,0x0302);
   	write_reg(0x003B,0x0302);
   	write_reg(0x0023,0x0000);
    write_reg(0x0024,0x0000);
   	write_reg(0x0025,0x8000);   // 65hz
   	write_reg(0x004f,0);        // ÐÐÊ×Ö·0
   	write_reg(0x004e,0);        // ÁÐÊ×Ö·0

	// Test blank.
	uint32_t i;
	write_reg(0x004e,0);    // 0-239 
	write_reg(0x004f,0);    // 0-319 
	rw_data_prepare();                      // Prepare to write GRAM 
	for (i=0; i<(320*240); i++)
	{
		write_data(0x001f);
	}
*/
	// Test device ID.
	//write_reg(0x004e,2);    // 0-239 
/*
	uint16_t deviceid = read_reg(0x00);		
	if(deviceid == 0x8989) txStr("OK");
	else if(deviceid == 0) txStr("Zero");
	else if(deviceid > 0x8989) txStr("Really big");
	else txStr("wut");
	char did[10];

	txStr("\r\n");
	itoa(deviceid, did);
	txStr(did);
    GPIOB->BSRR = (1<<1);
*/
}

void lcdSetPixel(uint16_t x, uint16_t y, uint16_t pixel)
{
	write_reg(0x004e,x);
	write_reg(0x004f,y);

	rw_data_prepare();
	write_data(pixel);
}

static void delay(int cnt)
{
	volatile unsigned int dl;
	while(cnt--)
	{
		for(dl=0; dl<500; dl++);
	}
}
