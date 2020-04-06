SYSEXIT = 1
SYSCALL32 = 0x80
EXIT_SUCCESS = 0

.data
# F0304008101100F04510002008570030
# F040500CD2205020321000CB04520031
# +_______________________________
# 1E0709014E2315110772000EB0CA90061
number_1:
    	.long 0xF0304008, 0x101100F0, 0x45100020, 0x08570030
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
number_2:
    	.long 0xF040500C, 0xD2205020, 0x321000CB, 0x04520031
		#.long 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
result: 
        .long 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
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
#zakonczenie programu
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int $SYSCALL32
