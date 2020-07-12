
# There are some critical things to remember.
# I have access to the following registers: $zero, $v0 - $v1 (Return Values), $a0 - $a3 (Arguments),
#											===== 6 registers plus one for the zero =====
#
#											$t0 - $t9, $s0 - $s7, $gp, $sp, $fp, $ra, ====== 22 (10 temps, 8 saves)
#											And in some special cases hi and lo

.data
	firstPrintMessage:  .asciiz "This message is of type: asciiz \n"
	firstPrintChar: 	.byte 'B'
	firstPrintNum: 		.word 33
	numberToAddOne: 	.word 111
	numberToAddTwo:		.word 33
	messageToPrintInFunctionCall: .asciiz "I am inside the function! \n"
	userTextInput: 		.space 20
.text
	main:
	# For this first part we told the system to print a string (4)
	#li $v0, 4 # We are telling the assembler: 1. To print a string. 2. The address for the string will be in $a0
	#la $a0, firstPrintMessage # Put the message we want to print into $a0
	#syscall # Do the thing!
	
	# Now lets print a char (4) remember an integer is a byte, so is a char but it is still a string
	#li $v0, 4
	#la $a0, firstPrintChar
	#syscall
	
	#li $v0, 1
	#lw $a0, firstPrintNum #it is a word, so load it
	#syscall
	
	
	# To add ints we need to load them into some registers
	lw $t0, numberToAddOne($0)
	lw $t1, numberToAddTwo($0)
	
	mul $a0, $t0, $t1
	li $v0, 1
	syscall
	
	li $v0, 5 # Get Integer input from the user, and store the result inside of $v0
	syscall
	
	li $v0, 8 # Get text string from the user
	la $a0, userTextInput # Put the text string inside here
	li $a1, 20 # This specifies how big the string is that is going to be read in
	syscall # do the thing
	
	
	
	jal firstFunctionToCall
	
	
	li $v0, 10
	syscall
#########################################################################################################
# Discussion points regarding calling functions, when we are using an s register in a function, by convention
# The function cannot modify the value in the s register. To work with this, before anything else in the called
# function we are going to save off the s registers into the stack. when we are done with the function call
# we reset the vals in the s register to the respective values saved off onto the stack.
# Say we saved an int into register $s0
# Then:
# addi $sp, $sp, -4
# sw $s0, 0($sp)
#
# And when we are done
# lw $s0, 0($sp)
# addi $sp, $sp, 4


# Going yet further, say you had a function that is going to end up calling other functions.
# Well whenever you call a function the very next line to execute is stored in $ra, thus $ra MUST be 
# preserved whenever a new fucntion is called.
#
#
#
#
#
#
#
	firstFunctionToCall: 
		li $v0, 4
		la $a0, messageToPrintInFunctionCall
		syscall
		
		jr $ra
		
	
	
	
	
	
	
	
	
	
	
	
	
	
	
