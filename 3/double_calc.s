SYSEXIT = 1
SYSCALL32 = 0x80
EXIT_SUCCESS = 0

.data
first_num_msg: 
    .string "Podaj pierwsza liczbe: "
second_num_msg: 
    .string "Podaj druga liczbe: "
operator_msg: 
    .string "Podaj operacje do wykonania [+, -, *, /]: "
value: 
    .string "  %.14lf\n"
out: 
    .string "%c______________________________\n  %.14lf\n"
in: .ascii "%lf"
number_1: .double 0
number_2: .double 0
operator: .ascii ""
in_operator: .string "%c"
duble_num_1: .double 0
duble_num_2: .double 0
result: .double 0

.text

.global _start

_start:

#wiadomosc o podaniu operatora
pushl $operator_msg
call printf
addl $4, %esp
#wczytanie operatora
pushl $operator
pushl $in_operator
call scanf
addl $8, %esp

#wiadomosc o podaniu pierwszej liczby
pushl $first_num_msg
call printf
addl $4, %esp
#wczytanie pierwszej liczby
pushl $number_1
pushl $in
call scanf
addl $8, %esp

#wiadomosc o podaniu drugiej liczby
pushl $second_num_msg
call printf
addl $4, %esp
#wczytanie drugiej liczby
pushl $number_2
pushl $in
call scanf
addl $8, %esp

#inicjalizacja jednostki zmiennoprzecinkowej (fpu)
finit 

#wyswietlenie pierwszej wprowadzonej liczby 
#w formacie liczby zmiennoprzecinkowej
fldl number_1+4 #zaladowanie na stos fpu st(0)
fldl number_1
fstl (duble_num_1) #przeniesienie ze stosu fpu
pushl duble_num_1+4
pushl duble_num_1
pushl $value
call printf 
addl $12, %esp

#wyswietlenie drugiej wprowadzonej liczby 
#w formacie liczby zmiennoprzecinkowej
fldl number_2+4 #zaladowanie na stos fpu st(0)
fldl number_2
fstl (duble_num_1) #przeniesienie ze stosu fpu
pushl duble_num_1+4
pushl duble_num_1
pushl $value
call printf 
addl $12, %esp

load:
fldl number_2
fst %st(1) # skopiuj st(0) do st(1)
fldl number_1 

#wyczyszczenie rejestru edx
xor %edx, %edx 

#skok do odpowiedniej operacji
movb operator, %dl #dolny bajt dx
cmpb $'+', %dl
je add
cmpb $'-', %dl
je sub
cmpb $'*', %dl
je mul
cmpb $'/', %dl
je div
#jezeli zadna nie pasuje zakoncz program
jmp end

add:
#dodaj st(1) i st(0), wynik w st(0)
fadd %st(1), %st(0)
jmp print

sub:
#odejmij st(1) i st(0), wynik w st(0)
fsub %st(1), %st(0)
jmp print

mul:
#pomnoz st(1) i st(0), wynik w st(0)
fmul %st(1), %st(0)
jmp print

div:
#podziel st(1) i st(0), wynik w st(0)
fdiv %st(1), %st(0)
jmp print

#wyswietlenie wyniku
print:
#przeniesienie ze stosu fpu
fstl (result)
pushl result+4
pushl result
pushl %edx
pushl $out
call printf
addl $16, %esp

#zakonczenie programu
end:
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int $SYSCALL32
