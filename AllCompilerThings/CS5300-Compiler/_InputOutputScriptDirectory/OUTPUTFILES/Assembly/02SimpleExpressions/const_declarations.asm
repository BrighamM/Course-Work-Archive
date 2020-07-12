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

#WRITE("5=", int, _ASCIIVAL_=> 10)
la $t0 string1
li $v0 4
move $a0 $t0
syscall
li $t0 5
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("a=", char, _ASCIIVAL_=> 10)
la $t0 string2
li $v0 4
move $a0 $t0
syscall
li $t0 'a'
li $v0 11
move $a0 $t0
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("true=", bool, _ASCIIVAL_=> 10)
la $t0 string3
li $v0 4
move $a0 $t0
syscall
li $t0 1
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("str=", str, _ASCIIVAL_=> 10)
la $t0 string4
li $v0 4
move $a0 $t0
syscall
la $t0 string0
li $v0 4
move $a0 $t0
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
string0:    .asciiz    "Hello world"
string1:    .asciiz    "5="
string2:    .asciiz    "a="
string3:    .asciiz    "true="
string4:    .asciiz    "str="


.align 2

    Global_Area:

