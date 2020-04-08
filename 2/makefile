all: add.exe sub.exe

add.exe: add.o
	ld -m elf_i386 -o add.exe add.o

sub.exe: sub.o
	ld -m elf_i386 -o sub.exe sub.o

add.o: add.s
	as --32 --gstabs -o add.o add.s

sub.o: sub.s
	as --32 --gstabs -o sub.o sub.s
