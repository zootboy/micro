/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    hiduser.h
 * Purpose: HID Custom User Definitions
 * Version: V1.20
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

#ifndef __HIDUSER_H__
#define __HIDUSER_H__


/* HID Number of Reports */
#define HID_REPORT_NUM      1

/* HID In/Out Endpoint Address */
#define HID_EP_IN       0x81

/* HID Global Variables */
extern U8   HID_Protocol;
extern U8   HID_IdleTime[HID_REPORT_NUM];

/* HID Requests Callback Functions */
extern BOOL HID_GetReport   (void);
extern BOOL HID_SetReport   (void);
extern BOOL HID_GetIdle     (void);
extern BOOL HID_SetIdle     (void);
extern BOOL HID_GetProtocol (void);
extern BOOL HID_SetProtocol (void);


#endif  /* __HIDUSER_H__ */
