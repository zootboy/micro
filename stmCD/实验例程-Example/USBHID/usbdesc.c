/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbdesc.c
 * Purpose: USB Descriptors
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
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 Changed string descriptor handling
 *                Changed HID Report Descriptor
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbdesc.h"

#include "hid.h"

/*------------------------------------------------------------------------------
  HID Report Descriptor
 *------------------------------------------------------------------------------*/

/*   Bit    Input       Output
      0     Joystick     LED0
      1     Joystick     LED1
      2     Joystick     LED2
      3     Joystick     LED3
      4     Joystick     LED4
      5     ---          LED5
      6     ---          LED6
      7     ---          LED7
*/

#define HID_INPUT_REPORT_BYTES       1              /* size of report in Bytes */
#define HID_OUTPUT_REPORT_BYTES      1              /* size of report in Bytes */
#define HID_FEATURE_REPORT_BYTES     1              /* size of report in Bytes */

const U8 HID_ReportDescriptor[] = {
  HID_UsagePageVendor( 0x00                     ),
  HID_Usage          ( 0x01                     ),
  HID_Collection     ( HID_Application          ),
    HID_LogicalMin   ( 0                        ),  /* value range: 0 - 0xFF */
    HID_LogicalMaxS  ( 0xFF                     ),
    HID_ReportSize   ( 8                        ),  /* 8 bits */
    HID_ReportCount  ( HID_INPUT_REPORT_BYTES   ),
    HID_Usage        ( 0x01                     ),
    HID_Input        ( HID_Data | HID_Variable | HID_Absolute ),
    HID_ReportCount  ( HID_OUTPUT_REPORT_BYTES  ),
    HID_Usage        ( 0x01                     ),
    HID_Output       ( HID_Data | HID_Variable | HID_Absolute ),
    HID_ReportCount  ( HID_FEATURE_REPORT_BYTES ),
    HID_Usage        ( 0x01                     ),
    HID_Feature      ( HID_Data | HID_Variable | HID_Absolute ),
  HID_EndCollection,
};

const U16 HID_ReportDescSize = sizeof(HID_ReportDescriptor);


/* USB Standard Device Descriptor */
const U8 USB_DeviceDescriptor[] = {
  USB_DEVICE_DESC_SIZE,              /* bLength */
  USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0200), /* 2.00 */          /* bcdUSB */
  0x00,                              /* bDeviceClass */
  0x00,                              /* bDeviceSubClass */
  0x00,                              /* bDeviceProtocol */
  USB_MAX_PACKET0,                   /* bMaxPacketSize0 */
  WBVAL(0xC251),                     /* idVendor */
  WBVAL(0x2201),                     /* idProduct */
  WBVAL(0x0100), /* 1.00 */          /* bcdDevice */
  0x01,                              /* iManufacturer */
  0x02,                              /* iProduct */
  0x03,                              /* iSerialNumber */
  0x01                               /* bNumConfigurations: one possible configuration*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
const U8 USB_ConfigDescriptor[] = {
/* Configuration 1 */
  USB_CONFIGUARTION_DESC_SIZE,       /* bLength */
  USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
  WBVAL(                             /* wTotalLength */
    USB_CONFIGUARTION_DESC_SIZE +
    USB_INTERFACE_DESC_SIZE     +
    HID_DESC_SIZE               +
    USB_ENDPOINT_DESC_SIZE
  ),
  0x01,                              /* bNumInterfaces */
  0x01,                              /* bConfigurationValue: 0x01 is used to select this configuration */
  0x00,                              /* iConfiguration: no string to describe this configuration */
  USB_CONFIG_BUS_POWERED /*|*/       /* bmAttributes */
/*USB_CONFIG_REMOTE_WAKEUP*/,
  USB_CONFIG_POWER_MA(100),          /* bMaxPower, device power consumption is 100 mA */

/* Interface 0, Alternate Setting 0, HID Class */
  USB_INTERFACE_DESC_SIZE,           /* bLength */
  USB_INTERFACE_DESCRIPTOR_TYPE,     /* bDescriptorType */
  0x00,                              /* bInterfaceNumber */
  0x00,                              /* bAlternateSetting */
  0x01,                              /* bNumEndpoints */
  USB_DEVICE_CLASS_HUMAN_INTERFACE,  /* bInterfaceClass */
  HID_SUBCLASS_NONE,                 /* bInterfaceSubClass */
  HID_PROTOCOL_NONE,                 /* bInterfaceProtocol */
  0x04,                              /* iInterface */
/* HID Class Descriptor */
/* HID_DESC_OFFSET = 0x0012 */
  HID_DESC_SIZE,                     /* bLength */
  HID_HID_DESCRIPTOR_TYPE,           /* bDescriptorType */
  WBVAL(0x0100), /* 1.00 */          /* bcdHID */
  0x00,                              /* bCountryCode */
  0x01,                              /* bNumDescriptors */
  HID_REPORT_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(HID_REPORT_DESC_SIZE),       /* wDescriptorLength */
/* Endpoint, HID Interrupt In */
  USB_ENDPOINT_DESC_SIZE,            /* bLength */
  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
  USB_ENDPOINT_IN(1),                /* bEndpointAddress */
  USB_ENDPOINT_TYPE_INTERRUPT,       /* bmAttributes */
  WBVAL(0x0004),                     /* wMaxPacketSize */
  0x20,          /* 32ms */          /* bInterval */
/* Terminator */
  0                                  /* bLength */
};


/* USB String Descriptor (optional) */
const U8 USB_StringDescriptor[] = {
/* Index 0x00: LANGID Codes */
  0x04,                              /* bLength */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  WBVAL(0x0409), /* US English */    /* wLANGID */
/* Index 0x01: Manufacturer */
  (13*2 + 2),                        /* bLength (13 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'K',0,
  'e',0,
  'i',0,
  'l',0,
  ' ',0,
  'S',0,
  'o',0,
  'f',0,
  't',0,
  'w',0,
  'a',0,
  'r',0,
  'e',0,
/* Index 0x02: Product */
  (16*2 + 2),                        /* bLength (16 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'K',0,
  'e',0,
  'i',0,
  'l',0,
  ' ',0,
  'M',0,
  'C',0,
  'B',0,
  '1',0,
  '7',0,
  '0',0,
  '0',0,
  ' ',0,
  'H',0,
  'I',0,
  'D',0,
/* Index 0x03: Serial Number */
  (12*2 + 2),                        /* bLength (12 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  '0',0,                             /* allowed characters are       */
  '0',0,                             /*   0x0030 - 0x0039 ('0'..'9') */
  '0',0,                             /*   0x0041 - 0x0046 ('A'..'F') */
  '1',0,                             /*   length >= 26               */
  'A',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
  '0',0,
/* Index 0x04: Interface 0, Alternate Setting 0 */
  ( 3*2 + 2),                        /* bLength (3 Char + Type + lenght) */
  USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
  'H',0,
  'I',0,
  'D',0,
};
