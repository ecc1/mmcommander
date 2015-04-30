// Common USB Registers

SFRX(USBADDR,  0xDE00); // Function Address
SFRX(USBPOW,   0xDE01); // Power/Control Register
SFRX(USBIIF,   0xDE02); // IN Endpoints and EP0 Interrupt Flags
SFRX(USBOIF,   0xDE04); // OUT Endpoints Interrupt Flags
SFRX(USBCIF,   0xDE06); // Common USB Interrupt Flags
SFRX(USBIIE,   0xDE07); // IN Endpoints and EP0 Interrupt Enable Mask
SFRX(USBOIE,   0xDE09); // Out Endpoints Interrupt Enable Mask
SFRX(USBCIE,   0xDE0B); // Common USB Interrupt Enable Mask
SFRX(USBFRML,  0xDE0C); // Current Frame Number (Low byte)
SFRX(USBFRMH,  0xDE0D); // Current Frame Number (High byte)
SFRX(USBINDEX, 0xDE0E); // Selects current endpoint.

// Indexed Endpoint Registers

SFRX(USBMAXI, 0xDE10); // Max. packet size for IN endpoint
SFRX(USBCS0,  0xDE11); // EP0 Control and Status (USBINDEX = 0)
SFRX(USBCSIL, 0xDE11); // IN EP{1-5} Control and Status Low
SFRX(USBCSIH, 0xDE12); // IN EP{1-5} Control and Status High
SFRX(USBMAXO, 0xDE13); // Max. packet size for OUT endpoint
SFRX(USBCSOL, 0xDE14); // OUT EP{1-5} Control and Status Low
SFRX(USBCSOH, 0xDE15); // OUT EP{1-5} Control and Status High
SFRX(USBCNT0, 0xDE16); // Number of received bytes in EP0 FIFO (USBINDEX = 0)
SFRX(USBCNTL, 0xDE16); // Number of bytes in OUT FIFO Low
SFRX(USBCNTH, 0xDE17); // Number of bytes in OUT FIFO High

// Endpoint FIFO Registers

SFRX(USBF0, 0xDE20); //  Endpoint 0 FIFO
SFRX(USBF1, 0xDE22); //  Endpoint 1 FIFO
SFRX(USBF2, 0xDE24); //  Endpoint 2 FIFO
SFRX(USBF3, 0xDE26); //  Endpoint 3 FIFO
SFRX(USBF4, 0xDE28); //  Endpoint 4 FIFO
SFRX(USBF5, 0xDE2A); //  Endpoint 5 FIFO
