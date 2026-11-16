ifeq ($(strip $(DEVKITXENON)),)
$(error "Defina DEVKITXENON, ex: export DEVKITXENON=/usr/local/xenon")
endif

include $(DEVKITXENON)/rules

TARGET   := app
DEPSDIR  := .
SOURCES  := main.c
OBJS     := $(SOURCES:.c=.o)

MACHDEP  = -DXENON -m32 -mno-altivec -fno-pic -mpowerpc64 -mhard-float
CFLAGS   = -O2 -Wall $(MACHDEP) -I$(DEVKITXENON)/usr/include
LDFLAGS  = $(MACHDEP) -L$(DEVKITXENON)/xenon/lib/32 -L$(DEVKITXENON)/usr/lib
LIBS     := -lxenon -lm

all: $(TARGET).elf32

$(TARGET).elf: $(OBJS)
	$(CC) -n -T $(DEVKITXENON)/app.lds -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

$(TARGET).elf32: $(TARGET).elf
	$(OBJCOPY) -O elf32-powerpc --adjust-vma 0x80000000 $< $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).elf32
