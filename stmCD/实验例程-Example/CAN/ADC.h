/*----------------------------------------------------------------------------
 * Name:    ADC.h
 * Purpose: MCB1700 low level ADC definitions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __ADC_H
#define __ADC_H

#define ADC_VALUE_MAX 0xFFF


extern void     ADC_init    (void);
extern void     ADC_startCnv(void);
extern void     ADC_stopCnv (void);
extern uint32_t ADC_getCnv  (void);

#endif
