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

#WRITE(false, 3<>3, _ASCIIVAL_=> 10)
li $t0 1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 3
li $t1 3
sne $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE(true, 3=3, _ASCIIVAL_=> 10)
li $t0 0
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 3
li $t1 3
seq $t0 $t0 $t1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#i := ORD(_ASCIIVAL_=> 65)
li $t0 'A'
la $t1 0($gp)
sw $t0 ($t1) 

#c := CHR(i)
lw $t0 0($gp)
la $t1 4($gp)
sw $t0 ($t1) 

#WRITE(i, _ASCIIVAL_=> 32, c, _ASCIIVAL_=> 10)
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 ' '
li $v0 11
move $a0 $t0
syscall
lw $t0 4($gp)
li $v0 11
move $a0 $t0
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("Expected:\n")
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE("10\n")
la $t0 string1
li $v0 4
move $a0 $t0
syscall

#WRITE("01\n")
la $t0 string2
li $v0 4
move $a0 $t0
syscall

#WRITE("65 A\n")
la $t0 string3
li $v0 4
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
string0:    .asciiz    "Expected:\n"
string1:    .asciiz    "10\n"
string2:    .asciiz    "01\n"
string3:    .asciiz    "65 A\n"


.align 2

    Global_Area:

