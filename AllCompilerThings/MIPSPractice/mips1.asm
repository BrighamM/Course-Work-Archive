.text
	li $v0, 4 # We do this to signal the system that we want to print something to the screen.
	la $a0, myMessage
	syscall

.data
	myMessage: .asciiz "Hello Worlds\n"






