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
lw $t1 0($gp)
li $t2 2
div  $t1 $t2
mfhi $t1
li $t2 0
seq $t1 $t1 $t2
abs $t1 $t1
sge $t1 $t1 1
beq $t1 1 ifBlock0
b endBlock0
ifBlock0:
#WRITE(a)
lw $t2 0($gp)
li $v0 1
or $a0 $t2 $zero
syscall

b endBlock0
endBlock0:
#a := a+1
lw $t1 0($gp)
li $t2 1
add $t1 $t1 $t2
la $t2 0($gp)
sw $t1 ($t2) 

b WhileLabel0
EndWhileLabel0:
#WRITE("\nExpected:\n02468\n")
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
string0:    .asciiz    "\nExpected:\n02468\n"


.align 2

    Global_Area:

