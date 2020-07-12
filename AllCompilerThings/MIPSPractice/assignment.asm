.text

#	li $v0, 1
#	lw $a0, number 
#	syscall
	la $gp, Global_Area

	j main
	
main:
	li $t0, 42
	sw $t0, 0($gp)

	li $v0, 1
	lw $t0, 0($gp)
	or $a0, $t0, $0 
	syscall


.data

	Global_Area: 

