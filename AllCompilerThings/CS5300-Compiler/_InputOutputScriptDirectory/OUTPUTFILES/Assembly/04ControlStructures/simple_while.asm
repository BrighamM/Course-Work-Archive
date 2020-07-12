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

#a := 0
li $t0 0
la $t1 0($gp)
sw $t0 ($t1) 

b WhileLabel0
WhileLabel0:
lw $t0 0($gp)
li $t1 10
slt $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
beq $t0 $zero EndWhileLabel0
#WRITE(a)
lw $t1 0($gp)
li $v0 1
or $a0 $t1 $zero
syscall

#a := a+1
lw $t1 0($gp)
li $t2 1
add $t1 $t1 $t2
la $t2 0($gp)
sw $t1 ($t2) 

b WhileLabel0
EndWhileLabel0:
#WRITE("\nExpected\n0123456789\n")
la $t0 string0
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
string0:    .asciiz    "\nExpected\n0123456789\n"


.align 2

    Global_Area:

