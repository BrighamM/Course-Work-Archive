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

#j := 0
li $t0 0
la $t1 4($gp)
sw $t0 ($t1) 

b WhileLabel0
WhileLabel0:
lw $t0 0($gp)
li $t1 6
sle $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
beq $t0 $zero EndWhileLabel0
b WhileLabel1
WhileLabel1:
lw $t1 4($gp)
lw $t2 0($gp)
sle $t1 $t1 $t2
abs $t1 $t1
sge $t1 $t1 1
beq $t1 $zero EndWhileLabel1
#WRITE(i, ":", j, _ASCIIVAL_=> 32)
lw $t2 0($gp)
li $v0 1
or $a0 $t2 $zero
syscall
la $t2 string0
li $v0 4
move $a0 $t2
syscall
lw $t2 4($gp)
li $v0 1
or $a0 $t2 $zero
syscall
li $t2 ' '
li $v0 11
move $a0 $t2
syscall

#j := j+1
lw $t2 4($gp)
li $t3 1
add $t2 $t2 $t3
la $t3 4($gp)
sw $t2 ($t3) 

b WhileLabel1
EndWhileLabel1:
#WRITE(_ASCIIVAL_=> 10)
li $t1 '\n'
li $v0 11
move $a0 $t1
syscall

#i := SUCC(i)
lw $t1 0($gp)
addi $t1 $t1 1 
la $t2 0($gp)
sw $t1 ($t2) 

#j := 0
li $t1 0
la $t2 4($gp)
sw $t1 ($t2) 

b WhileLabel0
EndWhileLabel0:
#WRITE("Expected: list pairs of [0-6]\n")
la $t0 string1
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
string0:    .asciiz    ":"
string1:    .asciiz    "Expected: list pairs of [0-6]\n"


.align 2

    Global_Area:

