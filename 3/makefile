all: float_calc.exe double_calc.exe

float_calc.exe: float_calc.o
	ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o float_calc.exe float_calc.o

float_calc.o: float_calc.s
	as --32 --gstabs -o float_calc.o float_calc.s

double_calc.exe: double_calc.o
	ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc -o double_calc.exe double_calc.o

double_calc.o: double_calc.s
	as --32 --gstabs -o double_calc.o double_calc.s