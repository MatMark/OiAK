SYSEXIT = 1
SYSCALL32 = 0x80
EXIT_SUCCESS = 0

.data
first_num_msg: .string "Podaj pierwsza liczbe: "
second_num_msg: .string "Podaj druga liczbe: "
operator_msg: .string "Podaj operacje do wykonania [+, -, *, /]: "
value: .string "  %f\n"
out: .string "%c %f\n"
in: .ascii "%f"
number_1: .float 0
number_2: .float 0
operator: .ascii ""
in_operator: .string "%c"
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
fld number_1 #zaladowanie na stos fpu st(0)
fstpl (%esp) #przeniesienie ze stosu fpu
pushl $value
call printf 

#wyswietlenie drugiej wprowadzonej liczby w formacie liczby zmiennoprzecinkowej
fld number_2 #zaladowanie na stos fpu st(0)
fstpl (%esp) #przeniesienie ze stosu fpu
pushl $value
call printf

load:
fld number_2
fst %st(1) # skopiuj st(0) do st(1)
fld number_1

#wyczyszczenie rejestru edx
xor %edx, %edx 

#skok do odpowiedniej operacji
movb operator, %edx
cmp $'+', %edx
je add
cmp $'-', %edx
je sub
cmp $'*', %edx
je mul
cmp $'/', %edx
je div
#jezeli zadna nie pasuje zakoncz program
jmp end

add:
faddp %st(1), %st(0) #dodaj st(1) i st(0), wynik w st(0)
jmp print

sub:
fsubp %st(1), %st(0) #odejmij st(1) i st(0), wynik w st(0)
jmp print

mul:
fmulp %st(1), %st(0) #pomnoz st(1) i st(0), wynik w st(0)
jmp print

div:
fdivp %st(1), %st(0) #podziel st(1) i st(0), wynik w st(0)
jmp print

#wyswietlenie wyniku
print:
fstpl (%esp) #przeniesienie ze stosu fpu
pushl %edx
pushl $out
call printf

#zakonczenie programu
end:
movl $SYSEXIT, %eax
movl $EXIT_SUCCESS, %ebx
int $SYSCALL32