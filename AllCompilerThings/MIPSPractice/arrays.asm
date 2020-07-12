.data
	myArray: .space 16
	anotherArray: .word 100:3 # 3 elements each with a value of 100
.text
	main:
		addi $s0, $0, 3
		addi $s1, $0, 7
		addi $s2, $0, 9
		addi $s3, $0, 1
		
		# Start the index at 0
		addi $t0, $0, 0
		
		sw $s0, myArray($t0)
		addi $t0, $t0, 4
		sw $s1, myArray($t0)
		addi $t0, $t0, 4
		sw $s2, myArray($t0)
		addi $t0, $t0, 4
		sw $s3, myArray($t0)
		
		lw $t6, myArray($0)
		# To access different parts of the array, the register arg in myArray needs to be augmented by the data type size
		# so add 4 to the register arg.
		
		li $v0, 1
		addi $a0, $t6, 0
		syscall
		
		li $v0, 10
		syscall