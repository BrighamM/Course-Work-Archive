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

sum:
or $fp $sp $zero
#total := 0
li $t0 0
la $t1 52($fp)
sw $t0 ($t1) 

#i := 1
li $t0 1
la $t1 48($fp)
sw $t0 ($t1) 

lw $t0 48($fp)
la $t1 48($fp)
li $t2 12
ForLoop0: 
bgt $t0 $t2 Exit0
#total := total+a [i] 
lw $t3 52($fp)
la $t4 0($fp)
lw $t5 48($fp)
subi $t5 $t5 1
li $t6 4
mult $t5 $t6
mflo $t5
add $t5 $t5 $t4
lw $t5 ($t5) 
add $t3 $t3 $t5
la $t5 52($fp)
sw $t3 ($t5) 

addi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop0
Exit0: 
lw $t0 52($fp)
or $s7 $t0 $zero
jr $ra

main:

#x := 1
li $t0 1
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 0($gp)
la $t1 0($gp)
li $t2 12
ForLoop1: 
bgt $t0 $t2 Exit1
#arr [x]  := 5+x
li $t3 5
lw $t5 0($gp)
add $t3 $t3 $t5
la $t5 4($gp)
lw $t4 0($gp)
subi $t4 $t4 1
li $t6 4
mult $t4 $t6
mflo $t4
add $t4 $t4 $t5
sw $t3 ($t4) 

addi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop1
Exit1: 
#WRITE("The sum of the array is: ", sum(arr), _ASCIIVAL_=> 10)
la $t0 string0
li $v0 4
move $a0 $t0
syscall

# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -4
addi $sp $sp -48
la $t0 4($gp)
lw $t1 0($t0)
sw $t1 0($sp)
lw $t1 4($t0)
sw $t1 4($sp)
lw $t1 8($t0)
sw $t1 8($sp)
lw $t1 12($t0)
sw $t1 12($sp)
lw $t1 16($t0)
sw $t1 16($sp)
lw $t1 20($t0)
sw $t1 20($sp)
lw $t1 24($t0)
sw $t1 24($sp)
lw $t1 28($t0)
sw $t1 28($sp)
lw $t1 32($t0)
sw $t1 32($sp)
lw $t1 36($t0)
sw $t1 36($sp)
lw $t1 40($t0)
sw $t1 40($sp)
lw $t1 44($t0)
sw $t1 44($sp)
jal sum
addi $sp $sp 48
addi $sp $sp 4

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

li $v0 1
or $a0 $s7 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("Expected value         : 138\n")
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
string0:    .asciiz    "The sum of the array is: "
string1:    .asciiz    "Expected value         : 138\n"


.align 2

    Global_Area:

