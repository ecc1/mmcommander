#include "usb_descriptor.h"
#include "usb_cdc.h"
#include "configuration.h"

__code struct usb_descriptor usbDesc = {
    // device descriptor
    {
        sizeof(USB_DEVICE_DESCRIPTOR),
        DESC_TYPE_DEVICE,
        0x0200,  // USB spec in BCD
        CDC_DEVICE,
        0,
        0,
        EP0_PACKET_SIZE,
        0x0451,  // vendor: Texas Instruments
        0x16A6,  // product: CC1111
        0x0009,  // release number in BCD
        1,  // index of manufacturer string
        2,  // index of product string
        3,  // index of serial number string
        1,  // number of configurations
    },

    // configuration descriptor
    {
        sizeof(USB_CONFIGURATION_DESCRIPTOR),
        DESC_TYPE_CONFIG,
        sizeof(struct usb_descriptor) - sizeof(USB_DEVICE_DESCRIPTOR),
        2,  // number of interfaces
        1,  // configuration value
        0,  // index of descriptor string
        1 << 7,  // bmAttributes
        25,  // max power
    },

    // interface descriptor
    {
        sizeof(USB_INTERFACE_DESCRIPTOR),
        DESC_TYPE_INTERFACE,
        CDC_COMM_INTF_ID,
        0,  // alternate setting
        1,  // number of endpoints
        COMM_INTF,  // interface class
        ABSTRACT_CONTROL_MODEL,  // interface subclass
        V25TER,  // interface protocol
        0,  // index of descriptor string
    },

    // CDC class-specific descriptors
    {
        // Header Functional Descriptor
        5, CS_INTERFACE,
        DSC_FN_HEADER,
        0x10, 0x1,  // CDC version 1.10 in BCD

        // Abstract Control Management Functional Descriptor
        4, CS_INTERFACE,
        DSC_FN_ACM,
        2,  // supported class requests

        // Union Interface Functional Descriptor
        5, CS_INTERFACE,
        DSC_FN_UNION,
        CDC_COMM_INTF_ID,
        CDC_DATA_INTF_ID,

        // Call Management Functional Descriptor
        5, CS_INTERFACE,
        DSC_FN_CALL_MGT,
        0,  // does not handle call management
        CDC_DATA_INTF_ID,
    },

    // endpoint descriptor
    {
        sizeof(USB_ENDPOINT_DESCRIPTOR),
        DESC_TYPE_ENDPOINT,
        (1 << 7) | 1,  // endpoint address: IN + CDC notification endpoint
        EP_ATTR_INT,  // bmAttributes
        EP0_PACKET_SIZE,  // max packet size
        32,  // interval
    },

    // interface descriptor
    {
        sizeof(USB_INTERFACE_DESCRIPTOR),
        DESC_TYPE_INTERFACE,
        CDC_DATA_INTF_ID,
        0,  // alternate setting
        2,  // number of endpoints
        DATA_INTF,  // interface class
        0,  // interface subclass
        NO_PROTOCOL,  // interface protocol
        0,  // index of descriptor string
    },

    // endpoint descriptor
    {
        sizeof(USB_ENDPOINT_DESCRIPTOR),
        DESC_TYPE_ENDPOINT,
        (1 << 7) | 4,  // endpoint address: IN + CDC data endpoint
        EP_ATTR_BULK,  // bmAttributes
        32,  // max packet size
        1,  // interval
    },

    // endpoint descriptor
    {
        sizeof(USB_ENDPOINT_DESCRIPTOR),
        DESC_TYPE_ENDPOINT,
        (0 << 7) | 4,  // endpoint address: OUT + CDC data endpoint
        EP_ATTR_BULK,  // bmAttributes
        32,  // max packet size
        1,  // interval
    },

    // string descriptors
    {
        // index 0: language ID
        4, DESC_TYPE_STRING,
        9, 4,  // US-EN

        // index 1: manufacturer
        22, DESC_TYPE_STRING,
        'N', 0,
        'i', 0,
        'g', 0,
        'h', 0,
        't', 0,
        's', 0,
        'c', 0,
        'o', 0,
        'u', 0,
        't', 0,

        // index 2: product
        24, DESC_TYPE_STRING,
        'M', 0,
        'M', 0,
        'C', 0,
        'o', 0,
        'm', 0,
        'm', 0,
        'a', 0,
        'n', 0,
        'd', 0,
        'e', 0,
        'r', 0,

        // index 3: serial number
        8, DESC_TYPE_STRING,
#if _MMCOMMANDER_VERSION_ > 999
#error Version number is too big -- fix me!
#endif
        '0' + _MMCOMMANDER_VERSION_ / 100, 0,
        '0' + (_MMCOMMANDER_VERSION_ % 100) / 10, 0,
        '0' + (_MMCOMMANDER_VERSION_ % 10), 0,
    },
};

__code DBLBUF_LUT_INFO usbDblbufLut[] = {
    {
        &usbDesc.interface0,
        0,  // bitmask for IN endpoints
        0,  // bitmask for OUT endpoints
    },
    {
        &usbDesc.interface1,
        0,  // bitmask for IN endpoints
        0,  // bitmask for OUT endpoints
    },
};
