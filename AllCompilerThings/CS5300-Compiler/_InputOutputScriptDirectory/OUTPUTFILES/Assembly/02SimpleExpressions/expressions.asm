#***********************************************
#* PRINTING COMPILER BEGINNING SETUP SEQUENCE! *
#***********************************************

.text

    la $gp Global_Area
    or $fp $sp $zero
    j main

#****************************************
#* BEGIN PROGRAM COMPILATION WITH MAIN! *
#****************************************

main:

#WRITE("2+2=", 2+2, _ASCIIVAL_=> 10)
la $t0 string0
li $v0 4
move $a0 $t0
syscall
li $t0 2
li $t1 2
add $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("2*2=", 2*2, _ASCIIVAL_=> 10)
la $t0 string1
li $v0 4
move $a0 $t0
syscall
li $t0 2
li $t1 2
mult  $t0 $t1
mflo $t0
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("2/2=", 2/2, _ASCIIVAL_=> 10)
la $t0 string2
li $v0 4
move $a0 $t0
syscall
li $t0 2
li $t1 2
div  $t0 $t1
mflo $t0
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("2-2=", 2-2, _ASCIIVAL_=> 10)
la $t0 string3
li $v0 4
move $a0 $t0
syscall
li $t0 2
li $t1 2
sub $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("Enter A:")
la $t0 string4
li $v0 4
move $a0 $t0
syscall

#READ(a)
li $v0 5 
syscall
sw $v0 0($gp)

#WRITE("\nEnter b:")
la $t0 string5
li $v0 4
move $a0 $t0
syscall

#READ(b)
li $v0 5 
syscall
sw $v0 4($gp)

#WRITE(_ASCIIVAL_=> 10)
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a+b=", a+b, _ASCIIVAL_=> 10)
la $t0 string6
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
add $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a-b=", a-b, _ASCIIVAL_=> 10)
la $t0 string7
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
sub $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a*b=", a*b, _ASCIIVAL_=> 10)
la $t0 string8
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
mult  $t0 $t1
mflo $t0
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a/b=", a/b, _ASCIIVAL_=> 10)
la $t0 string9
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
div  $t0 $t1
mflo $t0
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a%b=", a%b, _ASCIIVAL_=> 10)
la $t0 string10
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
div  $t0 $t1
mfhi $t0
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a=b=", a=b, _ASCIIVAL_=> 10)
la $t0 string11
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
seq $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a<b=", a<b, _ASCIIVAL_=> 10)
la $t0 string12
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
slt $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a>b=", a>b, _ASCIIVAL_=> 10)
la $t0 string13
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
sgt $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a<>b=", a<>b, _ASCIIVAL_=> 10)
la $t0 string14
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
sne $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a<=b=", a<=b, _ASCIIVAL_=> 10)
la $t0 string15
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
sle $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a>=b=", a>=b, _ASCIIVAL_=> 10)
la $t0 string16
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
lw $t1 4($gp)
sge $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall


#**********************************************
#* END OF PROGRAM COMPILATION!                *
#* NOW PRINTING PROGRAM TERMINATION SEQUENCE! *
#**********************************************

li $v0 10
syscall

#****************************************************
#* COMPLETED PRINTING PROGRAM TERMINATION SEQUENCE! *
#* NOW PRINTING DATA SECTION, AND GLOBAL AREA!      *
#****************************************************

.data
string0:    .asciiz    "2+2="
string1:    .asciiz    "2*2="
string2:    .asciiz    "2/2="
string3:    .asciiz    "2-2="
string4:    .asciiz    "Enter A:"
string5:    .asciiz    "\nEnter b:"
string6:    .asciiz    "a+b="
string7:    .asciiz    "a-b="
string8:    .asciiz    "a*b="
string9:    .asciiz    "a/b="
string10:    .asciiz    "a%b="
string11:    .asciiz    "a=b="
string12:    .asciiz    "a<b="
string13:    .asciiz    "a>b="
string14:    .asciiz    "a<>b="
string15:    .asciiz    "a<=b="
string16:    .asciiz    "a>=b="


.align 2

    Global_Area:

