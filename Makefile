#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPRO")
endif
export PATH			:=	$(DEVKITPPC)/bin:$(PORTLIBS)/bin:$(PATH)

PREFIX	:=	powerpc-eabi-

export AS		:=	$(PREFIX)as
export CC		:=	$(PREFIX)gcc
export CXX		:=	$(PREFIX)g++
export AR		:=	$(PREFIX)ar
export OBJCOPY	:=	$(PREFIX)objcopy

TARGET		:= libwiiu
BUILD		:= build
INCLUDES	:= include
SOURCE		:= src
# TODO do this automaticly?
SOURCES		:= $(SOURCE) $(SOURCE)/wiiu $(SOURCE)/wiiu/service
RELEASE		:= release

CFLAGS	:= -std=gnu11 -mrvl -mcpu=750 -meabi -mhard-float -ffast-math -O3 -Wall -Werror -Wextra -Wno-unused-parameter -Wno-strict-aliasing $(addprefix -I,$(INCLUDES))
ASFLAGS	:= -mregnames
LDFLAGS	:= -nostartfiles -nostdlib -Wl,-Map,$(notdir $@).map,--gc-sections

OUTPUT	:= $(BUILD)/$(TARGET).a

CFILES	:= $(foreach DIR,$(SOURCES),$(wildcard $(DIR)/*.c))
OFILES	:= $(patsubst $(SOURCE)/%.c,$(BUILD)/%.o,$(CFILES))

all: buildDirs $(RELEASE)

$(RELEASE): releaseDirs $(OUTPUT)
	cp $(OUTPUT) $(RELEASE)/lib
	cp -r $(INCLUDES) $(RELEASE)
	cp link.ld $(RELEASE)

$(OUTPUT): $(OFILES)
	$(AR) rcs $@ $?

$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

releaseDirs:
	mkdir -p $(RELEASE) $(RELEASE)/lib

buildDirs:
	mkdir -p $(BUILD) $(patsubst $(SOURCE)/%,$(BUILD)/%,$(SOURCES))

clean:
	rm -vfr $(BUILD) $(RELEASE)