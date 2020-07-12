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

#i := 5
li $t0 5
la $t1 0($gp)
sw $t0 ($t1) 

#j := 1
li $t0 1
la $t1 4($gp)
sw $t0 ($t1) 

lw $t0 0($gp)
li $t1 5
slt $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
beq $t0 1 ifBlock0
lw $t1 0($gp)
li $t2 5
seq $t1 $t1 $t2
abs $t1 $t1
sge $t1 $t1 1
beq $t1 1 elseIfBlock00
b elseBlock0
b endBlock0
ifBlock0:
#WRITE("i less than 5!\n")
la $t1 string0
li $v0 4
move $a0 $t1
syscall

lw $t1 4($gp)
li $t2 1
seq $t1 $t1 $t2
abs $t1 $t1
sge $t1 $t1 1
beq $t1 1 ifBlock1
b endBlock1
ifBlock1:
#WRITE("j is 1\n")
la $t2 string1
li $v0 4
move $a0 $t2
syscall

b endBlock1
endBlock1:
b endBlock0
elseIfBlock00:
#WRITE("i is 5! (expected result)")
la $t1 string2
li $v0 4
move $a0 $t1
syscall

b endBlock0
elseBlock0:
#WRITE("i is greater than 5!")
la $t1 string3
li $v0 4
move $a0 $t1
syscall

b endBlock0
endBlock0:

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
string0:    .asciiz    "i less than 5!\n"
string1:    .asciiz    "j is 1\n"
string2:    .asciiz    "i is 5! (expected result)"
string3:    .asciiz    "i is greater than 5!"


.align 2

    Global_Area:

