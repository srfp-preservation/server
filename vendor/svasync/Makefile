all: libsv.a term

GCC=i586-pc-msdosdjgpp-gcc -O3 -Wall -g
AR=i586-pc-msdosdjgpp-ar
DEL=rm -f

libsv.a : svasync.o isr.o
	$(AR) -rs libsv.a svasync.o isr.o

svasync.o : svasync.c
	$(GCC) -c svasync.c

isr.o : isr.S
	$(GCC) -c isr.S

term : term.o libsv.a
	$(GCC) term.o libsv.a -o term -lpc

term.o : term.c
	$(GCC) -c term.c

clean :
	$(DEL) *.o
	$(DEL) libsv.a
	$(DEL) term.
	$(DEL) term.exe
