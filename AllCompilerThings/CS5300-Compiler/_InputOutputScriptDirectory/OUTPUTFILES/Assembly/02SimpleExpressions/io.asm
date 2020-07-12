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

#WRITE("Enter an integer, then a character:\n")
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#READ(i, c)
li $v0 5 
syscall
sw $v0 0($gp)
li $v0 12 
syscall
sw $v0 4($gp)

#WRITE("integer:   ", i, _ASCIIVAL_=> 10)
la $t0 string1
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("character: ", c, _ASCIIVAL_=> 10)
la $t0 string2
li $v0 4
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

#WRITE("true: ", true, _ASCIIVAL_=> 10)
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

#WRITE("false: ", false, _ASCIIVAL_=> 10)
la $t0 string4
li $v0 4
move $a0 $t0
syscall
li $t0 0
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
string0:    .asciiz    "Enter an integer, then a character:\n"
string1:    .asciiz    "integer:   "
string2:    .asciiz    "character: "
string3:    .asciiz    "true: "
string4:    .asciiz    "false: "


.align 2

    Global_Area:

