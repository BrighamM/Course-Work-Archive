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

moveTower:
or $fp $sp $zero
lw $t0 0($fp)
li $t1 1
seq $t0 $t0 $t1
abs $t0 $t0
sge $t0 $t0 1
beq $t0 1 ifBlock0
b elseBlock0
b endBlock0
ifBlock0:
#WRITE("Move ", disk, " from ", source, " to ", dest, _ASCIIVAL_=> 10)
la $t1 string0
li $v0 4
move $a0 $t1
syscall
lw $t1 0($fp)
li $v0 1
or $a0 $t1 $zero
syscall
la $t1 string1
li $v0 4
move $a0 $t1
syscall
lw $t1 4($fp)
li $v0 11
move $a0 $t1
syscall
la $t1 string2
li $v0 4
move $a0 $t1
syscall
lw $t1 8($fp)
li $v0 11
move $a0 $t1
syscall
li $t1 '\n'
li $v0 11
move $a0 $t1
syscall

b endBlock0
elseBlock0:

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

addi $sp $sp -16
lw $t1 0($fp)
li $t2 1
sub $t1 $t1 $t2
sw $t1 0($sp) 
lw $t1 4($fp)
sw $t1 4($sp) 
lw $t1 12($fp)
sw $t1 8($sp) 
lw $t1 8($fp)
sw $t1 12($sp) 
jal moveTower
lw $fp 116($sp)
addi $sp $sp 16

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

#WRITE("Move ", disk, " from ", source, " to ", dest, _ASCIIVAL_=> 10)
la $t1 string0
li $v0 4
move $a0 $t1
syscall
lw $t1 0($fp)
li $v0 1
or $a0 $t1 $zero
syscall
la $t1 string1
li $v0 4
move $a0 $t1
syscall
lw $t1 4($fp)
li $v0 11
move $a0 $t1
syscall
la $t1 string2
li $v0 4
move $a0 $t1
syscall
lw $t1 8($fp)
li $v0 11
move $a0 $t1
syscall
li $t1 '\n'
li $v0 11
move $a0 $t1
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

addi $sp $sp -16
lw $t1 0($fp)
li $t2 1
sub $t1 $t1 $t2
sw $t1 0($sp) 
lw $t1 12($fp)
sw $t1 4($sp) 
lw $t1 8($fp)
sw $t1 8($sp) 
lw $t1 4($fp)
sw $t1 12($sp) 
jal moveTower
lw $fp 116($sp)
addi $sp $sp 16

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

b endBlock0
endBlock0:
jr $ra

main:

#WRITE("Enter number of disks:")
la $t0 string3
li $v0 4
move $a0 $t0
syscall

#READ(disks)
li $v0 5 
syscall
sw $v0 0($gp)

#WRITE("Moving ", disks, " disks from tower A to tower B with tower C helping\n")
la $t0 string4
li $v0 4
move $a0 $t0
syscall
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string5
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

addi $sp $sp -16
lw $t0 0($gp)
sw $t0 0($sp) 
li $t0 'A'
sw $t0 4($sp) 
li $t0 'B'
sw $t0 8($sp) 
li $t0 'C'
sw $t0 12($sp) 
jal moveTower
lw $fp 116($sp)
addi $sp $sp 16

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

#WRITE("Done\n")
la $t0 string6
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
string0:    .asciiz    "Move "
string1:    .asciiz    " from "
string2:    .asciiz    " to "
string3:    .asciiz    "Enter number of disks:"
string4:    .asciiz    "Moving "
string5:    .asciiz    " disks from tower A to tower B with tower C helping\n"
string6:    .asciiz    "Done\n"


.align 2

    Global_Area:

