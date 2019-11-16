# global
src :=
obj :=

#
# Include the make variables (CC, etc...)
#
AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
#CC	= $(CROSS_COMPILE)gcc
CC	= $(CROSS_COMPILE)g++
CPP	= $(CC) -E
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)ranlib

# debug
ifeq ($(DEBUG), debug)
#DBGFLAGS = -g -ggdb
DBGFLAGS = -g
else
DBGFLAGS =
endif
$(warning "DBGFLAGS=$(DBGFLAGS)")

#OPTFLAGS= -Os
#Compile flags: Add the debug flag
#ifeq ($(ACU_MAKE_VERSION), debug)
#	CFLAGS  += -g -ggdb -D_DEBUG=1
#	LDFLAGS += -Wl,-Map,$@.map
#else
#	CFLAGS  += -DNDEBUG #-o2
#	LDFLAGS += -Wl,-s
#endif

#compile option, include head direction
CPPFLAGS := $(DBGFLAGS)
CPPFLAGS += -I$(TOPDIR)/include
CFLAGS  := $(CPPFLAGS) -W -Wall -Wstrict-prototypes -Wundef \
	-Wunknown-pragmas -Wunreachable-code \
	-Wfloat-equal -W -Wimplicit -Wconversion

# obj rule
#%.o:	%.c
#	$(CC) $(CFLAGS) -c -o $@ $<

