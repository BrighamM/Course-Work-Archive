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

#i := 10
li $t0 10
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 0($gp)
la $t1 0($gp)
li $t2 5
ForLoop0: 
blt $t0 $t2 Exit0
#WRITE(i, " \n")
lw $t3 0($gp)
li $v0 1
or $a0 $t3 $zero
syscall
la $t3 string0
li $v0 4
move $a0 $t3
syscall

subi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop0
Exit0: 
#j := 4
li $t0 4
la $t1 0($fp)
sw $t0 ($t1) 

lw $t0 0($fp)
la $t1 0($fp)
li $t2 0
ForLoop1: 
blt $t0 $t2 Exit1
#WRITE(_ASCIIVAL_=> 32, j)
li $t3 ' '
li $v0 11
move $a0 $t3
syscall
lw $t3 0($fp)
li $v0 1
or $a0 $t3 $zero
syscall

subi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop1
Exit1: 
#WRITE("\nExpected:\n")
la $t0 string1
li $v0 4
move $a0 $t0
syscall

#WRITE("10\n9\n8\n7\n6\n5\n 4 3 2 1 0\n")
la $t0 string2
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
string0:    .asciiz    " \n"
string1:    .asciiz    "\nExpected:\n"
string2:    .asciiz    "10\n9\n8\n7\n6\n5\n 4 3 2 1 0\n"


.align 2

    Global_Area:

