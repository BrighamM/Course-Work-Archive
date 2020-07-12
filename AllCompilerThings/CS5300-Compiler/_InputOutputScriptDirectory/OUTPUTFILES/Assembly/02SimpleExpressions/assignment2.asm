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

#number := 42
li $t0 42
la $t1 0($gp)
sw $t0 ($t1) 

#number1 := 142
li $t0 142
la $t1 4($gp)
sw $t0 ($t1) 

#number2 := 242
li $t0 242
la $t1 8($gp)
sw $t0 ($t1) 

#number3 := 342
li $t0 342
la $t1 12($gp)
sw $t0 ($t1) 

#number4 := 442
li $t0 442
la $t1 16($gp)
sw $t0 ($t1) 

#number5 := 542
li $t0 542
la $t1 20($gp)
sw $t0 ($t1) 

#number6 := 642
li $t0 642
la $t1 24($gp)
sw $t0 ($t1) 

#WRITE(number, "\n")
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number1, "\n")
lw $t0 4($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number2, "\n")
lw $t0 8($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number3, "\n")
lw $t0 12($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number4, "\n")
lw $t0 16($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number5, "\n")
lw $t0 20($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number6, "\n")
lw $t0 24($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number1, "\n", number2, "\n", number3, "\n")
lw $t0 4($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall
lw $t0 8($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string0
li $v0 4
move $a0 $t0
syscall
lw $t0 12($gp)
li $v0 1
or $a0 $t0 $zero
syscall
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
string0:    .asciiz    "\n"


.align 2

    Global_Area:

