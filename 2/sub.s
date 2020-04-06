SYSEXIT = 1
SYSCALL32 = 0x80
EXIT_SUCCESS = 0
# 0F304008 101100F0 45100020 08570030
# 0F40500C D2205020 321000CB 54520031
#-___________________________________
# FFEFEFFB 3DF0B0D0 12FFFF54 B404FFFF
.data
number_1:
    	.long 0x0F304008, 0x101100F0, 0x45100020, 0x08570030
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
number_2:
    	.long 0x0F40500C, 0xD2205020, 0x321000CB, 0x54520031
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
result: 
        .long 0x00000000, 0x00000000, 0x00000000, 0x00000000
.text
.global _start
_start:
#licznik do petli
movl $4, %ecx
_next:
#zapewnienie, ze wejdziemy tez do zerowego elementu gdyz "loop" przy wartosci rejestru ecx rownym zero nie wykonuje skoku 
decl %ecx
#zaladowanie odpowiednich czesci liczb do rejestrow eax i ebx
movl number_1(, %ecx, 4), %eax
movl number_2(, %ecx, 4), %ebx
#odjecie z pozyczka pierwszego argumentu od drugiego i zapisanie w drugim
subl %ebx, %eax
jnc _no_burrow
#odjecie pozyczki z wyzszej pozycji
decl %ecx
decl result(, %ecx, 4)
incl %ecx
#wyzerowanie flagi przeniesienia (pozyczki)
clc
_no_burrow:
#wynik jest sumowany z ewentualna pozyczka (jezeli wystapila pozyczka element ma wartosc -1 [0xffffffff])
addl %eax, result(, %ecx, 4)
#przywrocenie normalnej wartosci rejestru ecx
incl %ecx
loop _next
#zakonczenie programu
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int $SYSCALL32
