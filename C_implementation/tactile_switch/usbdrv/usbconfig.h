/*
 * Name: usbconfig.h
 * Project: Hardware Login Key for ATtiny85
 * Author: Paschalis M. (configured by GitHub Copilot)
 * Creation Date: 2025-10-02
 * Tabsize: 4
 */

#ifndef __usbconfig_h_included__
#define __usbconfig_h_included__

/* ---------------------------- Hardware Config ---------------------------- */

#define USB_CFG_IOPORTNAME      B
#define USB_CFG_DMINUS_BIT      0 // D- is on PB0
#define USB_CFG_DPLUS_BIT       2 // D+ is on PB2 (INT0)
#define USB_CFG_CLOCK_KHZ       (F_CPU/1000)

/* --------------------------- Functional Range ---------------------------- */
#define USB_CFG_HAVE_INTRIN_ENDPOINT    1
#define USB_CFG_INTR_POLL_INTERVAL      10
#define USB_CFG_IS_SELF_POWERED         0
#define USB_CFG_MAX_BUS_POWER           100
#define USB_CFG_IMPLEMENT_FN_WRITE      0
#define USB_CFG_IMPLEMENT_FN_READ       0

/* -------------------------- Device Description --------------------------- */
#define  USB_CFG_VENDOR_ID       0xc0, 0x16
#define  USB_CFG_DEVICE_ID       0xdf, 0x05
#define USB_CFG_DEVICE_VERSION  0x01, 0x00
#define USB_CFG_VENDOR_NAME     'P', 'a', 's', 'c', 'h', 'a', 'l', 'i', 's'
#define USB_CFG_VENDOR_NAME_LEN 9
#define USB_CFG_DEVICE_NAME     'H', 'a', 'r', 'd', 'w', 'a', 'r', 'e', ' ', 'K', 'e', 'y'
#define USB_CFG_DEVICE_NAME_LEN 12
#define USB_CFG_DEVICE_CLASS        0
#define USB_CFG_DEVICE_SUBCLASS     0
#define USB_CFG_INTERFACE_CLASS     3
#define USB_CFG_INTERFACE_SUBCLASS  1
#define USB_CFG_INTERFACE_PROTOCOL  1
#define USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH    63

#endif /* __usbconfig_h_included__ */