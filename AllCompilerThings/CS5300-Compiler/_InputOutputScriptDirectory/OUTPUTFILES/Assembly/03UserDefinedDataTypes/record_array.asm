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

#c [3] .a .g  [9]  [_ASCIIVAL_=> 67] .d  [3]  := 314
li $t0 314
la $t1 0($gp)
li $t2 3
subi $t2 $t2 1
li $t3 876
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
addi $t2 $t2 4
addi $t2 $t2 8
li $t1 9
subi $t1 $t1 8
li $t3 96
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
li $t2 'C'
subi $t2 $t2 0
li $t3 96
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
addi $t2 $t2 12
li $t1 3
subi $t1 $t1 -10
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#c [2] .a .g  [8]  [_ASCIIVAL_=> 68]  := c [3] .a .g  [9]  [_ASCIIVAL_=> 67] 
la $t0 0($gp)
li $t1 3
subi $t1 $t1 1
li $t2 876
mult $t1 $t2
mflo $t1
add $t1 $t1 $t0
addi $t1 $t1 4
addi $t1 $t1 8
li $t0 9
subi $t0 $t0 8
li $t2 96
mult $t0 $t2
mflo $t0
add $t0 $t0 $t1
li $t1 'C'
subi $t1 $t1 0
li $t2 96
mult $t1 $t2
mflo $t1
add $t1 $t1 $t0
la $t0 0($gp)
li $t2 2
subi $t2 $t2 1
li $t3 876
mult $t2 $t3
mflo $t2
add $t2 $t2 $t0
addi $t2 $t2 4
addi $t2 $t2 8
li $t0 8
subi $t0 $t0 8
li $t3 96
mult $t0 $t3
mflo $t0
add $t0 $t0 $t2
li $t2 'D'
subi $t2 $t2 0
li $t3 96
mult $t2 $t3
mflo $t2
add $t2 $t2 $t0
lw $t0 0($t1)
sw $t0 0($t2)
lw $t0 4($t1)
sw $t0 4($t2)
lw $t0 8($t1)
sw $t0 8($t2)
lw $t0 12($t1)
sw $t0 12($t2)
lw $t0 16($t1)
sw $t0 16($t2)
lw $t0 20($t1)
sw $t0 20($t2)
lw $t0 24($t1)
sw $t0 24($t2)
lw $t0 28($t1)
sw $t0 28($t2)
lw $t0 32($t1)
sw $t0 32($t2)
lw $t0 36($t1)
sw $t0 36($t2)
lw $t0 40($t1)
sw $t0 40($t2)
lw $t0 44($t1)
sw $t0 44($t2)
lw $t0 48($t1)
sw $t0 48($t2)
lw $t0 52($t1)
sw $t0 52($t2)
lw $t0 56($t1)
sw $t0 56($t2)
lw $t0 60($t1)
sw $t0 60($t2)
lw $t0 64($t1)
sw $t0 64($t2)
lw $t0 68($t1)
sw $t0 68($t2)
lw $t0 72($t1)
sw $t0 72($t2)
lw $t0 76($t1)
sw $t0 76($t2)
lw $t0 80($t1)
sw $t0 80($t2)
lw $t0 84($t1)
sw $t0 84($t2)
lw $t0 88($t1)
sw $t0 88($t2)
lw $t0 92($t1)
sw $t0 92($t2)
#WRITE("Result   = ", c [2] .a .g  [8]  [_ASCIIVAL_=> 68] .d  [3] , _ASCIIVAL_=> 10)
la $t1 string0
li $v0 4
move $a0 $t1
syscall
la $t1 0($gp)
li $t2 2
subi $t2 $t2 1
li $t0 876
mult $t2 $t0
mflo $t2
add $t2 $t2 $t1
addi $t2 $t2 4
addi $t2 $t2 8
li $t1 8
subi $t1 $t1 8
li $t0 96
mult $t1 $t0
mflo $t1
add $t1 $t1 $t2
li $t2 'D'
subi $t2 $t2 0
li $t0 96
mult $t2 $t0
mflo $t2
add $t2 $t2 $t1
addi $t2 $t2 12
li $t1 3
subi $t1 $t1 -10
li $t0 4
mult $t1 $t0
mflo $t1
add $t1 $t1 $t2
lw $t1 ($t1) 
li $v0 1
or $a0 $t1 $zero
syscall
li $t1 '\n'
li $v0 11
move $a0 $t1
syscall

#WRITE("Expected = ", 314, _ASCIIVAL_=> 10)
la $t1 string1
li $v0 4
move $a0 $t1
syscall
li $t1 314
li $v0 1
or $a0 $t1 $zero
syscall
li $t1 '\n'
li $v0 11
move $a0 $t1
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
string0:    .asciiz    "Result   = "
string1:    .asciiz    "Expected = "


.align 2

    Global_Area:

