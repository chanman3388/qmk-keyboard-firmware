# Build Options
#   change yes to no to disable
#
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
CUSTOM_MATRIX = lite
NO_USB_STARTUP_CHECK = yes
LTO_ENABLE = no

SRC += matrix.c
I2C_DRIVER_REQUIRED = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = pimoroni_trackball
PIMORONI_TRACKBALL_ADDRESS = 0x0A
TRI_LAYER_ENABLE = yes
