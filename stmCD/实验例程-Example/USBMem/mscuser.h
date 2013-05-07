/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    mscuser.h
 * Purpose: Mass Storage Class Custom User Definitions
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

#ifndef __MSCUSER_H__
#define __MSCUSER_H__


/* Mass Storage Memory Layout */
#define MSC_MemorySize  16384            /* = 0x4000 */
#define MSC_BlockSize   512
#define MSC_BlockCount  (MSC_MemorySize / MSC_BlockSize)


/* Max In/Out Packet Size */
#define MSC_MAX_PACKET  64

/* MSC In/Out Endpoint Address */
#define MSC_EP_IN       0x82
#define MSC_EP_OUT      0x02

/* MSC Requests Callback Functions */
extern BOOL MSC_Reset     (void);
extern BOOL MSC_GetMaxLUN (void);

/* MSC Bulk Callback Functions */
extern void MSC_GetCBW (void);
extern void MSC_SetCSW (void);
extern void MSC_BulkIn (void);
extern void MSC_BulkOut(void);


#endif  /* __MSCUSER_H__ */
