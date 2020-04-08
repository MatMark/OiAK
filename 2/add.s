SYSEXIT = 1
SYSCALL32 = 0x80
EXIT_SUCCESS = 0

.data

number_1: .long 0xF0304008, 0x101100F0, 0x45100020, 0x08570030
number_2: .long 0xF040500C, 0xD2205020, 0x321000CB, 0x04520031
result: .long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
out_num: .string "\t\t%08X%08X%08X%08X\n"
out_res: .string "+_______________________________________________\n\t%08X%08X%08X%08X%08X\n"

.text
.global _start
_start:

#wyswietlenie pierwszej liczby
pushl number_1+12
pushl number_1+8
pushl number_1+4
pushl number_1
pushl $out_num
call printf

#wyswietlenie drugiej liczby
pushl number_2+12
pushl number_2+8
pushl number_2+4
pushl number_2
pushl $out_num
call printf

#licznik do petli
movl $4, %ecx

_next:
#zapewnienie, ze wejdziemy tez do zerowego elementu gdyz "loop" przy wartosci rejestru ecx rownym zero nie wykonuje skoku 
decl %ecx
#zaladowanie odpowiednich czesci liczb do rejestrow eax i ebx
movl number_1(, %ecx, 4), %eax
movl number_2(, %ecx, 4), %ebx
#suma z przeniesieniem, wynik w ebx
adcl %eax, %ebx
#skok w przypadku gdy flaga carry nie jest ustawiona
jnc _no_carry
#jezeli flaga carry jest ustawiona zwieksz result na kolejnej pozycji 
#(dla result np. pozycja 3 jest suma pozycji 2 w dodawanych liczbach dlatego wartosc ecx jest ta sama)
incl result(, %ecx, 4)
#wyzerowanie flagi przeniesienia
clc

_no_carry:
#przywrocenie normalnej wartosci rejestru ecx
incl %ecx
#wynik jest sumowany z ewentualnym przeniesieniem
addl %ebx, result(, %ecx, 4)
#sprawdzenie warunku petli
loop _next

#wyswietlenie wyniku
pushl result+16
pushl result+12
pushl result+8
pushl result+4
pushl result
pushl $out_res
call printf

#zakonczenie programu
_end:
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int $SYSCALL32
