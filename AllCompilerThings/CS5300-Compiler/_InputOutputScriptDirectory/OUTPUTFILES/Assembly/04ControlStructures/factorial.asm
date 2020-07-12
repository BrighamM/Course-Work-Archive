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

#f := 1
li $t0 1
la $t1 4($gp)
sw $t0 ($t1) 

#n := 1
li $t0 1
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 0($gp)
la $t1 0($gp)
li $t2 8
ForLoop0: 
bgt $t0 $t2 Exit0
#f := f*n
lw $t3 4($gp)
lw $t4 0($gp)
mult  $t3 $t4
mflo $t3
la $t4 4($gp)
sw $t3 ($t4) 

#WRITE(n, _ASCIIVAL_=> 9, f, _ASCIIVAL_=> 10)
lw $t3 0($gp)
li $v0 1
or $a0 $t3 $zero
syscall
li $t3 '\t'
li $v0 11
move $a0 $t3
syscall
lw $t3 4($gp)
li $v0 1
or $a0 $t3 $zero
syscall
li $t3 '\n'
li $v0 11
move $a0 $t3
syscall

addi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop0
Exit0: 
#WRITE("\nExpected:\n")
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE("1\t1\n")
la $t0 string1
li $v0 4
move $a0 $t0
syscall

#WRITE("2\t2\n")
la $t0 string2
li $v0 4
move $a0 $t0
syscall

#WRITE("3\t6\n")
la $t0 string3
li $v0 4
move $a0 $t0
syscall

#WRITE("4\t24\n")
la $t0 string4
li $v0 4
move $a0 $t0
syscall

#WRITE("5\t120\n")
la $t0 string5
li $v0 4
move $a0 $t0
syscall

#WRITE("6\t720\n")
la $t0 string6
li $v0 4
move $a0 $t0
syscall

#WRITE("7\t5040\n")
la $t0 string7
li $v0 4
move $a0 $t0
syscall

#WRITE("8\t40320\n")
la $t0 string8
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
string0:    .asciiz    "\nExpected:\n"
string1:    .asciiz    "1\t1\n"
string2:    .asciiz    "2\t2\n"
string3:    .asciiz    "3\t6\n"
string4:    .asciiz    "4\t24\n"
string5:    .asciiz    "5\t120\n"
string6:    .asciiz    "6\t720\n"
string7:    .asciiz    "7\t5040\n"
string8:    .asciiz    "8\t40320\n"


.align 2

    Global_Area:

