# include gcc var. and obj rule
include ../Makefile.mk
# CFLAGS += -DET_DEBUG -DDEBUG

CSRCS		:= $(wildcard *.c)
COBJS		:= $(CSRCS:%.c=%.o)
#OBJLIST		+= $(addprefix $(CURDIR), $(COBJS))
#$(warning $(OBJLIST))

all: $(COBJS)
#	@echo $(OBJLIST) >> $(TOPDIR)/list.txt
clean:
	@-rm -f *.o
# $(CURDIR) is a dynamic value
#all: 
#	@echo ${CURDIR}; \
#	$(MAKE) -C ./test all

