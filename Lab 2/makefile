all: add.exe sub.exe

add.exe: add.o
	ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o add.exe add.o

add.o: add.s
	as --32 --gstabs -o add.o add.s

sub.exe: sub.o
	ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o sub.exe sub.o

sub.o: sub.s
	as --32 --gstabs -o sub.o sub.s
