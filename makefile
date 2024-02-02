CC=gcc
CFLAGS	= -Wall -O2 -S
LINKER  = -Xlinker -Ttext -Xlinker 80100000

HEADER  = DATA.H
PROG	= main.exe
OBJS    = main.o player.o crystals.o enemy.o clear.o\
          Framework/pad.o Framework/render.o \
          Framework/obj.o Framework/aabb.o Framework/audio.o

all: $(PROG)

main.exe: $(OBJS)
	$(CC) $(LINKER) $(OBJS) -o $@
#	strip $@

#.c.o:
#	$(CC) $(CFLAGS) -funsigned-char -c $<

psx.exe: $(PROG)
	yarexe DATA.MAK

run: $(PROG)	
	del psx.exe 
	yarexe DATA.MAK	
	nopsx psx.exe
	
conrun: $(PROG)
	del psx.exe
	yarexe DATA.MAK
	nops.bat /fast /exe psx.exe	
clean:
	del $(PROG)
	del *.o
	del Framework\*.o
	del psx.exe
	del *.iso
	del *.cue
	del *.bin

