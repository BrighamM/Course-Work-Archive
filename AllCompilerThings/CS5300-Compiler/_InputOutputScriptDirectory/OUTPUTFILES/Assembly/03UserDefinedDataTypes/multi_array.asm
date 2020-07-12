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

#g [0]  [0]  := 0
li $t0 0
la $t1 0($gp)
li $t2 0
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 0
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [0]  [1]  := 0
li $t0 0
la $t1 0($gp)
li $t2 0
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 1
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [0]  [2]  := 0
li $t0 0
la $t1 0($gp)
li $t2 0
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 2
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [0]  [3]  := 0
li $t0 0
la $t1 0($gp)
li $t2 0
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 3
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [1]  [0]  := 0
li $t0 0
la $t1 0($gp)
li $t2 1
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 0
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [1]  [1]  := 1
li $t0 1
la $t1 0($gp)
li $t2 1
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 1
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [1]  [2]  := 2
li $t0 2
la $t1 0($gp)
li $t2 1
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 2
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [1]  [3]  := 3
li $t0 3
la $t1 0($gp)
li $t2 1
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 3
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [2]  [0]  := 0
li $t0 0
la $t1 0($gp)
li $t2 2
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 0
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [2]  [1]  := 2
li $t0 2
la $t1 0($gp)
li $t2 2
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 1
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [2]  [2]  := 4
li $t0 4
la $t1 0($gp)
li $t2 2
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 2
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [2]  [3]  := 6
li $t0 6
la $t1 0($gp)
li $t2 2
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 3
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [3]  [0]  := 0
li $t0 0
la $t1 0($gp)
li $t2 3
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 0
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [3]  [1]  := 3
li $t0 3
la $t1 0($gp)
li $t2 3
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 1
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [3]  [2]  := 6
li $t0 6
la $t1 0($gp)
li $t2 3
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 2
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#g [3]  [3]  := 9
li $t0 9
la $t1 0($gp)
li $t2 3
subi $t2 $t2 0
li $t3 16
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
li $t1 3
subi $t1 $t1 0
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#i := 2
li $t0 2
la $t1 80($gp)
sw $t0 ($t1) 

#r := g [i] 
la $t0 0($gp)
lw $t1 80($gp)
subi $t1 $t1 0
li $t2 16
mult $t1 $t2
mflo $t1
add $t1 $t1 $t0
la $t0 64($gp)
lw $t2 0($t1)
sw $t2 0($t0)
lw $t2 4($t1)
sw $t2 4($t0)
lw $t2 8($t1)
sw $t2 8($t0)
lw $t2 12($t1)
sw $t2 12($t0)
#j := r [i] 
la $t1 64($gp)
lw $t0 80($gp)
subi $t0 $t0 0
li $t2 4
mult $t0 $t2
mflo $t0
add $t0 $t0 $t1
lw $t0 ($t0) 
la $t1 84($gp)
sw $t0 ($t1) 

#WRITE("Result   :", j, _ASCIIVAL_=> 10)
la $t0 string0
li $v0 4
move $a0 $t0
syscall
lw $t0 84($gp)
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("Expected :", 4, _ASCIIVAL_=> 10)
la $t0 string1
li $v0 4
move $a0 $t0
syscall
li $t0 4
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
string0:    .asciiz    "Result   :"
string1:    .asciiz    "Expected :"


.align 2

    Global_Area:

