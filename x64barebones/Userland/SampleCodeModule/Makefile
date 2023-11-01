include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_SHELL=$(wildcard shell/*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_COMMANDS=$(wildcard shell/commands/*.c)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_SHELL=$(SOURCES_SHELL:.c=.o)
OBJECTS_COMMANDS=$(SOURCES_COMMANDS:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS_ASM) $(SOURCES) $(SOURCES_COMMANDS) $(SOURCES_SHELL)
	$(GCC) $(GCCFLAGS) -I./include  -I./shell/include -T sampleCodeModule.ld _loader.c $(OBJECTS_ASM) $(SOURCES) $(SOURCES_COMMANDS) $(SOURCES_SHELL) -o ../$(MODULE)

%.o : %.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf obj

.PHONY: all clean print

