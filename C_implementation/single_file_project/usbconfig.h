/* Name: usbconfig.h
 * Project: V-USB, virtual USB port for Atmel's(r) AVR(r) microcontrollers
 * Author: Christian Starkjohann
 * Creation Date: 2005-04-01
 * Tabsize: 4
 * Copyright: (c) 2005 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
 * This Revision: $Id: usbconfig-prototype.h 767 2009-08-22 11:39:22Z cs $
 */

#ifndef __usbconfig_h_included__
#define __usbconfig_h_included__

/* ---------------------------- Hardware Config ---------------------------- */

#define USB_CFG_IOPORTNAME      B
#define USB_CFG_DMINUS_BIT      3   // PB3 for D-
#define USB_CFG_DPLUS_BIT       4   // PB4 for D+

#define USB_CFG_CLOCK_KHZ       16000  // Assuming 16 MHz clock
#define USB_CFG_CHECK_CRC       0      // Disable CRC check for simplicity

/* ----------------------- Optional Hardware Config ------------------------ */

//#define USB_CFG_PULLUP_IOPORTNAME   D
//#define USB_CFG_PULLUP_BIT          5

/* --------------------------- Functional Range ---------------------------- */

#define USB_CFG_HAVE_INTRIN_ENDPOINT    0  // No interrupt endpoint needed
#define USB_CFG_HAVE_INTRIN_ENDPOINT3   0
#define USB_CFG_EP3_NUMBER              3

#define USB_CFG_IMPLEMENT_HALT          0
#define USB_CFG_SUPPRESS_INTR_CODE      0
#define USB_CFG_INTR_POLL_INTERVAL      10

#define USB_CFG_IS_SELF_POWERED         0
#define USB_CFG_MAX_BUS_POWER           100

#define USB_CFG_IMPLEMENT_FN_WRITE      0
#define USB_CFG_IMPLEMENT_FN_READ       0
#define USB_CFG_IMPLEMENT_FN_WRITEOUT   0

#define USB_CFG_HAVE_FLOWCONTROL        0
#define USB_CFG_LONG_TRANSFERS          0

#define USB_COUNT_SOF                   0
#define USB_CFG_CHECK_DATA_TOGGLING     0

/* -------------------------- Device Description --------------------------- */

#define USB_CFG_VENDOR_ID 0x03, 0x04   // Example shared VID/PID pair
#define USB_CFG_DEVICE_ID 0x0c, 0x05   // Example shared VID/PID pair
#define USB_CFG_DEVICE_VERSION  0x00, 0x01

#define USB_CFG_VENDOR_NAME     'd','i','g','i','s','t','u','m','p','.','c','o','m'
#define USB_CFG_VENDOR_NAME_LEN 13

#define USB_CFG_DEVICE_NAME     'D','i','g','i','K','e','y'
#define USB_CFG_DEVICE_NAME_LEN 7

/* ------------------- Fine Control over USB Descriptors ------------------- */

#define USB_CFG_DESCR_PROPS_DEVICE                  0
#define USB_CFG_DESCR_PROPS_CONFIGURATION           0
#define USB_CFG_DESCR_PROPS_STRINGS                 0
#define USB_CFG_DESCR_PROPS_STRING_0                0
#define USB_CFG_DESCR_PROPS_STRING_VENDOR           0
#define USB_CFG_DESCR_PROPS_STRING_PRODUCT          0
#define USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER    0
#define USB_CFG_DESCR_PROPS_HID                     0
#define USB_CFG_DESCR_PROPS_HID_REPORT              0
#define USB_CFG_DESCR_PROPS_UNKNOWN                 0

/* ----------------------- Optional MCU Description ------------------------ */

// Configure interrupt handling for ATtiny85
#define USB_INTR_CFG            PCMSK
#define USB_INTR_CFG_SET        (1 << USB_CFG_DPLUS_BIT)
#define USB_INTR_ENABLE_BIT     PCIE
#define USB_INTR_PENDING_BIT    PCIF
#define USB_INTR_VECTOR         SIG_PIN_CHANGE

#endif /* __usbconfig_h_included__ */
