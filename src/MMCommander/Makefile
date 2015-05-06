CC = sdcc
CPP = sdcpp
AS = sdas8051

DEFINES = -Dchip=1111
INCLUDES = -I. -Iusb/others -Iusb/class_cdc -Iusb/library -Imisc
CODEFLAGS = --model-small --opt-code-speed --stack-auto
CFLAGS = $(DEFINES) $(INCLUDES) $(CODEFLAGS) -Wp,-Wall,-MD,$(@:%.rel=%.d),-MT,$@
CPPFLAGS = $(DEFINES) $(INCLUDES) -P -Wall -MD $(@:%.asm=%.d) -MT $@
ASFLAGS = -l -o
LDFLAGS = --out-fmt-ihx \
	  --code-loc 0x000 --code-size 0x8000 \
	  --xram-loc 0xF000 --xram-size 0xF00 \
	  --iram-size 0x100

PROGRAMS = MMCommander serialtest delaytest usbtest

LIBRARY = modules.lib

CFILES = \
	crc_4b6b.c \
	init.c \
	interrupts.c \
	medtronicRF.c \
	txFilter.c \
	misc/delay.c \
	misc/led.c \
	misc/serial.c \
	usb/class_cdc/usb_cdc_hooks.c \
	usb/class_cdc/usb_firmware_library_config.c \
	usb/class_cdc/usb_uart.c \
	usb/library/usb_descriptor_parser.c \
	usb/library/usb_framework.c \
	usb/library/usb_interrupt.c \
	usb/library/usb_standard_requests.c \
	usb/library/usb_suspend.c \
	usb/others/clock.c \
	usb/others/hal_int.c \
	usb/others/hal_mcu.c \
	usb/others/hal_uart_usb.c \
	usb/others/util_buffer.c \
	# end of list

SFILES = usb/class_cdc/usb_cdc_descriptor.s

# Disable some warnings

# unreachable code (constants used for conditional compilation)
init.rel txFilter.rel: CFLAGS += --disable-warning 126

# unreferenced function arguments
usb/class_cdc/usb_cdc_hooks.rel usb/others/hal_led.rel usb/others/hal_mcu.rel usb/others/hal_uart_cc8051.rel usb/others/hal_uart_usb.rel: CFLAGS += --disable-warning 85

# control flow changed by optimizer
usb/library/usb_framework.rel usb/others/hal_mcu.rel: CFLAGS += --disable-warning 110

all: $(PROGRAMS:%=%.hex)

OBJS = $(CFILES:%.c=%.rel) $(SFILES:%.s=%.rel)

$(LIBRARY): $(OBJS)
	sdcclib $@ $(OBJS)

%.hex: %.rel $(LIBRARY)
ifdef VERBOSE
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBRARY)
else
	@echo LD $@ && $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBRARY)
endif

%.rel: %.c
ifdef VERBOSE
	$(CC) -c $(CFLAGS) -o $@ $<
else
	@echo CC $< && $(CC) -c $(CFLAGS) -o $@ $<
endif

# Keep .asm files created by preprocessing .s files
.SECONDARY: $(SFILES:%.s=%.asm)

%.asm: %.s
ifdef VERBOSE
	$(CPP) $(CPPFLAGS) -o $@ $<
else
	@echo CPP $< && $(CPP) $(CPPFLAGS) -o $@ $<
endif

%.rel: %.asm
ifdef VERBOSE
	$(AS) $(ASFLAGS) $<
else
	@echo AS $< && $(AS) $(ASFLAGS) $<
endif

BYPRODUCTS = *.asm *.d *.lnk *.lst *.map *.mem *.rel *.rst *.sym *~

clean:
	@for dir in $(sort $(dir $(PROGRAMS) $(OBJS))); do \
	    echo Cleaning  $$dir; \
	    (cd $$dir && rm -f $(if $(VERBOSE),-v) $(BYPRODUCTS)); \
	done

DEPS = $(PROGRAMS:%=%.d) $(CFILES:%.c=%.d) $(SFILES:%.s=%.d)

-include $(DEPS)
