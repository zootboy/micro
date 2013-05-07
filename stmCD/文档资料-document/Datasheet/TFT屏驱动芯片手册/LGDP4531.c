/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  LG LGDP4531 LCD controller driver
 *****************************************************************************
 * FileName:        LGDP4531.c
 * Dependencies:    Graphics.h
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Anton Alkhimenok     11/12/07	Version 1.0 release
 * Anton Alkhimenok	    01/30/08	combined version for landscape and portrait
 * Sean Justice         01/30/08    PIC32 support
 *****************************************************************************/
#include "Graphics.h"

// Color
WORD_VAL    _color;
// Clipping region control
SHORT _clipRgn;
// Clipping region borders
SHORT _clipLeft;
SHORT _clipTop;
SHORT _clipRight;
SHORT _clipBottom;

/////////////////////// LOCAL FUNCTIONS PROTOTYPES ////////////////////////////
void SetReg(BYTE index, WORD value);
void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch);
void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch);
void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch);
void PutImage16BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch);

void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch);
void PutImage4BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch);
void PutImage8BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch);
void PutImage16BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch);

/*********************************************************************
* Function:  void  DelayMs(WORD time)
*
* PreCondition: none
*
* Input: time - delay in ms
*
* Output: none
*
* Side Effects: none
*
* Overview: delays execution on time specified in ms
*
* Note: none
*
********************************************************************/
#ifdef __PIC32MX
void  DelayMs(WORD time)
{
    while(time--)
    {
        unsigned int int_status;

        int_status = INTDisableInterrupts();
        OpenCoreTimer(GetSystemClock() / 2000);     // core timer is at 1/2 system clock
        INTRestoreInterrupts(int_status);

        mCTClearIntFlag();

        while(!mCTGetIntFlag());

    }

    mCTClearIntFlag();
}
#else
#define DELAY_1MS 16000/5  // for 16MIPS
void  DelayMs(WORD time){
unsigned delay;
	while(time--)
		for(delay=0; delay<DELAY_1MS; delay++);	
}
#endif

/*********************************************************************
* Function:  void  SetReg(BYTE index, WORD value)
*
* PreCondition: none
*
* Input: index - register number
*        value - value to be set
*
* Output: none
*
* Side Effects: none
*
* Overview: sets graphics controller register
*
* Note: none
*
********************************************************************/
void  SetReg(BYTE index, WORD value){

    while(PMMODEbits.BUSY);
    CS_LAT_BIT = 0;
    SetIndex(index);
    WriteData(((WORD_VAL)value).v[1],((WORD_VAL)value).v[0]);
    CS_LAT_BIT = 1;
}

/*********************************************************************
* Function:  void ResetDevice()
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: resets LCD, initializes PMP
*
* Note: none
*
********************************************************************/
void ResetDevice(void){

    // Disable FLASH
    CS_FLASH_LAT_BIT = 1; 
    // Set FLASH CS pin as output
    CS_FLASH_TRIS_BIT = 0;
   
    // Hold in reset
    RST_LAT_BIT = 0;   
    // Set reset pin as output
    RST_TRIS_BIT = 0;

    // Enable data access
    RS_LAT_BIT = 1;
    // Set RS pin as output
    RS_TRIS_BIT = 0;

    // Disable LCD 
    CS_LAT_BIT = 1;
    // Set LCD CS pin as output
    CS_TRIS_BIT = 0;

    DelayMs(500);

#if (GRAPHICS_PICTAIL_VERSION == 2)
    // Power on LCD
    POWERON_LAT_BIT = 0;
    POWERON_TRIS_BIT = 0;
#endif

    DelayMs(200);

    // PMP setup 
    PMMODE = 0;
    PMAEN = 0;
    PMCON = 0;
    PMMODEbits.MODE  = 2;  // Master 2
    PMMODEbits.WAITB = 0;
    PMMODEbits.WAITM = 1;
    PMMODEbits.WAITE = 0;
    PMCONbits.CSF    = 0;
    PMCONbits.PTRDEN = 1;    
    PMCONbits.PTWREN = 1;
    PMCONbits.PMPEN  = 1; 

    // Release from reset
    RST_LAT_BIT = 1;   

    DelayMs(20);

    // Synchronization after reset
    CS_LAT_BIT = 0;
    WriteData(0,0);
    WriteData(0,0);
    CS_LAT_BIT = 1;  

    // Setup display

    SetReg(0x10,0x0628);
    SetReg(0x12,0x0006);
    SetReg(0x13,0x0A32);
    SetReg(0x11,0x0040);
    SetReg(0x15,0x0050);
    SetReg(0x12,0x0016);
    DelayMs(15);
    SetReg(0x10,0x5660);
    DelayMs(15);
    SetReg(0x13,0x2A4E);
    SetReg(0x01,0x0100);
    SetReg(0x02,0x0300);

#ifdef USE_PORTRAIT
    SetReg(0x03,0x1030);
#else
    SetReg(0x03,0x1038);
#endif

    SetReg(0x08,0x0202);
    SetReg(0x0A,0x0000);
    SetReg(0x30,0x0000);
    SetReg(0x31,0x0402);
    SetReg(0x32,0x0106);
    SetReg(0x33,0x0700);
    SetReg(0x34,0x0104);
    SetReg(0x35,0x0301);
    SetReg(0x36,0x0707);
    SetReg(0x37,0x0305);
    SetReg(0x38,0x0208);
    SetReg(0x39,0x0F0B);
    DelayMs(15);
    SetReg(0x41,0x0002);
    SetReg(0x60,0x2700);
    SetReg(0x61,0x0001);
    SetReg(0x90,0x0119);
    SetReg(0x92,0x010A);
    SetReg(0x93,0x0004);
    SetReg(0xA0,0x0100);
    SetReg(0x07,0x0001);
    DelayMs(15);
    SetReg(0x07,0x0021); 
    DelayMs(15);
    SetReg(0x07,0x0023);
    DelayMs(15);
    SetReg(0x07,0x0033);
    DelayMs(15);
    SetReg(0x07,0x0133);
    DelayMs(15);
    SetReg(0xA0,0x0000);
    DelayMs(20);

}

/*********************************************************************
* Function: void PutPixel(SHORT x, SHORT y)
*
* PreCondition: none
*
* Input: x,y - pixel coordinates
*
* Output: none
*
* Side Effects: none
*
* Overview: puts pixel
*
* Note: none
*
********************************************************************/
void PutPixel(SHORT x, SHORT y){
DWORD_VAL address;
    if(_clipRgn){
        if(x<_clipLeft)
            return;
        if(x>_clipRight)
            return;
        if(y<_clipTop)
            return;
        if(y>_clipBottom)
            return;
    }

#ifdef	USE_PORTRAIT

    address.Val = (long)LINE_MEM_PITCH*y + x;

#else

    y = GetMaxY() - y;
    address.Val = (long)LINE_MEM_PITCH*x + y;

#endif

    CS_LAT_BIT = 0;
    SetAddress(address.v[2],address.v[1],address.v[0]);
    WriteData(_color.v[1],_color.v[0]);   
    CS_LAT_BIT = 1;
}

/*********************************************************************
* Function: WORD GetPixel(SHORT x, SHORT y)
*
* PreCondition: none
*
* Input: x,y - pixel coordinates 
*
* Output: pixel color
*
* Side Effects: none
*
* Overview: returns pixel color at x,y position
*
* Note: none
*
********************************************************************/
WORD GetPixel(SHORT x, SHORT y){
DWORD_VAL address;
WORD_VAL  result;

#ifdef	USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*y + x;
#else
    y = GetMaxY() - y;
    address.Val = (long)LINE_MEM_PITCH*x + y;
#endif

    CS_LAT_BIT = 0;

    SetAddress(address.v[2],address.v[1],address.v[0]);

    // Temporary change wait cycles for reading (250ns = 4 cycles)
    PMMODEbits.WAITM = 4;
    RS_LAT_BIT = 1;

    // First RD cycle to move data from GRAM to Read Data Latch
    result.v[1] = PMDIN1;

    while(PMMODEbits.BUSY);

    // Second RD cycle to move data from GRAM to Read Data Latch
    result.v[1] = PMDIN1;

    while(PMMODEbits.BUSY);

    // First RD cycle to get data from Read Data Latch
    // Read previous dummy value
    result.v[1] = PMDIN1;

    while(PMMODEbits.BUSY);

    // Second RD cycle to get data from Read Data Latch
    // Read MSB
    result.v[1] = PMDIN1;

    while(PMMODEbits.BUSY);

    // Disable LCD 
    CS_LAT_BIT = 1;
    // Disable PMP 
    PMCONbits.PMPEN  = 1; 

    // Read LSB
    result.v[0] = PMDIN1;

    // Restore wait cycles for writing (60ns = 1 cycle)    
    PMMODEbits.WAITM = 1;
    // Enable PMP
    PMCONbits.PMPEN  = 1; 

    return result.Val;
}

/*********************************************************************
* Function: void Bar(SHORT left, SHORT top, SHORT right, SHORT bottom)
*
* PreCondition: none
*
* Input: left,top - top left corner coordinates,
*        right,bottom - bottom right corner coordinates
*
* Output: none
*
* Side Effects: none
*
* Overview: draws rectangle filled with current color
*
* Note: none
*
********************************************************************/
void Bar(SHORT left, SHORT top, SHORT right, SHORT bottom){
DWORD_VAL address;
register SHORT  x,y;

	if(_clipRgn){
        if(left<_clipLeft)
           left = _clipLeft;
        if(right>_clipRight)
           right= _clipRight;
        if(top<_clipTop)
           top = _clipTop;
        if(bottom>_clipBottom)
           bottom = _clipBottom;
    }

#ifdef	USE_PORTRAIT

    address.Val = (DWORD)LINE_MEM_PITCH*top + left;

    CS_LAT_BIT = 0;
    for(y=top; y<bottom+1; y++){
        SetAddress(address.v[2],address.v[1],address.v[0]);
        for(x=left; x<right+1; x++){
            WriteData(_color.v[1],_color.v[0]);
        }
        address.Val += LINE_MEM_PITCH;
    }
    CS_LAT_BIT = 1;

#else

	top = GetMaxY() - top;
    bottom = GetMaxY() - bottom;
    address.Val = (DWORD)LINE_MEM_PITCH*left + top;

    CS_LAT_BIT = 0;
    for(y=bottom; y<top+1; y++){
        SetAddress(address.v[2],address.v[1],address.v[0]);
        for(x=left; x<right+1; x++){
            WriteData(_color.v[1],_color.v[0]);
        }
        address.Val -= 1;
    }
    CS_LAT_BIT = 1;

#endif

}

/*********************************************************************
* Function: void ClearDevice(void)
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
* Overview: clears screen with current color 
*
* Note: none
*
********************************************************************/
void ClearDevice(void){
DWORD     counter;

    CS_LAT_BIT = 0;
    SetAddress(0,0,0);
    for(counter=0; counter<(DWORD)(GetMaxX()+1)*(GetMaxY()+1); counter++){
        WriteData(_color.v[1],_color.v[0]);
    }
    CS_LAT_BIT = 1;
}

/*********************************************************************
* Function: void PutImage(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage(SHORT left, SHORT top, void* bitmap, BYTE stretch){
FLASH_BYTE* flashAddress;
BYTE colorDepth;
WORD colorTemp;

#ifndef USE_PORTRAIT
	top = GetMaxY() - top; 
#endif

    // Save current color
    colorTemp = _color.Val;

    switch(*((SHORT*)bitmap))
    {
#ifdef USE_BITMAP_FLASH
        case FLASH:
            // Image address
            flashAddress = ((BITMAP_FLASH*)bitmap)->address;
            // Read color depth
            colorDepth = *(flashAddress+1);
            // Draw picture
            switch(colorDepth){
                case 1:
                    PutImage1BPP(left, top, flashAddress, stretch);
                    break;
                case 4:
                    PutImage4BPP(left, top, flashAddress, stretch);
                    break;
                case 8:
                    PutImage8BPP(left, top, flashAddress, stretch);
                    break;
                case 16:
                    PutImage16BPP(left, top, flashAddress, stretch);
                    break;
            }
            break;
#endif
#ifdef USE_BITMAP_EXTERNAL
        case EXTERNAL:
            // Get color depth
            ExternalMemoryCallback(bitmap, 1, 1, &colorDepth);
            // Draw picture
            switch(colorDepth){
                case 1:
                    PutImage1BPPExt(left, top, bitmap, stretch);
                    break;
                case 4:
                    PutImage4BPPExt(left, top, bitmap, stretch);
                    break;
                case 8:
                    PutImage8BPPExt(left, top, bitmap, stretch);
                    break;
                case 16:
                    PutImage16BPPExt(left, top, bitmap, stretch);
                    break;
                default:
                    break;
            }
            break;
#endif
        default:
            break;
    }

    // Restore current color
    _color.Val = colorTemp;
}

#ifdef USE_BITMAP_FLASH
/*********************************************************************
* Function: void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner,
*        bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage1BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch){
register DWORD_VAL address;
register FLASH_BYTE* flashAddress;
register FLASH_BYTE* tempFlashAddress;
BYTE temp;
WORD sizeX, sizeY;
WORD x,y;
BYTE stretchX,stretchY;
WORD pallete[2];
BYTE mask;

    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Read image size
    sizeY = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    pallete[0] = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    pallete[1] = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;

    CS_LAT_BIT = 0;
    for(y=0; y<sizeY; y++){
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY<stretch; stretchY++){
            flashAddress = tempFlashAddress;
            SetAddress(address.v[2],address.v[1],address.v[0]);
            mask = 0;
            for(x=0; x<sizeX; x++){

                // Read 8 pixels from flash
                if(mask == 0){
                    temp = *flashAddress;
                    flashAddress++;
                    mask = 0x80;
                }
                
                // Set color
                if(mask&temp){
                    SetColor(pallete[1]);
                }else{
                    SetColor(pallete[0]);
                }

                // Write pixel to screen
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }

                // Shift to the next pixel
                mask >>= 1;
           }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
    }
    CS_LAT_BIT = 1;
}

/*********************************************************************
* Function: void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs 16 color image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage4BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch){
register DWORD_VAL address;
register FLASH_BYTE* flashAddress;
register FLASH_BYTE* tempFlashAddress;
WORD sizeX, sizeY;
register WORD x,y;
BYTE temp;
register BYTE stretchX,stretchY;
WORD pallete[16];
WORD counter;

    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Read image size
    sizeY = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;

    // Read pallete
    for(counter=0;counter<16;counter++){
        pallete[counter] = *((FLASH_WORD*)flashAddress);
        flashAddress += 2;
    }

    CS_LAT_BIT = 0;     
    for(y=0; y<sizeY; y++){
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY<stretch; stretchY++){
            flashAddress = tempFlashAddress;
            SetAddress(address.v[2],address.v[1],address.v[0]);
            for(x=0; x<sizeX; x++){
                // Read 2 pixels from flash
                if(x&0x0001){
                    // second pixel in byte
                    SetColor(pallete[temp>>4]);
                }else{
                    temp = *flashAddress;
                    flashAddress++;
                    // first pixel in byte
                    SetColor(pallete[temp&0x0f]);
                }

                // Write pixel to screen       
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }

                // Shift to the next pixel
                //temp >>= 4;
            }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
    }
    CS_LAT_BIT = 1;
}

/*********************************************************************
* Function: void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs 256 color image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage8BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch){
register DWORD_VAL address;
register FLASH_BYTE* flashAddress;
register FLASH_BYTE* tempFlashAddress;
WORD sizeX, sizeY;
WORD x,y;
BYTE temp;
BYTE stretchX, stretchY;
WORD pallete[256];
WORD counter;

    // Move pointer to size information
    flashAddress = bitmap + 2;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Read image size
    sizeY = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;
    sizeX = *((FLASH_WORD*)flashAddress);
    flashAddress += 2;

    // Read pallete
    for(counter=0;counter<256;counter++){
        pallete[counter] = *((FLASH_WORD*)flashAddress);
        flashAddress += 2;
    }

    CS_LAT_BIT = 0;     
    for(y=0; y<sizeY; y++){
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY<stretch; stretchY++){
            flashAddress = tempFlashAddress;
            SetAddress(address.v[2],address.v[1],address.v[0]);
            for(x=0; x<sizeX; x++){
                // Read pixels from flash
                temp = *flashAddress;
                flashAddress++;

                // Set color
                SetColor(pallete[temp]);

                // Write pixel to screen       
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }
            }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
    }
    CS_LAT_BIT = 1;
}

/*********************************************************************
* Function: void PutImage16BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs hicolor image starting from left,top coordinates
*
* Note: image must be located in flash
*
********************************************************************/
void PutImage16BPP(SHORT left, SHORT top, FLASH_BYTE* bitmap, BYTE stretch){
register DWORD_VAL address;
register FLASH_WORD* flashAddress;
register FLASH_WORD* tempFlashAddress;
WORD sizeX, sizeY;
register WORD x,y;
WORD temp;
register BYTE stretchX,stretchY;

    // Move pointer to size information
    flashAddress = (FLASH_WORD*)bitmap + 1;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Read image size
    sizeY = *flashAddress;
    flashAddress++;
    sizeX = *flashAddress;
    flashAddress++;

    CS_LAT_BIT = 0;     
    for(y=0; y<sizeY; y++){
        tempFlashAddress = flashAddress;
        for(stretchY = 0; stretchY<stretch; stretchY++){
            flashAddress = tempFlashAddress;
            SetAddress(address.v[2],address.v[1],address.v[0]);
            for(x=0; x<sizeX; x++){
                // Read pixels from flash
                temp = *flashAddress;
                flashAddress++;

                // Set color
                SetColor(temp);

                // Write pixel to screen       
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }
            }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
    }
    CS_LAT_BIT = 1;
}
#endif

#ifdef USE_BITMAP_EXTERNAL
/*********************************************************************
* Function: void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage1BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch){
register DWORD_VAL  address;
register DWORD      memOffset;
BITMAP_HEADER       bmp;
WORD                pallete[2];
BYTE                lineBuffer[(SCREEN_HOR_SIZE/8)+1];
BYTE*               pData; 
SHORT               byteWidth;

BYTE                temp;
BYTE                mask;
WORD                sizeX, sizeY;
WORD                x,y;
BYTE                stretchX, stretchY;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (2 entries)
    ExternalMemoryCallback(bitmap, sizeof(BITMAP_HEADER), 2*sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 2*sizeof(WORD);

    // Line width in bytes
    byteWidth = bmp.width>>3;
    if(bmp.width&0x0007)
        byteWidth++;

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y=0; y<sizeY; y++){

        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        CS_LAT_BIT = 0;
        for(stretchY = 0; stretchY<stretch; stretchY++){
            pData = lineBuffer;
            SetAddress(address.v[2],address.v[1],address.v[0]);
            mask = 0;
            for(x=0; x<sizeX; x++){

                // Read 8 pixels from flash
                if(mask == 0){
                    temp = *pData++;
                    mask = 0x80;
                }
                
                // Set color
                if(mask&temp){
                    SetColor(pallete[1]);
                }else{
                    SetColor(pallete[0]);
                }

                // Write pixel to screen
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }

                // Shift to the next pixel
                mask >>= 1;
           }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
        CS_LAT_BIT = 1;
    }
}

/*********************************************************************
* Function: void PutImage4BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage4BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch){
register DWORD_VAL  address;
register DWORD      memOffset;
BITMAP_HEADER       bmp;
WORD                pallete[16];
BYTE                lineBuffer[(SCREEN_HOR_SIZE/2)+1];
BYTE*               pData; 
SHORT               byteWidth;

BYTE                temp;
WORD                sizeX, sizeY;
WORD                x,y;
BYTE                stretchX, stretchY;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (16 entries)
    ExternalMemoryCallback(bitmap, sizeof(BITMAP_HEADER), 16*sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 16*sizeof(WORD);

    // Line width in bytes
    byteWidth = bmp.width>>1;
    if(bmp.width&0x0001)
        byteWidth++;

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y=0; y<sizeY; y++){

        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        CS_LAT_BIT = 0;
        for(stretchY = 0; stretchY<stretch; stretchY++){

            pData = lineBuffer;
            SetAddress(address.v[2],address.v[1],address.v[0]);

            for(x=0; x<sizeX; x++){

                // Read 2 pixels from flash
                if(x&0x0001){
                    // second pixel in byte
                    SetColor(pallete[temp>>4]);
                }else{
                    temp = *pData++;
                    // first pixel in byte
                    SetColor(pallete[temp&0x0f]);
                }

                // Write pixel to screen       
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }
           }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
        CS_LAT_BIT = 1;
    }
}

/*********************************************************************
* Function: void PutImage8BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage8BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch){
register DWORD_VAL  address;
register DWORD      memOffset;
BITMAP_HEADER       bmp;
WORD                pallete[256];
BYTE                lineBuffer[SCREEN_HOR_SIZE];
BYTE*               pData; 

BYTE                temp;
WORD                sizeX, sizeY;
WORD                x,y;
BYTE                stretchX, stretchY;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);

    // Get pallete (256 entries)
    ExternalMemoryCallback(bitmap, sizeof(BITMAP_HEADER), 256*sizeof(WORD), pallete);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER) + 256*sizeof(WORD);

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    for(y=0; y<sizeY; y++){

        // Get line
        ExternalMemoryCallback(bitmap, memOffset, sizeX, lineBuffer);
        memOffset += sizeX;
        CS_LAT_BIT = 0;
        for(stretchY = 0; stretchY<stretch; stretchY++){

            pData = lineBuffer;
            SetAddress(address.v[2],address.v[1],address.v[0]);

            for(x=0; x<sizeX; x++){

                temp = *pData++;
                SetColor(pallete[temp]);                    

                // Write pixel to screen       
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }
           }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
        CS_LAT_BIT = 1;
    }
}

/*********************************************************************
* Function: void PutImage16BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch)
*
* PreCondition: none
*
* Input: left,top - left top image corner, bitmap - image pointer,
*        stretch - image stretch factor
*
* Output: none
*
* Side Effects: none
*
* Overview: outputs monochrome image starting from left,top coordinates
*
* Note: image must be located in external memory
*
********************************************************************/
void PutImage16BPPExt(SHORT left, SHORT top, void* bitmap, BYTE stretch){
register DWORD_VAL  address;
register DWORD      memOffset;
BITMAP_HEADER       bmp;
WORD                lineBuffer[SCREEN_HOR_SIZE];
WORD*               pData; 
WORD                byteWidth;

WORD                temp;
WORD                sizeX, sizeY;
WORD                x,y;
BYTE                stretchX, stretchY;

    // Set start address
#ifdef USE_PORTRAIT
    address.Val = (long)LINE_MEM_PITCH*top + left;
#else
    address.Val = (long)LINE_MEM_PITCH*left+ top;
#endif

    // Get bitmap header
    ExternalMemoryCallback(bitmap, 0, sizeof(BITMAP_HEADER), &bmp);

    // Set offset to the image data
    memOffset = sizeof(BITMAP_HEADER);

    // Get size
    sizeX = bmp.width;
    sizeY = bmp.height;

    byteWidth = sizeX<<1;

    for(y=0; y<sizeY; y++){

        // Get line
        ExternalMemoryCallback(bitmap, memOffset, byteWidth, lineBuffer);
        memOffset += byteWidth;
        CS_LAT_BIT = 0;
        for(stretchY = 0; stretchY<stretch; stretchY++){

            pData = lineBuffer;
            SetAddress(address.v[2],address.v[1],address.v[0]);

            for(x=0; x<sizeX; x++){

                temp = *pData++;
                SetColor(temp);                    

                // Write pixel to screen       
                for(stretchX=0; stretchX<stretch; stretchX++){
                    WriteData(_color.v[1],_color.v[0]);
                }

           }
#ifdef USE_PORTRAIT
		   address.Val += LINE_MEM_PITCH; 
#else
           address.Val -= 1;
#endif
        }
        CS_LAT_BIT = 1;
    }
}
#endif
