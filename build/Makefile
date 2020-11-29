#***********************************************************************************************
#    File        : Makefile
#    Author      : Lyu Yang
#    Date        : 2020-04-30
#    Description : Makefile for STM32F4
#***********************************************************************************************
TRX_ID=mchf
TRX_NAME='MCHF QRP'
FIRMWARE=fw-$(TRX_ID)
BOOTLOADER=bl-$(TRX_ID)

CROSS_COMPILE = arm-none-eabi-
SRC_DIR = ..
OBJ_DIR = obj

CC = $(CROSS_COMPILE)gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -flto -ffunction-sections -fdata-sections -Wall -Wuninitialized -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -DARM_MATH_CM4 -DCORTEX_M4 -DSTM32F407xx -D__FPU_PRESENT=1U -DUI_BRD_MCHF -DRF_BRD_MCHF -DNDEBUG -D_GNU_SOURCE -DTRX_ID=\"$(TRX_ID)\" -DTRX_NAME=\"$(TRX_NAME)\" -DUSE_HAL_DRIVER -DFDV_ARM_MATH -DFREEDV_MODE_EN_DEFAULT=0 -DFREEDV_MODE_1600_EN=1 -DCODEC2_MODE_EN_DEFAULT=0 -DCODEC2_MODE_1300_EN=1

CXX = $(CROSS_COMPILE)g++
CXXFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -flto -ffunction-sections -fdata-sections -Wall -Wuninitialized -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -DARM_MATH_CM4 -DCORTEX_M4 -DSTM32F407xx -D__FPU_PRESENT=1U -DUI_BRD_MCHF -DRF_BRD_MCHF -DNDEBUG -D_GNU_SOURCE -DTRX_ID=\"$(TRX_ID)\" -DTRX_NAME=\"$(TRX_NAME)\" -DUSE_HAL_DRIVER -DFDV_ARM_MATH -DFREEDV_MODE_EN_DEFAULT=0 -DFREEDV_MODE_1600_EN=1 -DCODEC2_MODE_EN_DEFAULT=0 -DCODEC2_MODE_1300_EN=1

AS = $(CROSS_COMPILE)gcc
ASFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -x assembler-with-cpp -Wall -ffunction-sections -fdata-sections

LD = $(CROSS_COMPILE)g++
LDFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=gnu11 -flto -ffunction-sections -fdata-sections -Xlinker --gc-sections --specs=nosys.specs --specs=nano.specs

OBJCP = $(CROSS_COMPILE)objcopy

AR = $(CROSS_COMPILE)ar
ARFLAGS = cr

OBJDUMP = $(CROSS_COMPILE)objdump
OBJDUMPFLAG = --disassemble --syms --all-header

SIZE = $(CROSS_COMPILE)size

$(FIRMWARE).elf   : CFLAGS  += -O2
$(FIRMWARE).elf   : LDFLAGS += -T./stm32f4xx_firmware.ld
$(BOOTLOADER).elf : CFLAGS  += -Os -DBOOTLOADER_BUILD
$(BOOTLOADER).elf : LDFLAGS += -T./stm32f4xx_bootloader.ld

# Propagate version info from source to environment variables
PROJECT_VERSION_FILE := ../src/uhsdr_version.h
$(eval $(shell sed -n -e 's/"//g' -e '/UHSDR_VER_MAJOR/{s!#define\s*!!;   s!\s\s*!=!p}' $(PROJECT_VERSION_FILE) ))
$(eval $(shell sed -n -e 's/"//g' -e '/UHSDR_VER_MINOR/{s!#define\s*!!;   s!\s\s*!=!p}' $(PROJECT_VERSION_FILE) ))
$(eval $(shell sed -n -e 's/"//g' -e '/UHSDR_VER_RELEASE/{s!#define\s*!!; s!\s\s*!=!p}' $(PROJECT_VERSION_FILE) ))

#---------------------------------------------------------------------------------------------------
include ./common.mk

INC_DIR     := $(foreach d, $(SRC_INC_DIR) $(HAL_INC_DIR), -I$d)
FW_OBJS     := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
HAL_OBJS    := $(patsubst $(SRC_DIR)/%.S,$(OBJ_DIR)/%.o,$(HAL_ASMS))
HAL_OBJS    += $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(HAL_SRCS))
DSP_OBJS    := $(patsubst $(SRC_DIR)/%.S,$(OBJ_DIR)/%.o,$(DSPLIB_ASMS))
DSP_OBJS    += $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(DSPLIB_SRCS))
BL_OBJS     := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BL_SRCS))
BL_HAL_OBJS := $(patsubst $(SRC_DIR)/%.S,$(OBJ_DIR)/%.o,$(BL_HAL_ASMS))
BL_HAL_OBJS += $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BL_HAL_SRCS))

$(DSP_OBJS): CFLAGS += -Wno-strict-aliasing
$(OBJ_DIR)/basesw/%/usbh_mtp.o: CFLAGS += -Wno-implicit-fallthrough
$(OBJ_DIR)/basesw/%/usbh_msc.o: CFLAGS += -Wno-implicit-fallthrough
$(OBJ_DIR)/basesw/%stm32f4xx_ll_usb.o: CFLAGS += -Wno-attributes
$(OBJ_DIR)/drivers/usb/%/usbh_hid.o: CFLAGS += -Wno-implicit-fallthrough

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(shell dirname $@)
	@$(AS) $(INC_DIR) $(ASFLAGS) -c $< -o $@
	@echo AS $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(INC_DIR) $(CFLAGS) -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	@$(CC) $(INC_DIR) $(CFLAGS) -c $< -o $@
	@echo CC $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(shell dirname $@)
	@$(CXX) $(INC_DIR) $(CXXFLAGS) -MM -MT $@ -MF $(patsubst %.o, %.d, $@) $<
	@$(CXX) $(INC_DIR) $(CXXFLAGS) -c $< -o $@
	@echo CC $<

%.bin: %.elf
	@$(OBJCP) -O binary $< $@

%.hex: %.elf
	@$(OBJCP) -O ihex $< $@

%.dfu: %.hex
	@python3 ../scripts/hex2dfu/hex2dfu.py $< $@

#---------------------------------------------------------------------------------------------------
.PHONY: firmware bootloader clean

firmware: $(FIRMWARE)
bootloader: $(BOOTLOADER)

$(FIRMWARE): $(FIRMWARE).elf $(FIRMWARE).dfu $(FIRMWARE).bin
$(BOOTLOADER): $(BOOTLOADER).bin $(BOOTLOADER).dfu

$(FIRMWARE).elf: $(HAL_OBJS) $(DSP_OBJS) $(FW_OBJS)
	@$(LD) $(LDFLAGS) -Wl,-Map,$(FIRMWARE).map -o $@ $^
	@$(SIZE) $@

$(BOOTLOADER).elf: $(BL_HAL_OBJS) $(BL_OBJS)
	@$(LD) $(LDFLAGS) -Wl,-Map,$(BOOTLOADER).map -o $@ $^
	@$(SIZE) $@

dfu-bl:
	@dfu-util -d -R -a 0 0483:df11 -D $(BOOTLOADER).dfu

dfu-fw:
	@dfu-util -d -R -a 0 0483:df11 -D $(FIRMWARE).dfu

clean:
	@rm -rf obj
	@rm -rf $(FIRMWARE).elf
	@rm -rf $(FIRMWARE).dfu
	@rm -rf $(FIRMWARE).bin
	@rm -rf $(FIRMWARE).map
	@rm -rf $(BOOTLOADER).elf
	@rm -rf $(BOOTLOADER).dfu
	@rm -rf $(BOOTLOADER).bin
	@rm -rf $(BOOTLOADER).map

