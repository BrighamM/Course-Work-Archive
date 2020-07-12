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

swap:
or $fp $sp $zero
#t := a
lw $t0 0($fp)
la $t1 8($fp)
sw $t0 ($t1) 

#a := b
lw $t0 4($fp)
la $t1 0($fp)
sw $t0 ($t1) 

#b := t
lw $t0 8($fp)
la $t1 4($fp)
sw $t0 ($t1) 

jr $ra

main:

#a := 1
li $t0 1
la $t1 0($gp)
sw $t0 ($t1) 

#b := 0
li $t0 0
la $t1 4($gp)
sw $t0 ($t1) 

#WRITE(a, b, _ASCIIVAL_=> 10)
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
lw $t0 4($gp)
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
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

addi $sp $sp -8
lw $t0 0($gp)
sw $t0 0($sp) 
lw $t0 4($gp)
sw $t0 4($sp) 
jal swap
lw $fp 108($sp)
lw $t0 0($sp) 
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 4($sp) 
la $t1 4($gp)
sw $t0 ($t1) 

addi $sp $sp 8

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
lw $s7 40($sp)
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

#WRITE(a, b, _ASCIIVAL_=> 10)
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
lw $t0 4($gp)
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
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


.align 2

    Global_Area:

