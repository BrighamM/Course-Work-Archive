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

#x := 1
li $t0 1
la $t1 24($gp)
sw $t0 ($t1) 

#y := 2
li $t0 2
la $t1 28($gp)
sw $t0 ($t1) 

#z := 3
li $t0 3
la $t1 32($gp)
sw $t0 ($t1) 

#p.x  := x*y
lw $t0 24($gp)
lw $t1 28($gp)
mult  $t0 $t1
mflo $t0
la $t1 0($gp)
addi $t1 $t1 0
sw $t0 ($t1) 

#p.y  := y*z
lw $t0 28($gp)
lw $t1 32($gp)
mult  $t0 $t1
mflo $t0
la $t1 0($gp)
addi $t1 $t1 4
sw $t0 ($t1) 

#p.z  := z*x
lw $t0 32($gp)
lw $t1 24($gp)
mult  $t0 $t1
mflo $t0
la $t1 0($gp)
addi $t1 $t1 8
sw $t0 ($t1) 

#p.q .x  := 17
li $t0 17
la $t1 0($gp)
addi $t1 $t1 12
addi $t1 $t1 0
sw $t0 ($t1) 

#p.q .y  := 18
li $t0 18
la $t1 0($gp)
addi $t1 $t1 12
addi $t1 $t1 4
sw $t0 ($t1) 

#p.q .z  := 19
li $t0 19
la $t1 0($gp)
addi $t1 $t1 12
addi $t1 $t1 8
sw $t0 ($t1) 

#p.q .x  := p.q .y 
la $t0 0($gp)
addi $t0 $t0 12
addi $t0 $t0 4
lw $t0 ($t0) 
la $t1 0($gp)
addi $t1 $t1 12
addi $t1 $t1 0
sw $t0 ($t1) 

#p.q .y  := p.q .z 
la $t0 0($gp)
addi $t0 $t0 12
addi $t0 $t0 8
lw $t0 ($t0) 
la $t1 0($gp)
addi $t1 $t1 12
addi $t1 $t1 4
sw $t0 ($t1) 

#p.q .z  := p.q .x 
la $t0 0($gp)
addi $t0 $t0 12
addi $t0 $t0 0
lw $t0 ($t0) 
la $t1 0($gp)
addi $t1 $t1 12
addi $t1 $t1 8
sw $t0 ($t1) 

#WRITE("Result  : ")
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(p.x , _ASCIIVAL_=> 32, p.y , _ASCIIVAL_=> 32, p.z , _ASCIIVAL_=> 32, p.q .x , _ASCIIVAL_=> 32, p.q .y , _ASCIIVAL_=> 32, p.q .z , _ASCIIVAL_=> 10)
la $t0 0($gp)
addi $t0 $t0 0
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 ' '
li $v0 11
move $a0 $t0
syscall
la $t0 0($gp)
addi $t0 $t0 4
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 ' '
li $v0 11
move $a0 $t0
syscall
la $t0 0($gp)
addi $t0 $t0 8
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 ' '
li $v0 11
move $a0 $t0
syscall
la $t0 0($gp)
addi $t0 $t0 12
addi $t0 $t0 0
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 ' '
li $v0 11
move $a0 $t0
syscall
la $t0 0($gp)
addi $t0 $t0 12
addi $t0 $t0 4
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 ' '
li $v0 11
move $a0 $t0
syscall
la $t0 0($gp)
addi $t0 $t0 12
addi $t0 $t0 8
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("Expected: 2 6 3 18 19 18\n")
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
string0:    .asciiz    "Result  : "
string1:    .asciiz    "Expected: 2 6 3 18 19 18\n"


.align 2

    Global_Area:

