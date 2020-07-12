.data
	notEqualsMessage: .asciiz "The Janks ain't equal!"
	systemTermMessage: .asciiz "The System has been shooted!"

.text
	main:
		addi $t1, $0, 111
		addi $t2, $0, 111
		
		bne $t1, $t2 notEquals
		
		slt $t0, $t1, $t2
		
		li $v0, 4
		la $a0, systemTermMessage
		syscall
		
		li $v0, 10
		syscall
		
	notEquals:
		li $v0, 4
		la $a0, notEqualsMessage
		syscall