# command option
ifdef O
ifeq ("$(origin O)", "command line")
BUILD_DIR := $(O)
endif
endif

# source directory
OBJTREE		:= $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))
SRCTREE		:= $(CURDIR)
TOPDIR			:= $(SRCTREE)
LNDIR			:= $(OBJTREE)

export	TOPDIR SRCTREE OBJTREE

#include configuration if required in priority
sinclude config.mk
export	DEBUG

# architecture
ARCH = pc
ifndef CROSS_COMPILE
$(warning "not define CROSS_COMPILE")
ifeq ($(ARCH), pc)
	CROSS_COMPILE =
endif
ifeq ($(ARCH), ppc)
	CROSS_COMPILE = ppc_8xx-
endif
ifeq ($(ARCH), arm)
	CROSS_COMPILE = /opt/usr/bin/arm-buildroot-linux-gnueabihf-
endif
else#CROSS_COMPILE
$(warning "define CROSS_COMPILE")
$(warning "CROSS_COMPILE= $(CROSS_COMPILE)")
endif#CROSS_COMPILE

export CROSS_COMPILE


#include gcc var.
include Makefile.mk

# defined in Makefile.mk
#export obj src
# all files
#SRCLIST=$(shell find . -name "*.c")
SRCLIST := $(shell find . -regex '.*\.\(c\|cpp\)')
OBJLIST := $(SRCLIST:%.c=%.o)
OBJLIST += $(SRCLIST:%.cpp=%.o)

# top directory source file
SRCS = $(CURDIR)/main.cpp
OBJS = $(SRCS:%.cpp=%.o)

# directly include xxxx.a here
#PLATFORM_LIBS := -L $(shell dirname `$(CC) $(CFLAGS) \
#	-print-libgcc-file-name`) \
#	-lgcc -lpthread -lrt -lm
#PUB_LIBS := -L$(TOPDIR)/lib -lhardware -lpub -lapplog
#LIBS := -lgcc -lpthread -lrt -lm -L$(TOPDIR)/lib \
	 -lhardware -lpub -lapplog
#LIBS 			:= $(addprefix $(obj),$(LIBS))

# source code directory
SUBDIRS	= RSAEuro 


#	  ui 

ALL := $(obj)posapp
all:		$(ALL)

$(obj)posapp: depend $(OBJS)
	@echo "SRCLIST=$(SRCLIST)"
	@echo "OBJLIST=$(OBJLIST)"
	$(CC)  $(CFLAGS) -o $@ $(OBJLIST)

$(OBJS):
	$(CC)  $(CFLAGS) -c -o $@ $(SRCS)
	
#	
#	echo "123" > $(obj)posapp
#	echo $(OBJLIST)
#	OBJLIST=$(shell find ./common -name "*.o")
#	echo $$OBJLIST > $(obj)posapp
#	$(CC)  $(CFLAGS) -o $@ $(OBJLIST)

# get OBJLIST value
depend:
		for dir in $(SUBDIRS) ; do \
			$(MAKE) -C $$dir all; done
debug:	
	echo "DEBUG=debug" > config.mk 


.PHONY: clean
clean:
	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir clean; done
	@-rm -f  $(ALL) *.o config.mk

#$(obj)posapp: depend
#	(CC)  $(CPPFLAGS) -o $@ $(OBJS)

#depend dep:
#		for dir in $(SUBDIRS) ; do \
#			$(MAKE) -C $$dir _depend; done

#$(OBJS):
#		$(MAKE) -C cpu/$(CPU) $(if $(REMOTE_BUILD),$@,$(notdir $@))

#$(SUBDIRS):	
#		$(MAKE) -C $@ all

