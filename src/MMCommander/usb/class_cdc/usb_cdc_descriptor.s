/***********************************************************************************

    Filename:	  usb_cdc_descriptor.s

    Description:  Descriptor for USB CDC class.

***********************************************************************************/
/*
+------------------------------------------------------------------------------
|The default USB descriptor defines a minimum configuration, with no endpoints
|apart from EP0. The application can define 3 IN and OUT endpoints, and override
|the configuration and interface descriptor (only one of each).
|The device and string descriptors are locked.
+------------------------------------------------------------------------------*/


#define ASM_FILE
#include "usb_descriptor.h"
#include "usb_cdc.h"

		.module	 usb_descriptor

		.globl _usbDescStart
		.globl _usbDescEnd
		.globl _usbDescLut
		.globl _usbDescLutEnd
		.globl _usbDblbufLut
		.globl _usbDblbufLutEnd

		.area CONST (CODE)
;; USB descriptors
_usbDescStart:
deviceDesc:	; Device descriptor
		.db deviceDescEnd - deviceDesc
		.db DESC_TYPE_DEVICE	; bDescriptorType
		.db 0x00, 0x02		; bcdUSB
		.db CDC_DEVICE		; bDeviceClass
		.db 0x00		; bDeviceSubClass
		.db 0x00		; bDeviceProtocol
		.db EP0_PACKET_SIZE
		.db 0x51, 0x04		; idVendor Texas Instruments
		#if (chip==2531)
		.db 0xA8, 0x16		; idProduct CC2531
		#elif (chip==2511)
		.db 0xA4, 0x16		; idProduct CC2511
		#else
		.db 0xA6, 0x16		; idProduct CC1111
		#endif
		.db 0x09, 0x00		; bcdDevice
		.db 0x01		; iManufacturer
		.db 0x02		; iProduct
		.db 0x03		; iSerialNumber
		.db 0x01		; bNumConfigurations
deviceDescEnd:

config1LengthStart:
configDesc:	; Configuration descriptor
		.db configDescEnd - configDesc
		.db DESC_TYPE_CONFIG	; bDescriptorType
		.db config1LengthEnd - config1LengthStart, 0x00
		.db 0x02		; NumInterfaces
		.db 0x01		; bConfigurationValue
		.db 0x00		; iConfiguration
		.db 0x80		; bmAttributes
		.db 25			; MaxPower
configDescEnd:


;
;		INTERFACE 0
;


interface0Desc: ; Interface descriptor
		.db interface0DescEnd - interface0Desc
		.db DESC_TYPE_INTERFACE	   ; bDescriptorType
		.db 0x00		   ; bInterfaceNumber
		.db 0x00		   ; bAlternateSetting
		.db 0x01		   ; bNumEndpoints
		.db COMM_INTF		   ; bInterfaceClass
		.db ABSTRACT_CONTROL_MODEL ; bInterfaceSubClass
		.db V25TER		   ; bInterfaceProcotol
		.db 0x00		   ; iInterface
interface0DescEnd:

;; CDC Class-Specific Descriptors

headerFunctionalDesc: ; Header Functional Descriptor
		.db headerFunctionalDescEnd - headerFunctionalDesc
		.db CS_INTERFACE
		.db DSC_FN_HEADER
		.db 0x10, 0x01
headerFunctionalDescEnd:


absCtrlManFuncDesc: ; Abstract Control Management Functional Descriptor
		.db absCtrlManFuncDescEnd - absCtrlManFuncDesc
		.db CS_INTERFACE
		.db DSC_FN_ACM
		.db 0x02   ;set the supported class requests
absCtrlManFuncDescEnd:

unionFunctionalDesc: ; Union Functional Descriptor
		.db unionFunctionalDescEnd - unionFunctionalDesc
		.db CS_INTERFACE
		.db DSC_FN_UNION
		.db CDC_COMM_INTF_ID
		.db CDC_DATA_INTF_ID
unionFunctionalDescEnd:


callMngFuncDesc: ; Call Management Functional Descriptor
		.db callMngFuncDescEnd - callMngFuncDesc
		.db CS_INTERFACE
		.db DSC_FN_CALL_MGT
		.db 0x00
		.db CDC_DATA_INTF_ID
callMngFuncDescEnd:



endpoint0Desc:	; Endpoint descriptor (EP2 IN)
		.db endpoint0DescEnd - endpoint0Desc
		.db DESC_TYPE_ENDPOINT	; bDescriptorType
		.db 0x82		; bEndpointAddress
		.db EP_ATTR_INT		; bmAttributes
		.db 0x40, 0x00		; wMaxPacketSize
		.db 0x40		; bInterval
endpoint0DescEnd:

;
;		INTERFACE 1
;

interface1Desc: ; Interface descriptor
		.db interface1DescEnd - interface1Desc
		.db DESC_TYPE_INTERFACE ; Interface descriptor type
		.db 0x01		; Interface Number
		.db 0x00		; Alternate Setting Number
		.db 0x02		; Number of endpoints in this intf
		.db DATA_INTF		; Class code
		.db 0x00		; Subclass code
		.db NO_PROTOCOL		; Protocol code
		.db 0x00		; Interface string index
interface1DescEnd:


endpoint1Desc:	; Endpoint descriptor (EP4 OUT)
		.db endpoint1DescEnd - endpoint1Desc
		.db DESC_TYPE_ENDPOINT	; bDescriptorType
		.db 0x84		; bEndpointAddress
		.db EP_ATTR_BULK	; bmAttributes
		.db 0x40, 0x00		; wMaxPacketSize
		.db 0x01		; bInterval
endpoint1DescEnd:

endpoint2Desc:	; Endpoint descriptor (EP4 IN)
		.db endpoint2DescEnd - endpoint2Desc
		.db DESC_TYPE_ENDPOINT	; bDescriptorType
		.db 0x04		; bEndpointAddress
		.db EP_ATTR_BULK	; bmAttributes
		.db 0x40, 0x00		; wMaxPacketSize
		.db 0x01		; bInterval
endpoint2DescEnd:
config1LengthEnd:
;;-------------------------------------------------------------------------------------------------------


;;-------------------------------------------------------------------------------------------------------
;; String descriptors
string0Desc:	; Language ID
		.db string0DescEnd - string0Desc
		.db DESC_TYPE_STRING	; bDescriptorType
		.db 0x09		; US-EN
		.db 0x04
string0DescEnd:

string1Desc:	; Manufacturer
		.db string1DescEnd - string1Desc
		.db DESC_TYPE_STRING	; bDescriptorType
		.ascii "N\0i\0g\0h\0t\0s\0c\0o\0u\0t\0"
string1DescEnd:

string2Desc:	; Product
		.db string2DescEnd - string2Desc
		.db DESC_TYPE_STRING	; bDescriptorType
		.ascii "M\0\M\0C\0o\0m\0m\0a\0n\0d\0e\0r\0"
string2DescEnd:

string3Desc:	; Serial number
		.db string3DescEnd - string3Desc
		.db DESC_TYPE_STRING	; bDescriptorType
		.ascii "0\0"
		.ascii "0\0"
		.ascii "1\0"
string3DescEnd:

_usbDescEnd:
;;-------------------------------------------------------------------------------------------------------


;;-------------------------------------------------------------------------------------------------------
;; Look-up table for descriptors that are not returned through requests for DSC_DEVICE, DSC_CONFIG or
;; DSC_STRING (e.g. HID report descriptors)
_usbDescLut:
_usbDescLutEnd:
;;-------------------------------------------------------------------------------------------------------


;;-------------------------------------------------------------------------------------------------------
;; Look-up table for double buffer settings (one set of bit masks for each defined interface)
_usbDblbufLut:	.dw interface0Desc	; pInterface
		.db 0x00		; inMask
		.db 0x00		; outMask
		.dw interface1Desc	; pInterface
		.db 0x00		; inMask
		.db 0x00		; outMask
_usbDblbufLutEnd:
;;-------------------------------------------------------------------------------------------------------


/*
+------------------------------------------------------------------------------
|  Copyright 2004-2007 Texas Instruments Incorporated. All rights reserved.
|
|  IMPORTANT: Your use of this Software is limited to those specific rights
|  granted under the terms of a software license agreement between the user who
|  downloaded the software, his/her employer (which must be your employer) and
|  Texas Instruments Incorporated (the "License"). You may not use this Software
|  unless you agree to abide by the terms of the License. The License limits
|  your use, and you acknowledge, that the Software may not be modified, copied
|  or distributed unless embedded on a Texas Instruments microcontroller or used
|  solely and exclusively in conjunction with a Texas Instruments radio
|  frequency transceiver, which is integrated into your product. Other than for
|  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
|  works of, modify, distribute, perform, display or sell this Software and/or
|  its documentation for any purpose.
|
|  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
|  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
|  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
|  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
|  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
|  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
|  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING
|  BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
|  CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
|  SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
|  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
|
|  Should you have any questions regarding your right to use this Software,
|  contact Texas Instruments Incorporated at www.TI.com.
|
*/
