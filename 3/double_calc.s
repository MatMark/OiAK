SYSEXIT = 1
SYSCALL32 = 0x80
EXIT_SUCCESS = 0

.data
first_num_msg: .string "Podaj pierwsza liczbe: "
second_num_msg: .string "Podaj druga liczbe: "
operator_msg: .string "Podaj operacje do wykonania [+, -, *, /]: "
value: .string "  %.16lf\n"
out: .string "%c______________________________________________\n  %.16lf\n"
in: .ascii "%lf"
number_1: .double 0
number_2: .double 0
operator: .ascii ""
in_operator: .string "%c"
duble_num_1: .double 0
duble_num_2: .double 0
result: .double 15.22

.text

.global _start

_start:

#wiadomosc o podaniu operatora
pushl $operator_msg
call printf
#wczytanie operatora
pushl $operator
pushl $in_operator
call scanf

#wiadomosc o podaniu pierwszej liczby
pushl $first_num_msg
call printf
#wczytanie pierwszej liczby
pushl $number_1
pushl $in
call scanf

#wiadomosc o podaniu drugiej liczby
pushl $second_num_msg
call printf
#wczytanie drugiej liczby
pushl $number_2
pushl $in
call scanf

#inicjalizacja jednostki zmiennoprzecinkowej (fpu)
finit 

#wyswietlenie pierwszej wprowadzonej liczby w formacie liczby zmiennoprzecinkowej
fldl number_1+4 #zaladowanie na stos fpu st(0)
fldl number_1
fstl (duble_num_1) #przeniesienie ze stosu fpu
pushl duble_num_1+4
pushl duble_num_1
pushl $value
call printf 

#wyswietlenie drugiej wprowadzonej liczby w formacie liczby zmiennoprzecinkowej
fldl number_2+4 #zaladowanie na stos fpu st(0)
fldl number_2
fstl (duble_num_1) #przeniesienie ze stosu fpu
pushl duble_num_1+4
pushl duble_num_1
pushl $value
call printf 

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
fadd %st(1), %st(0) #dodaj st(1) i st(0), wynik w st(0)
jmp print

sub:
fsub %st(1), %st(0) #odejmij st(1) i st(0), wynik w st(0)
jmp print

mul:
fmul %st(1), %st(0) #pomnoz st(1) i st(0), wynik w st(0)
jmp print

div:
fdiv %st(1), %st(0) #podziel st(1) i st(0), wynik w st(0)
jmp print

#wyswietlenie wyniku
print:
fstl (result) #przeniesienie ze stosu fpu
pushl result+4
pushl result
pushl %edx
pushl $out
call printf

#zakonczenie programu
end:
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int $SYSCALL32
