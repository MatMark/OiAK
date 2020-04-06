all: add sub

add: add.o
	ld -m elf_i386 -o add add.o

sub: sub.o
	ld -m elf_i386 -o sub sub.o

add.o: add.s
	as --32 --gstabs -o add.o add.s

sub.o: sub.s
	as --32 --gstabs -o sub.o sub.s
