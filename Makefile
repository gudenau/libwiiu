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
SOURCES		:= src src/wiiu src/wiiu/service

CFLAGS	:= -std=gnu11 -mrvl -mcpu=750 -meabi -mhard-float -ffast-math -O3 -Wall -Wextra -Wno-unused-parameter -Wno-strict-aliasing $(addprefix -I,$(INCLUDES))
ASFLAGS	:= -mregnames
LDFLAGS	:= -nostartfiles -Wl,-Map,$(notdir $@).map,-wrap,malloc,-wrap,free,-wrap,memalign,-wrap,calloc,-wrap,realloc,-wrap,malloc_usable_size,-wrap,_malloc_r,-wrap,_free_r,-wrap,_realloc_r,-wrap,_calloc_r,-wrap,_memalign_r,-wrap,_malloc_usable_size_r,-wrap,valloc,-wrap,_valloc_r,-wrap,_pvalloc_r,--gc-sections

CFILES	:= $(foreach DIR,$(SOURCES),$(wildcard $(DIR)/*.c))
OFILES	:= $(patsubst $(SOURCE)/%.c,$(BUILD)/%.o,$(CFILES))

all: buildDirs $(OFILES)

$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

buildDirs:
	mkdir -p $(BUILD) $(patsubst $(SOURCE)/%,$(BUILD)/%,$(SOURCES))

clean:
	rm -vfr $(BUILD)