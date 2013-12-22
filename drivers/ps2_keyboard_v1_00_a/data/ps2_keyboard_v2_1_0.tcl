##############################################################################
## Filename:          C:\Users\superman\Desktop\DerekLab7/drivers/ps2_keyboard_v1_00_a/data/ps2_keyboard_v2_1_0.tcl
## Description:       Microprocess Driver Command (tcl)
## Date:              Sun Nov 24 14:04:04 2013 (by Create and Import Peripheral Wizard)
##############################################################################

#uses "xillib.tcl"

proc generate {drv_handle} {
  xdefine_include_file $drv_handle "xparameters.h" "ps2_keyboard" "NUM_INSTANCES" "DEVICE_ID" "C_BASEADDR" "C_HIGHADDR" 
}
