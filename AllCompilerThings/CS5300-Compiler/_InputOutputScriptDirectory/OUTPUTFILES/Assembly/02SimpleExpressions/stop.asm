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

#WRITE("42 should write once, not twice\n")
la $t0 string0
li $v0 4
move $a0 $t0
syscall

#WRITE(number)
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
syscall

#STOP
li $v0 10
syscall

#WRITE(number)
lw $t0 0($gp)
li $v0 1
or $a0 $t0 $zero
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
string0:    .asciiz    "42 should write once, not twice\n"


.align 2

    Global_Area:

