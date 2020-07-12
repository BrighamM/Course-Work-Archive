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

#a [1]  := 40
li $t0 40
la $t1 0($gp)
li $t2 1
subi $t2 $t2 1
li $t3 4
mult $t2 $t3
mflo $t2
add $t2 $t2 $t1
sw $t0 ($t2) 

#x := 2
li $t0 2
la $t2 12($gp)
sw $t0 ($t2) 

#a [x]  := x
lw $t0 12($gp)
la $t2 0($gp)
lw $t1 12($gp)
subi $t1 $t1 1
li $t3 4
mult $t1 $t3
mflo $t1
add $t1 $t1 $t2
sw $t0 ($t1) 

#a [3]  := a [1] +a [2] 
la $t0 0($gp)
li $t1 1
subi $t1 $t1 1
li $t2 4
mult $t1 $t2
mflo $t1
add $t1 $t1 $t0
lw $t1 ($t1) 
la $t0 0($gp)
li $t2 2
subi $t2 $t2 1
li $t3 4
mult $t2 $t3
mflo $t2
add $t2 $t2 $t0
lw $t2 ($t2) 
add $t1 $t1 $t2
la $t2 0($gp)
li $t0 3
subi $t0 $t0 1
li $t3 4
mult $t0 $t3
mflo $t0
add $t0 $t0 $t2
sw $t1 ($t0) 

#WRITE("Result  : ", a [3] , _ASCIIVAL_=> 10)
la $t1 string0
li $v0 4
move $a0 $t1
syscall
la $t1 0($gp)
li $t0 3
subi $t0 $t0 1
li $t2 4
mult $t0 $t2
mflo $t0
add $t0 $t0 $t1
lw $t0 ($t0) 
li $v0 1
or $a0 $t0 $zero
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("Expected: ", 42, _ASCIIVAL_=> 10)
la $t0 string1
li $v0 4
move $a0 $t0
syscall
li $t0 42
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
string0:    .asciiz    "Result  : "
string1:    .asciiz    "Expected: "


.align 2

    Global_Area:

