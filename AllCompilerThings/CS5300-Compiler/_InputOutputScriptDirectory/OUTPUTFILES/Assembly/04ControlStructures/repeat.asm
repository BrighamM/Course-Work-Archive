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

#i := 0
li $t0 0
la $t1 0($gp)
sw $t0 ($t1) 

#WRITE("i from 0 to 5\n")
la $t0 string0
li $v0 4
move $a0 $t0
syscall

b RepeatLabel0
RepeatLabel0:
#WRITE("i: ", i, " \n")
la $t0 string1
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string2
li $v0 4
move $a0 $t0
syscall

#i := i+1
lw $t0 0($gp)
li $t1 1
add $t0 $t0 $t1
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 0($gp)
li $t1 5
sgt $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
sle $t0 $t0 $zero
beq $t0 1 RepeatLabel0
b EndRepeatLabel0
EndRepeatLabel0:
b RepeatLabel1
RepeatLabel1:
#WRITE("should only happen once ", i, " \n")
la $t0 string3
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string2
li $v0 4
move $a0 $t0
syscall

#i := i+1
lw $t0 0($gp)
li $t1 1
add $t0 $t0 $t1
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 0($gp)
li $t1 5
sgt $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
sle $t0 $t0 $zero
beq $t0 1 RepeatLabel1
b EndRepeatLabel1
EndRepeatLabel1:
b WhileLabel0
WhileLabel0:
lw $t0 0($gp)
li $t1 5
slt $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
beq $t0 $zero EndWhileLabel0
#WRITE("should not happen i=", i, _ASCIIVAL_=> 10)
la $t1 string4
li $v0 4
move $a0 $t1
syscall
lw $t1 0($gp)
li $v0 1
or $a0 $t1 $zero
syscall
li $t1 '\n'
li $v0 11
move $a0 $t1
syscall

b WhileLabel0
EndWhileLabel0:

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
string0:    .asciiz    "i from 0 to 5\n"
string1:    .asciiz    "i: "
string2:    .asciiz    " \n"
string3:    .asciiz    "should only happen once "
string4:    .asciiz    "should not happen i="


.align 2

    Global_Area:

