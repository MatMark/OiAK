all: float_calc run

run: float_calc
	./float_calc

float_calc: float_calc.o
	ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o float_calc float_calc.o

float_calc.o: float_calc.s
	as --32 --gstabs -o float_calc.o float_calc.s
