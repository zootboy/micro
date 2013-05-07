/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbdesc.h
 * Purpose: USB Descriptors Definitions
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

#ifndef __USBDESC_H__
#define __USBDESC_H__


#define WBVAL(x) (x & 0xFF),((x >> 8) & 0xFF)

#define USB_DEVICE_DESC_SIZE        (sizeof(USB_DEVICE_DESCRIPTOR))
#define USB_CONFIGUARTION_DESC_SIZE (sizeof(USB_CONFIGURATION_DESCRIPTOR))
#define USB_INTERFACE_DESC_SIZE     (sizeof(USB_INTERFACE_DESCRIPTOR))
#define USB_ENDPOINT_DESC_SIZE      (sizeof(USB_ENDPOINT_DESCRIPTOR))

#define HID_DESC_OFFSET              0x0012
#define HID_DESC_SIZE               (sizeof(HID_DESCRIPTOR))
#define HID_REPORT_DESC_SIZE        (sizeof(HID_ReportDescriptor))

extern const U8  USB_DeviceDescriptor[];
extern const U8  USB_ConfigDescriptor[];
extern const U8  USB_StringDescriptor[];

extern const U8  HID_ReportDescriptor[];
extern const U16 HID_ReportDescSize;


#endif  /* __USBDESC_H__ */
