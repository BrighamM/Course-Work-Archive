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

lw $t0 0($gp)
la $t1 0($gp)
li $t2 5
ForLoop0: 
bgt $t0 $t2 Exit0
#WRITE(i, " ")
lw $t3 0($gp)
li $v0 1
or $a0 $t3 $zero
syscall
la $t3 string0
li $v0 4
move $a0 $t3
syscall

addi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop0
Exit0: 
#WRITE("\n\nExpected:\n0 1 2 3 4 5\n")
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
string0:    .asciiz    " "
string1:    .asciiz    "\n\nExpected:\n0 1 2 3 4 5\n"


.align 2

    Global_Area:

