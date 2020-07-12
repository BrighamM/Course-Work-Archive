.data

.text
	main:
	
		while:
			bgt $zero, $0, exit
			
			j while
		exit: