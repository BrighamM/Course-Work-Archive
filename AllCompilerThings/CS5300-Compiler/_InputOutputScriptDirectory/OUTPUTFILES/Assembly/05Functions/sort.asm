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

rand:
or $fp $sp $zero
#seed := (8121*seed+28411)
li $t0 8121
lw $t1 0($gp)
mult  $t0 $t1
mflo $t0
li $t1 28411
add $t0 $t0 $t1
la $t1 0($gp)
sw $t0 ($t1) 

#result := seed/134456
lw $t0 0($gp)
li $t1 134456
div  $t0 $t1
mflo $t0
la $t1 0($fp)
sw $t0 ($t1) 

#seed := seed%134456
lw $t0 0($gp)
li $t1 134456
div  $t0 $t1
mfhi $t0
la $t1 0($gp)
sw $t0 ($t1) 

lw $t0 0($fp)
or $s7 $t0 $zero
jr $ra

print:
or $fp $sp $zero
#i := 0
li $t0 0
la $t1 404($fp)
sw $t0 ($t1) 

lw $t0 404($fp)
la $t1 404($fp)
li $t2 100
li $t3 1
sub $t2 $t2 $t3
ForLoop0: 
bgt $t0 $t2 Exit0
#WRITE(a [i] , _ASCIIVAL_=> 32)
la $t3 0($fp)
lw $t4 404($fp)
subi $t4 $t4 0
li $t5 4
mult $t4 $t5
mflo $t4
add $t4 $t4 $t3
lw $t4 ($t4) 
li $v0 1
or $a0 $t4 $zero
syscall
li $t4 ' '
li $v0 11
move $a0 $t4
syscall

addi $t0  $t0 1
sw $t0 ($t1) 
j ForLoop0
Exit0: 
#WRITE(a [LIST_MAX] )
la $t0 0($fp)
li $t1 100
subi $t1 $t1 0
li $t2 4
mult $t1 $t2
mflo $t1
add $t1 $t1 $t0
lw $t1 ($t1) 
li $v0 1
or $a0 $t1 $zero
syscall

jr $ra

rfill:
or $fp $sp $zero
#i := 0
li $t1 0
la $t0 404($fp)
sw $t1 ($t0) 

lw $t1 404($fp)
la $t0 404($fp)
li $t2 100
ForLoop1: 
bgt $t1 $t2 Exit1
#a [i]  := rand()%1000

# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -4
jal rand
addi $sp $sp 4

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

li $t4 1000
div  $s7 $t4
mfhi $s7
la $t4 0($fp)
lw $t3 404($fp)
subi $t3 $t3 0
li $t5 4
mult $t3 $t5
mflo $t3
add $t3 $t3 $t4
sw $s7 ($t3) 

addi $t1  $t1 1
sw $t1 ($t0) 
j ForLoop1
Exit1: 
jr $ra

swap:
or $fp $sp $zero
#t := a
lw $t1 0($fp)
la $t0 8($fp)
sw $t1 ($t0) 

#a := b
lw $t1 4($fp)
la $t0 0($fp)
sw $t1 ($t0) 

#b := t
lw $t1 8($fp)
la $t0 4($fp)
sw $t1 ($t0) 

jr $ra

sort:
or $fp $sp $zero
#i := 0
li $t1 0
la $t0 412($fp)
sw $t1 ($t0) 

lw $t1 412($fp)
la $t0 412($fp)
li $t2 100
ForLoop2: 
bgt $t1 $t2 Exit2
#j := i+1
lw $t3 412($fp)
li $t4 1
add $t3 $t3 $t4
la $t4 416($fp)
sw $t3 ($t4) 

lw $t3 416($fp)
la $t4 416($fp)
li $t5 100
ForLoop3: 
bgt $t3 $t5 Exit3
la $t6 0($fp)
lw $t7 412($fp)
subi $t7 $t7 0
li $t8 4
mult $t7 $t8
mflo $t7
add $t7 $t7 $t6
lw $t7 ($t7) 
la $t6 0($fp)
lw $t8 416($fp)
subi $t8 $t8 0
li $t9 4
mult $t8 $t9
mflo $t8
add $t8 $t8 $t6
lw $t8 ($t8) 
sgt $t7 $t7 $t8
abs $t7 $t7
sge $t7 $t7 1
beq $t7 1 ifBlock0
b endBlock0
ifBlock0:

# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -8
la $t8 0($fp)
lw $t6 412($fp)
subi $t6 $t6 0
li $t9 4
mult $t6 $t9
mflo $t6
add $t6 $t6 $t8
lw $t6 ($t6) 
sw $t6 0($sp) 
la $t6 0($fp)
lw $t8 416($fp)
subi $t8 $t8 0
li $t9 4
mult $t8 $t9
mflo $t8
add $t8 $t8 $t6
lw $t8 ($t8) 
sw $t8 4($sp) 
jal swap
lw $fp 108($sp)
lw $t8 0($sp) 
la $t6 0($fp)
lw $t9 412($fp)
subi $t9 $t9 0
li $s0 4
mult $t9 $s0
mflo $t9
add $t9 $t9 $t6
sw $t8 ($t9) 

lw $t8 4($sp) 
la $t9 0($fp)
lw $t6 416($fp)
subi $t6 $t6 0
li $s0 4
mult $t6 $s0
mflo $t6
add $t6 $t6 $t9
sw $t8 ($t6) 

addi $sp $sp 8

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s7 40($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

b endBlock0
endBlock0:
addi $t3  $t3 1
sw $t3 ($t4) 
j ForLoop3
Exit3: 
addi $t1  $t1 1
sw $t1 ($t0) 
j ForLoop2
Exit2: 
jr $ra

main:


# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -404
la $t1 4($gp)
lw $t0 0($t1)
sw $t0 0($sp)
lw $t0 4($t1)
sw $t0 4($sp)
lw $t0 8($t1)
sw $t0 8($sp)
lw $t0 12($t1)
sw $t0 12($sp)
lw $t0 16($t1)
sw $t0 16($sp)
lw $t0 20($t1)
sw $t0 20($sp)
lw $t0 24($t1)
sw $t0 24($sp)
lw $t0 28($t1)
sw $t0 28($sp)
lw $t0 32($t1)
sw $t0 32($sp)
lw $t0 36($t1)
sw $t0 36($sp)
lw $t0 40($t1)
sw $t0 40($sp)
lw $t0 44($t1)
sw $t0 44($sp)
lw $t0 48($t1)
sw $t0 48($sp)
lw $t0 52($t1)
sw $t0 52($sp)
lw $t0 56($t1)
sw $t0 56($sp)
lw $t0 60($t1)
sw $t0 60($sp)
lw $t0 64($t1)
sw $t0 64($sp)
lw $t0 68($t1)
sw $t0 68($sp)
lw $t0 72($t1)
sw $t0 72($sp)
lw $t0 76($t1)
sw $t0 76($sp)
lw $t0 80($t1)
sw $t0 80($sp)
lw $t0 84($t1)
sw $t0 84($sp)
lw $t0 88($t1)
sw $t0 88($sp)
lw $t0 92($t1)
sw $t0 92($sp)
lw $t0 96($t1)
sw $t0 96($sp)
lw $t0 100($t1)
sw $t0 100($sp)
lw $t0 104($t1)
sw $t0 104($sp)
lw $t0 108($t1)
sw $t0 108($sp)
lw $t0 112($t1)
sw $t0 112($sp)
lw $t0 116($t1)
sw $t0 116($sp)
lw $t0 120($t1)
sw $t0 120($sp)
lw $t0 124($t1)
sw $t0 124($sp)
lw $t0 128($t1)
sw $t0 128($sp)
lw $t0 132($t1)
sw $t0 132($sp)
lw $t0 136($t1)
sw $t0 136($sp)
lw $t0 140($t1)
sw $t0 140($sp)
lw $t0 144($t1)
sw $t0 144($sp)
lw $t0 148($t1)
sw $t0 148($sp)
lw $t0 152($t1)
sw $t0 152($sp)
lw $t0 156($t1)
sw $t0 156($sp)
lw $t0 160($t1)
sw $t0 160($sp)
lw $t0 164($t1)
sw $t0 164($sp)
lw $t0 168($t1)
sw $t0 168($sp)
lw $t0 172($t1)
sw $t0 172($sp)
lw $t0 176($t1)
sw $t0 176($sp)
lw $t0 180($t1)
sw $t0 180($sp)
lw $t0 184($t1)
sw $t0 184($sp)
lw $t0 188($t1)
sw $t0 188($sp)
lw $t0 192($t1)
sw $t0 192($sp)
lw $t0 196($t1)
sw $t0 196($sp)
lw $t0 200($t1)
sw $t0 200($sp)
lw $t0 204($t1)
sw $t0 204($sp)
lw $t0 208($t1)
sw $t0 208($sp)
lw $t0 212($t1)
sw $t0 212($sp)
lw $t0 216($t1)
sw $t0 216($sp)
lw $t0 220($t1)
sw $t0 220($sp)
lw $t0 224($t1)
sw $t0 224($sp)
lw $t0 228($t1)
sw $t0 228($sp)
lw $t0 232($t1)
sw $t0 232($sp)
lw $t0 236($t1)
sw $t0 236($sp)
lw $t0 240($t1)
sw $t0 240($sp)
lw $t0 244($t1)
sw $t0 244($sp)
lw $t0 248($t1)
sw $t0 248($sp)
lw $t0 252($t1)
sw $t0 252($sp)
lw $t0 256($t1)
sw $t0 256($sp)
lw $t0 260($t1)
sw $t0 260($sp)
lw $t0 264($t1)
sw $t0 264($sp)
lw $t0 268($t1)
sw $t0 268($sp)
lw $t0 272($t1)
sw $t0 272($sp)
lw $t0 276($t1)
sw $t0 276($sp)
lw $t0 280($t1)
sw $t0 280($sp)
lw $t0 284($t1)
sw $t0 284($sp)
lw $t0 288($t1)
sw $t0 288($sp)
lw $t0 292($t1)
sw $t0 292($sp)
lw $t0 296($t1)
sw $t0 296($sp)
lw $t0 300($t1)
sw $t0 300($sp)
lw $t0 304($t1)
sw $t0 304($sp)
lw $t0 308($t1)
sw $t0 308($sp)
lw $t0 312($t1)
sw $t0 312($sp)
lw $t0 316($t1)
sw $t0 316($sp)
lw $t0 320($t1)
sw $t0 320($sp)
lw $t0 324($t1)
sw $t0 324($sp)
lw $t0 328($t1)
sw $t0 328($sp)
lw $t0 332($t1)
sw $t0 332($sp)
lw $t0 336($t1)
sw $t0 336($sp)
lw $t0 340($t1)
sw $t0 340($sp)
lw $t0 344($t1)
sw $t0 344($sp)
lw $t0 348($t1)
sw $t0 348($sp)
lw $t0 352($t1)
sw $t0 352($sp)
lw $t0 356($t1)
sw $t0 356($sp)
lw $t0 360($t1)
sw $t0 360($sp)
lw $t0 364($t1)
sw $t0 364($sp)
lw $t0 368($t1)
sw $t0 368($sp)
lw $t0 372($t1)
sw $t0 372($sp)
lw $t0 376($t1)
sw $t0 376($sp)
lw $t0 380($t1)
sw $t0 380($sp)
lw $t0 384($t1)
sw $t0 384($sp)
lw $t0 388($t1)
sw $t0 388($sp)
lw $t0 392($t1)
sw $t0 392($sp)
lw $t0 396($t1)
sw $t0 396($sp)
lw $t0 400($t1)
sw $t0 400($sp)
jal rfill
lw $fp 504($sp)
la $t1 4($gp)
lw $t0 0($sp) 
sw $t0 0($t1) 
lw $t0 4($sp) 
sw $t0 4($t1) 
lw $t0 8($sp) 
sw $t0 8($t1) 
lw $t0 12($sp) 
sw $t0 12($t1) 
lw $t0 16($sp) 
sw $t0 16($t1) 
lw $t0 20($sp) 
sw $t0 20($t1) 
lw $t0 24($sp) 
sw $t0 24($t1) 
lw $t0 28($sp) 
sw $t0 28($t1) 
lw $t0 32($sp) 
sw $t0 32($t1) 
lw $t0 36($sp) 
sw $t0 36($t1) 
lw $t0 40($sp) 
sw $t0 40($t1) 
lw $t0 44($sp) 
sw $t0 44($t1) 
lw $t0 48($sp) 
sw $t0 48($t1) 
lw $t0 52($sp) 
sw $t0 52($t1) 
lw $t0 56($sp) 
sw $t0 56($t1) 
lw $t0 60($sp) 
sw $t0 60($t1) 
lw $t0 64($sp) 
sw $t0 64($t1) 
lw $t0 68($sp) 
sw $t0 68($t1) 
lw $t0 72($sp) 
sw $t0 72($t1) 
lw $t0 76($sp) 
sw $t0 76($t1) 
lw $t0 80($sp) 
sw $t0 80($t1) 
lw $t0 84($sp) 
sw $t0 84($t1) 
lw $t0 88($sp) 
sw $t0 88($t1) 
lw $t0 92($sp) 
sw $t0 92($t1) 
lw $t0 96($sp) 
sw $t0 96($t1) 
lw $t0 100($sp) 
sw $t0 100($t1) 
lw $t0 104($sp) 
sw $t0 104($t1) 
lw $t0 108($sp) 
sw $t0 108($t1) 
lw $t0 112($sp) 
sw $t0 112($t1) 
lw $t0 116($sp) 
sw $t0 116($t1) 
lw $t0 120($sp) 
sw $t0 120($t1) 
lw $t0 124($sp) 
sw $t0 124($t1) 
lw $t0 128($sp) 
sw $t0 128($t1) 
lw $t0 132($sp) 
sw $t0 132($t1) 
lw $t0 136($sp) 
sw $t0 136($t1) 
lw $t0 140($sp) 
sw $t0 140($t1) 
lw $t0 144($sp) 
sw $t0 144($t1) 
lw $t0 148($sp) 
sw $t0 148($t1) 
lw $t0 152($sp) 
sw $t0 152($t1) 
lw $t0 156($sp) 
sw $t0 156($t1) 
lw $t0 160($sp) 
sw $t0 160($t1) 
lw $t0 164($sp) 
sw $t0 164($t1) 
lw $t0 168($sp) 
sw $t0 168($t1) 
lw $t0 172($sp) 
sw $t0 172($t1) 
lw $t0 176($sp) 
sw $t0 176($t1) 
lw $t0 180($sp) 
sw $t0 180($t1) 
lw $t0 184($sp) 
sw $t0 184($t1) 
lw $t0 188($sp) 
sw $t0 188($t1) 
lw $t0 192($sp) 
sw $t0 192($t1) 
lw $t0 196($sp) 
sw $t0 196($t1) 
lw $t0 200($sp) 
sw $t0 200($t1) 
lw $t0 204($sp) 
sw $t0 204($t1) 
lw $t0 208($sp) 
sw $t0 208($t1) 
lw $t0 212($sp) 
sw $t0 212($t1) 
lw $t0 216($sp) 
sw $t0 216($t1) 
lw $t0 220($sp) 
sw $t0 220($t1) 
lw $t0 224($sp) 
sw $t0 224($t1) 
lw $t0 228($sp) 
sw $t0 228($t1) 
lw $t0 232($sp) 
sw $t0 232($t1) 
lw $t0 236($sp) 
sw $t0 236($t1) 
lw $t0 240($sp) 
sw $t0 240($t1) 
lw $t0 244($sp) 
sw $t0 244($t1) 
lw $t0 248($sp) 
sw $t0 248($t1) 
lw $t0 252($sp) 
sw $t0 252($t1) 
lw $t0 256($sp) 
sw $t0 256($t1) 
lw $t0 260($sp) 
sw $t0 260($t1) 
lw $t0 264($sp) 
sw $t0 264($t1) 
lw $t0 268($sp) 
sw $t0 268($t1) 
lw $t0 272($sp) 
sw $t0 272($t1) 
lw $t0 276($sp) 
sw $t0 276($t1) 
lw $t0 280($sp) 
sw $t0 280($t1) 
lw $t0 284($sp) 
sw $t0 284($t1) 
lw $t0 288($sp) 
sw $t0 288($t1) 
lw $t0 292($sp) 
sw $t0 292($t1) 
lw $t0 296($sp) 
sw $t0 296($t1) 
lw $t0 300($sp) 
sw $t0 300($t1) 
lw $t0 304($sp) 
sw $t0 304($t1) 
lw $t0 308($sp) 
sw $t0 308($t1) 
lw $t0 312($sp) 
sw $t0 312($t1) 
lw $t0 316($sp) 
sw $t0 316($t1) 
lw $t0 320($sp) 
sw $t0 320($t1) 
lw $t0 324($sp) 
sw $t0 324($t1) 
lw $t0 328($sp) 
sw $t0 328($t1) 
lw $t0 332($sp) 
sw $t0 332($t1) 
lw $t0 336($sp) 
sw $t0 336($t1) 
lw $t0 340($sp) 
sw $t0 340($t1) 
lw $t0 344($sp) 
sw $t0 344($t1) 
lw $t0 348($sp) 
sw $t0 348($t1) 
lw $t0 352($sp) 
sw $t0 352($t1) 
lw $t0 356($sp) 
sw $t0 356($t1) 
lw $t0 360($sp) 
sw $t0 360($t1) 
lw $t0 364($sp) 
sw $t0 364($t1) 
lw $t0 368($sp) 
sw $t0 368($t1) 
lw $t0 372($sp) 
sw $t0 372($t1) 
lw $t0 376($sp) 
sw $t0 376($t1) 
lw $t0 380($sp) 
sw $t0 380($t1) 
lw $t0 384($sp) 
sw $t0 384($t1) 
lw $t0 388($sp) 
sw $t0 388($t1) 
lw $t0 392($sp) 
sw $t0 392($t1) 
lw $t0 396($sp) 
sw $t0 396($t1) 
lw $t0 400($sp) 
sw $t0 400($t1) 
addi $sp $sp 404

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s7 40($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

#WRITE("Random: ")
la $t1 string0
li $v0 4
move $a0 $t1
syscall


# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -404
la $t1 4($gp)
lw $t0 0($t1)
sw $t0 0($sp)
lw $t0 4($t1)
sw $t0 4($sp)
lw $t0 8($t1)
sw $t0 8($sp)
lw $t0 12($t1)
sw $t0 12($sp)
lw $t0 16($t1)
sw $t0 16($sp)
lw $t0 20($t1)
sw $t0 20($sp)
lw $t0 24($t1)
sw $t0 24($sp)
lw $t0 28($t1)
sw $t0 28($sp)
lw $t0 32($t1)
sw $t0 32($sp)
lw $t0 36($t1)
sw $t0 36($sp)
lw $t0 40($t1)
sw $t0 40($sp)
lw $t0 44($t1)
sw $t0 44($sp)
lw $t0 48($t1)
sw $t0 48($sp)
lw $t0 52($t1)
sw $t0 52($sp)
lw $t0 56($t1)
sw $t0 56($sp)
lw $t0 60($t1)
sw $t0 60($sp)
lw $t0 64($t1)
sw $t0 64($sp)
lw $t0 68($t1)
sw $t0 68($sp)
lw $t0 72($t1)
sw $t0 72($sp)
lw $t0 76($t1)
sw $t0 76($sp)
lw $t0 80($t1)
sw $t0 80($sp)
lw $t0 84($t1)
sw $t0 84($sp)
lw $t0 88($t1)
sw $t0 88($sp)
lw $t0 92($t1)
sw $t0 92($sp)
lw $t0 96($t1)
sw $t0 96($sp)
lw $t0 100($t1)
sw $t0 100($sp)
lw $t0 104($t1)
sw $t0 104($sp)
lw $t0 108($t1)
sw $t0 108($sp)
lw $t0 112($t1)
sw $t0 112($sp)
lw $t0 116($t1)
sw $t0 116($sp)
lw $t0 120($t1)
sw $t0 120($sp)
lw $t0 124($t1)
sw $t0 124($sp)
lw $t0 128($t1)
sw $t0 128($sp)
lw $t0 132($t1)
sw $t0 132($sp)
lw $t0 136($t1)
sw $t0 136($sp)
lw $t0 140($t1)
sw $t0 140($sp)
lw $t0 144($t1)
sw $t0 144($sp)
lw $t0 148($t1)
sw $t0 148($sp)
lw $t0 152($t1)
sw $t0 152($sp)
lw $t0 156($t1)
sw $t0 156($sp)
lw $t0 160($t1)
sw $t0 160($sp)
lw $t0 164($t1)
sw $t0 164($sp)
lw $t0 168($t1)
sw $t0 168($sp)
lw $t0 172($t1)
sw $t0 172($sp)
lw $t0 176($t1)
sw $t0 176($sp)
lw $t0 180($t1)
sw $t0 180($sp)
lw $t0 184($t1)
sw $t0 184($sp)
lw $t0 188($t1)
sw $t0 188($sp)
lw $t0 192($t1)
sw $t0 192($sp)
lw $t0 196($t1)
sw $t0 196($sp)
lw $t0 200($t1)
sw $t0 200($sp)
lw $t0 204($t1)
sw $t0 204($sp)
lw $t0 208($t1)
sw $t0 208($sp)
lw $t0 212($t1)
sw $t0 212($sp)
lw $t0 216($t1)
sw $t0 216($sp)
lw $t0 220($t1)
sw $t0 220($sp)
lw $t0 224($t1)
sw $t0 224($sp)
lw $t0 228($t1)
sw $t0 228($sp)
lw $t0 232($t1)
sw $t0 232($sp)
lw $t0 236($t1)
sw $t0 236($sp)
lw $t0 240($t1)
sw $t0 240($sp)
lw $t0 244($t1)
sw $t0 244($sp)
lw $t0 248($t1)
sw $t0 248($sp)
lw $t0 252($t1)
sw $t0 252($sp)
lw $t0 256($t1)
sw $t0 256($sp)
lw $t0 260($t1)
sw $t0 260($sp)
lw $t0 264($t1)
sw $t0 264($sp)
lw $t0 268($t1)
sw $t0 268($sp)
lw $t0 272($t1)
sw $t0 272($sp)
lw $t0 276($t1)
sw $t0 276($sp)
lw $t0 280($t1)
sw $t0 280($sp)
lw $t0 284($t1)
sw $t0 284($sp)
lw $t0 288($t1)
sw $t0 288($sp)
lw $t0 292($t1)
sw $t0 292($sp)
lw $t0 296($t1)
sw $t0 296($sp)
lw $t0 300($t1)
sw $t0 300($sp)
lw $t0 304($t1)
sw $t0 304($sp)
lw $t0 308($t1)
sw $t0 308($sp)
lw $t0 312($t1)
sw $t0 312($sp)
lw $t0 316($t1)
sw $t0 316($sp)
lw $t0 320($t1)
sw $t0 320($sp)
lw $t0 324($t1)
sw $t0 324($sp)
lw $t0 328($t1)
sw $t0 328($sp)
lw $t0 332($t1)
sw $t0 332($sp)
lw $t0 336($t1)
sw $t0 336($sp)
lw $t0 340($t1)
sw $t0 340($sp)
lw $t0 344($t1)
sw $t0 344($sp)
lw $t0 348($t1)
sw $t0 348($sp)
lw $t0 352($t1)
sw $t0 352($sp)
lw $t0 356($t1)
sw $t0 356($sp)
lw $t0 360($t1)
sw $t0 360($sp)
lw $t0 364($t1)
sw $t0 364($sp)
lw $t0 368($t1)
sw $t0 368($sp)
lw $t0 372($t1)
sw $t0 372($sp)
lw $t0 376($t1)
sw $t0 376($sp)
lw $t0 380($t1)
sw $t0 380($sp)
lw $t0 384($t1)
sw $t0 384($sp)
lw $t0 388($t1)
sw $t0 388($sp)
lw $t0 392($t1)
sw $t0 392($sp)
lw $t0 396($t1)
sw $t0 396($sp)
lw $t0 400($t1)
sw $t0 400($sp)
jal print
lw $fp 504($sp)
la $t1 4($gp)
lw $t0 0($sp) 
sw $t0 0($t1) 
lw $t0 4($sp) 
sw $t0 4($t1) 
lw $t0 8($sp) 
sw $t0 8($t1) 
lw $t0 12($sp) 
sw $t0 12($t1) 
lw $t0 16($sp) 
sw $t0 16($t1) 
lw $t0 20($sp) 
sw $t0 20($t1) 
lw $t0 24($sp) 
sw $t0 24($t1) 
lw $t0 28($sp) 
sw $t0 28($t1) 
lw $t0 32($sp) 
sw $t0 32($t1) 
lw $t0 36($sp) 
sw $t0 36($t1) 
lw $t0 40($sp) 
sw $t0 40($t1) 
lw $t0 44($sp) 
sw $t0 44($t1) 
lw $t0 48($sp) 
sw $t0 48($t1) 
lw $t0 52($sp) 
sw $t0 52($t1) 
lw $t0 56($sp) 
sw $t0 56($t1) 
lw $t0 60($sp) 
sw $t0 60($t1) 
lw $t0 64($sp) 
sw $t0 64($t1) 
lw $t0 68($sp) 
sw $t0 68($t1) 
lw $t0 72($sp) 
sw $t0 72($t1) 
lw $t0 76($sp) 
sw $t0 76($t1) 
lw $t0 80($sp) 
sw $t0 80($t1) 
lw $t0 84($sp) 
sw $t0 84($t1) 
lw $t0 88($sp) 
sw $t0 88($t1) 
lw $t0 92($sp) 
sw $t0 92($t1) 
lw $t0 96($sp) 
sw $t0 96($t1) 
lw $t0 100($sp) 
sw $t0 100($t1) 
lw $t0 104($sp) 
sw $t0 104($t1) 
lw $t0 108($sp) 
sw $t0 108($t1) 
lw $t0 112($sp) 
sw $t0 112($t1) 
lw $t0 116($sp) 
sw $t0 116($t1) 
lw $t0 120($sp) 
sw $t0 120($t1) 
lw $t0 124($sp) 
sw $t0 124($t1) 
lw $t0 128($sp) 
sw $t0 128($t1) 
lw $t0 132($sp) 
sw $t0 132($t1) 
lw $t0 136($sp) 
sw $t0 136($t1) 
lw $t0 140($sp) 
sw $t0 140($t1) 
lw $t0 144($sp) 
sw $t0 144($t1) 
lw $t0 148($sp) 
sw $t0 148($t1) 
lw $t0 152($sp) 
sw $t0 152($t1) 
lw $t0 156($sp) 
sw $t0 156($t1) 
lw $t0 160($sp) 
sw $t0 160($t1) 
lw $t0 164($sp) 
sw $t0 164($t1) 
lw $t0 168($sp) 
sw $t0 168($t1) 
lw $t0 172($sp) 
sw $t0 172($t1) 
lw $t0 176($sp) 
sw $t0 176($t1) 
lw $t0 180($sp) 
sw $t0 180($t1) 
lw $t0 184($sp) 
sw $t0 184($t1) 
lw $t0 188($sp) 
sw $t0 188($t1) 
lw $t0 192($sp) 
sw $t0 192($t1) 
lw $t0 196($sp) 
sw $t0 196($t1) 
lw $t0 200($sp) 
sw $t0 200($t1) 
lw $t0 204($sp) 
sw $t0 204($t1) 
lw $t0 208($sp) 
sw $t0 208($t1) 
lw $t0 212($sp) 
sw $t0 212($t1) 
lw $t0 216($sp) 
sw $t0 216($t1) 
lw $t0 220($sp) 
sw $t0 220($t1) 
lw $t0 224($sp) 
sw $t0 224($t1) 
lw $t0 228($sp) 
sw $t0 228($t1) 
lw $t0 232($sp) 
sw $t0 232($t1) 
lw $t0 236($sp) 
sw $t0 236($t1) 
lw $t0 240($sp) 
sw $t0 240($t1) 
lw $t0 244($sp) 
sw $t0 244($t1) 
lw $t0 248($sp) 
sw $t0 248($t1) 
lw $t0 252($sp) 
sw $t0 252($t1) 
lw $t0 256($sp) 
sw $t0 256($t1) 
lw $t0 260($sp) 
sw $t0 260($t1) 
lw $t0 264($sp) 
sw $t0 264($t1) 
lw $t0 268($sp) 
sw $t0 268($t1) 
lw $t0 272($sp) 
sw $t0 272($t1) 
lw $t0 276($sp) 
sw $t0 276($t1) 
lw $t0 280($sp) 
sw $t0 280($t1) 
lw $t0 284($sp) 
sw $t0 284($t1) 
lw $t0 288($sp) 
sw $t0 288($t1) 
lw $t0 292($sp) 
sw $t0 292($t1) 
lw $t0 296($sp) 
sw $t0 296($t1) 
lw $t0 300($sp) 
sw $t0 300($t1) 
lw $t0 304($sp) 
sw $t0 304($t1) 
lw $t0 308($sp) 
sw $t0 308($t1) 
lw $t0 312($sp) 
sw $t0 312($t1) 
lw $t0 316($sp) 
sw $t0 316($t1) 
lw $t0 320($sp) 
sw $t0 320($t1) 
lw $t0 324($sp) 
sw $t0 324($t1) 
lw $t0 328($sp) 
sw $t0 328($t1) 
lw $t0 332($sp) 
sw $t0 332($t1) 
lw $t0 336($sp) 
sw $t0 336($t1) 
lw $t0 340($sp) 
sw $t0 340($t1) 
lw $t0 344($sp) 
sw $t0 344($t1) 
lw $t0 348($sp) 
sw $t0 348($t1) 
lw $t0 352($sp) 
sw $t0 352($t1) 
lw $t0 356($sp) 
sw $t0 356($t1) 
lw $t0 360($sp) 
sw $t0 360($t1) 
lw $t0 364($sp) 
sw $t0 364($t1) 
lw $t0 368($sp) 
sw $t0 368($t1) 
lw $t0 372($sp) 
sw $t0 372($t1) 
lw $t0 376($sp) 
sw $t0 376($t1) 
lw $t0 380($sp) 
sw $t0 380($t1) 
lw $t0 384($sp) 
sw $t0 384($t1) 
lw $t0 388($sp) 
sw $t0 388($t1) 
lw $t0 392($sp) 
sw $t0 392($t1) 
lw $t0 396($sp) 
sw $t0 396($t1) 
lw $t0 400($sp) 
sw $t0 400($t1) 
addi $sp $sp 404

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s7 40($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

#WRITE(_ASCIIVAL_=> 10)
li $t1 '\n'
li $v0 11
move $a0 $t1
syscall


# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -412
la $t1 4($gp)
lw $t0 0($t1)
sw $t0 0($sp)
lw $t0 4($t1)
sw $t0 4($sp)
lw $t0 8($t1)
sw $t0 8($sp)
lw $t0 12($t1)
sw $t0 12($sp)
lw $t0 16($t1)
sw $t0 16($sp)
lw $t0 20($t1)
sw $t0 20($sp)
lw $t0 24($t1)
sw $t0 24($sp)
lw $t0 28($t1)
sw $t0 28($sp)
lw $t0 32($t1)
sw $t0 32($sp)
lw $t0 36($t1)
sw $t0 36($sp)
lw $t0 40($t1)
sw $t0 40($sp)
lw $t0 44($t1)
sw $t0 44($sp)
lw $t0 48($t1)
sw $t0 48($sp)
lw $t0 52($t1)
sw $t0 52($sp)
lw $t0 56($t1)
sw $t0 56($sp)
lw $t0 60($t1)
sw $t0 60($sp)
lw $t0 64($t1)
sw $t0 64($sp)
lw $t0 68($t1)
sw $t0 68($sp)
lw $t0 72($t1)
sw $t0 72($sp)
lw $t0 76($t1)
sw $t0 76($sp)
lw $t0 80($t1)
sw $t0 80($sp)
lw $t0 84($t1)
sw $t0 84($sp)
lw $t0 88($t1)
sw $t0 88($sp)
lw $t0 92($t1)
sw $t0 92($sp)
lw $t0 96($t1)
sw $t0 96($sp)
lw $t0 100($t1)
sw $t0 100($sp)
lw $t0 104($t1)
sw $t0 104($sp)
lw $t0 108($t1)
sw $t0 108($sp)
lw $t0 112($t1)
sw $t0 112($sp)
lw $t0 116($t1)
sw $t0 116($sp)
lw $t0 120($t1)
sw $t0 120($sp)
lw $t0 124($t1)
sw $t0 124($sp)
lw $t0 128($t1)
sw $t0 128($sp)
lw $t0 132($t1)
sw $t0 132($sp)
lw $t0 136($t1)
sw $t0 136($sp)
lw $t0 140($t1)
sw $t0 140($sp)
lw $t0 144($t1)
sw $t0 144($sp)
lw $t0 148($t1)
sw $t0 148($sp)
lw $t0 152($t1)
sw $t0 152($sp)
lw $t0 156($t1)
sw $t0 156($sp)
lw $t0 160($t1)
sw $t0 160($sp)
lw $t0 164($t1)
sw $t0 164($sp)
lw $t0 168($t1)
sw $t0 168($sp)
lw $t0 172($t1)
sw $t0 172($sp)
lw $t0 176($t1)
sw $t0 176($sp)
lw $t0 180($t1)
sw $t0 180($sp)
lw $t0 184($t1)
sw $t0 184($sp)
lw $t0 188($t1)
sw $t0 188($sp)
lw $t0 192($t1)
sw $t0 192($sp)
lw $t0 196($t1)
sw $t0 196($sp)
lw $t0 200($t1)
sw $t0 200($sp)
lw $t0 204($t1)
sw $t0 204($sp)
lw $t0 208($t1)
sw $t0 208($sp)
lw $t0 212($t1)
sw $t0 212($sp)
lw $t0 216($t1)
sw $t0 216($sp)
lw $t0 220($t1)
sw $t0 220($sp)
lw $t0 224($t1)
sw $t0 224($sp)
lw $t0 228($t1)
sw $t0 228($sp)
lw $t0 232($t1)
sw $t0 232($sp)
lw $t0 236($t1)
sw $t0 236($sp)
lw $t0 240($t1)
sw $t0 240($sp)
lw $t0 244($t1)
sw $t0 244($sp)
lw $t0 248($t1)
sw $t0 248($sp)
lw $t0 252($t1)
sw $t0 252($sp)
lw $t0 256($t1)
sw $t0 256($sp)
lw $t0 260($t1)
sw $t0 260($sp)
lw $t0 264($t1)
sw $t0 264($sp)
lw $t0 268($t1)
sw $t0 268($sp)
lw $t0 272($t1)
sw $t0 272($sp)
lw $t0 276($t1)
sw $t0 276($sp)
lw $t0 280($t1)
sw $t0 280($sp)
lw $t0 284($t1)
sw $t0 284($sp)
lw $t0 288($t1)
sw $t0 288($sp)
lw $t0 292($t1)
sw $t0 292($sp)
lw $t0 296($t1)
sw $t0 296($sp)
lw $t0 300($t1)
sw $t0 300($sp)
lw $t0 304($t1)
sw $t0 304($sp)
lw $t0 308($t1)
sw $t0 308($sp)
lw $t0 312($t1)
sw $t0 312($sp)
lw $t0 316($t1)
sw $t0 316($sp)
lw $t0 320($t1)
sw $t0 320($sp)
lw $t0 324($t1)
sw $t0 324($sp)
lw $t0 328($t1)
sw $t0 328($sp)
lw $t0 332($t1)
sw $t0 332($sp)
lw $t0 336($t1)
sw $t0 336($sp)
lw $t0 340($t1)
sw $t0 340($sp)
lw $t0 344($t1)
sw $t0 344($sp)
lw $t0 348($t1)
sw $t0 348($sp)
lw $t0 352($t1)
sw $t0 352($sp)
lw $t0 356($t1)
sw $t0 356($sp)
lw $t0 360($t1)
sw $t0 360($sp)
lw $t0 364($t1)
sw $t0 364($sp)
lw $t0 368($t1)
sw $t0 368($sp)
lw $t0 372($t1)
sw $t0 372($sp)
lw $t0 376($t1)
sw $t0 376($sp)
lw $t0 380($t1)
sw $t0 380($sp)
lw $t0 384($t1)
sw $t0 384($sp)
lw $t0 388($t1)
sw $t0 388($sp)
lw $t0 392($t1)
sw $t0 392($sp)
lw $t0 396($t1)
sw $t0 396($sp)
lw $t0 400($t1)
sw $t0 400($sp)
li $t1 0
sw $t1 404($sp) 
li $t1 100
sw $t1 408($sp) 
jal sort
lw $fp 512($sp)
la $t1 4($gp)
lw $t0 0($sp) 
sw $t0 0($t1) 
lw $t0 4($sp) 
sw $t0 4($t1) 
lw $t0 8($sp) 
sw $t0 8($t1) 
lw $t0 12($sp) 
sw $t0 12($t1) 
lw $t0 16($sp) 
sw $t0 16($t1) 
lw $t0 20($sp) 
sw $t0 20($t1) 
lw $t0 24($sp) 
sw $t0 24($t1) 
lw $t0 28($sp) 
sw $t0 28($t1) 
lw $t0 32($sp) 
sw $t0 32($t1) 
lw $t0 36($sp) 
sw $t0 36($t1) 
lw $t0 40($sp) 
sw $t0 40($t1) 
lw $t0 44($sp) 
sw $t0 44($t1) 
lw $t0 48($sp) 
sw $t0 48($t1) 
lw $t0 52($sp) 
sw $t0 52($t1) 
lw $t0 56($sp) 
sw $t0 56($t1) 
lw $t0 60($sp) 
sw $t0 60($t1) 
lw $t0 64($sp) 
sw $t0 64($t1) 
lw $t0 68($sp) 
sw $t0 68($t1) 
lw $t0 72($sp) 
sw $t0 72($t1) 
lw $t0 76($sp) 
sw $t0 76($t1) 
lw $t0 80($sp) 
sw $t0 80($t1) 
lw $t0 84($sp) 
sw $t0 84($t1) 
lw $t0 88($sp) 
sw $t0 88($t1) 
lw $t0 92($sp) 
sw $t0 92($t1) 
lw $t0 96($sp) 
sw $t0 96($t1) 
lw $t0 100($sp) 
sw $t0 100($t1) 
lw $t0 104($sp) 
sw $t0 104($t1) 
lw $t0 108($sp) 
sw $t0 108($t1) 
lw $t0 112($sp) 
sw $t0 112($t1) 
lw $t0 116($sp) 
sw $t0 116($t1) 
lw $t0 120($sp) 
sw $t0 120($t1) 
lw $t0 124($sp) 
sw $t0 124($t1) 
lw $t0 128($sp) 
sw $t0 128($t1) 
lw $t0 132($sp) 
sw $t0 132($t1) 
lw $t0 136($sp) 
sw $t0 136($t1) 
lw $t0 140($sp) 
sw $t0 140($t1) 
lw $t0 144($sp) 
sw $t0 144($t1) 
lw $t0 148($sp) 
sw $t0 148($t1) 
lw $t0 152($sp) 
sw $t0 152($t1) 
lw $t0 156($sp) 
sw $t0 156($t1) 
lw $t0 160($sp) 
sw $t0 160($t1) 
lw $t0 164($sp) 
sw $t0 164($t1) 
lw $t0 168($sp) 
sw $t0 168($t1) 
lw $t0 172($sp) 
sw $t0 172($t1) 
lw $t0 176($sp) 
sw $t0 176($t1) 
lw $t0 180($sp) 
sw $t0 180($t1) 
lw $t0 184($sp) 
sw $t0 184($t1) 
lw $t0 188($sp) 
sw $t0 188($t1) 
lw $t0 192($sp) 
sw $t0 192($t1) 
lw $t0 196($sp) 
sw $t0 196($t1) 
lw $t0 200($sp) 
sw $t0 200($t1) 
lw $t0 204($sp) 
sw $t0 204($t1) 
lw $t0 208($sp) 
sw $t0 208($t1) 
lw $t0 212($sp) 
sw $t0 212($t1) 
lw $t0 216($sp) 
sw $t0 216($t1) 
lw $t0 220($sp) 
sw $t0 220($t1) 
lw $t0 224($sp) 
sw $t0 224($t1) 
lw $t0 228($sp) 
sw $t0 228($t1) 
lw $t0 232($sp) 
sw $t0 232($t1) 
lw $t0 236($sp) 
sw $t0 236($t1) 
lw $t0 240($sp) 
sw $t0 240($t1) 
lw $t0 244($sp) 
sw $t0 244($t1) 
lw $t0 248($sp) 
sw $t0 248($t1) 
lw $t0 252($sp) 
sw $t0 252($t1) 
lw $t0 256($sp) 
sw $t0 256($t1) 
lw $t0 260($sp) 
sw $t0 260($t1) 
lw $t0 264($sp) 
sw $t0 264($t1) 
lw $t0 268($sp) 
sw $t0 268($t1) 
lw $t0 272($sp) 
sw $t0 272($t1) 
lw $t0 276($sp) 
sw $t0 276($t1) 
lw $t0 280($sp) 
sw $t0 280($t1) 
lw $t0 284($sp) 
sw $t0 284($t1) 
lw $t0 288($sp) 
sw $t0 288($t1) 
lw $t0 292($sp) 
sw $t0 292($t1) 
lw $t0 296($sp) 
sw $t0 296($t1) 
lw $t0 300($sp) 
sw $t0 300($t1) 
lw $t0 304($sp) 
sw $t0 304($t1) 
lw $t0 308($sp) 
sw $t0 308($t1) 
lw $t0 312($sp) 
sw $t0 312($t1) 
lw $t0 316($sp) 
sw $t0 316($t1) 
lw $t0 320($sp) 
sw $t0 320($t1) 
lw $t0 324($sp) 
sw $t0 324($t1) 
lw $t0 328($sp) 
sw $t0 328($t1) 
lw $t0 332($sp) 
sw $t0 332($t1) 
lw $t0 336($sp) 
sw $t0 336($t1) 
lw $t0 340($sp) 
sw $t0 340($t1) 
lw $t0 344($sp) 
sw $t0 344($t1) 
lw $t0 348($sp) 
sw $t0 348($t1) 
lw $t0 352($sp) 
sw $t0 352($t1) 
lw $t0 356($sp) 
sw $t0 356($t1) 
lw $t0 360($sp) 
sw $t0 360($t1) 
lw $t0 364($sp) 
sw $t0 364($t1) 
lw $t0 368($sp) 
sw $t0 368($t1) 
lw $t0 372($sp) 
sw $t0 372($t1) 
lw $t0 376($sp) 
sw $t0 376($t1) 
lw $t0 380($sp) 
sw $t0 380($t1) 
lw $t0 384($sp) 
sw $t0 384($t1) 
lw $t0 388($sp) 
sw $t0 388($t1) 
lw $t0 392($sp) 
sw $t0 392($t1) 
lw $t0 396($sp) 
sw $t0 396($t1) 
lw $t0 400($sp) 
sw $t0 400($t1) 
addi $sp $sp 412

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s7 40($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

#WRITE("\nSorted: ")
la $t1 string1
li $v0 4
move $a0 $t1
syscall


# SPILLING REGISTERS 
addi $sp $sp -104
sw $fp 100($sp)
sw $ra 96($sp)
sw $v0 92($sp)
sw $v1 88($sp)
sw $a0 84($sp)
sw $a1 80($sp)
sw $a2 76($sp)
sw $a3 72($sp)
sw $s0 68($sp)
sw $s1 64($sp)
sw $s2 60($sp)
sw $s3 56($sp)
sw $s4 52($sp)
sw $s5 48($sp)
sw $s6 44($sp)
sw $s7 40($sp)
sw $t0 36($sp)
sw $t1 32($sp)
sw $t2 28($sp)
sw $t3 24($sp)
sw $t4 20($sp)
sw $t5 16($sp)
sw $t6 12($sp)
sw $t7 8($sp)
sw $t8 4($sp)
sw $t9 0($sp)

addi $sp $sp -404
la $t1 4($gp)
lw $t0 0($t1)
sw $t0 0($sp)
lw $t0 4($t1)
sw $t0 4($sp)
lw $t0 8($t1)
sw $t0 8($sp)
lw $t0 12($t1)
sw $t0 12($sp)
lw $t0 16($t1)
sw $t0 16($sp)
lw $t0 20($t1)
sw $t0 20($sp)
lw $t0 24($t1)
sw $t0 24($sp)
lw $t0 28($t1)
sw $t0 28($sp)
lw $t0 32($t1)
sw $t0 32($sp)
lw $t0 36($t1)
sw $t0 36($sp)
lw $t0 40($t1)
sw $t0 40($sp)
lw $t0 44($t1)
sw $t0 44($sp)
lw $t0 48($t1)
sw $t0 48($sp)
lw $t0 52($t1)
sw $t0 52($sp)
lw $t0 56($t1)
sw $t0 56($sp)
lw $t0 60($t1)
sw $t0 60($sp)
lw $t0 64($t1)
sw $t0 64($sp)
lw $t0 68($t1)
sw $t0 68($sp)
lw $t0 72($t1)
sw $t0 72($sp)
lw $t0 76($t1)
sw $t0 76($sp)
lw $t0 80($t1)
sw $t0 80($sp)
lw $t0 84($t1)
sw $t0 84($sp)
lw $t0 88($t1)
sw $t0 88($sp)
lw $t0 92($t1)
sw $t0 92($sp)
lw $t0 96($t1)
sw $t0 96($sp)
lw $t0 100($t1)
sw $t0 100($sp)
lw $t0 104($t1)
sw $t0 104($sp)
lw $t0 108($t1)
sw $t0 108($sp)
lw $t0 112($t1)
sw $t0 112($sp)
lw $t0 116($t1)
sw $t0 116($sp)
lw $t0 120($t1)
sw $t0 120($sp)
lw $t0 124($t1)
sw $t0 124($sp)
lw $t0 128($t1)
sw $t0 128($sp)
lw $t0 132($t1)
sw $t0 132($sp)
lw $t0 136($t1)
sw $t0 136($sp)
lw $t0 140($t1)
sw $t0 140($sp)
lw $t0 144($t1)
sw $t0 144($sp)
lw $t0 148($t1)
sw $t0 148($sp)
lw $t0 152($t1)
sw $t0 152($sp)
lw $t0 156($t1)
sw $t0 156($sp)
lw $t0 160($t1)
sw $t0 160($sp)
lw $t0 164($t1)
sw $t0 164($sp)
lw $t0 168($t1)
sw $t0 168($sp)
lw $t0 172($t1)
sw $t0 172($sp)
lw $t0 176($t1)
sw $t0 176($sp)
lw $t0 180($t1)
sw $t0 180($sp)
lw $t0 184($t1)
sw $t0 184($sp)
lw $t0 188($t1)
sw $t0 188($sp)
lw $t0 192($t1)
sw $t0 192($sp)
lw $t0 196($t1)
sw $t0 196($sp)
lw $t0 200($t1)
sw $t0 200($sp)
lw $t0 204($t1)
sw $t0 204($sp)
lw $t0 208($t1)
sw $t0 208($sp)
lw $t0 212($t1)
sw $t0 212($sp)
lw $t0 216($t1)
sw $t0 216($sp)
lw $t0 220($t1)
sw $t0 220($sp)
lw $t0 224($t1)
sw $t0 224($sp)
lw $t0 228($t1)
sw $t0 228($sp)
lw $t0 232($t1)
sw $t0 232($sp)
lw $t0 236($t1)
sw $t0 236($sp)
lw $t0 240($t1)
sw $t0 240($sp)
lw $t0 244($t1)
sw $t0 244($sp)
lw $t0 248($t1)
sw $t0 248($sp)
lw $t0 252($t1)
sw $t0 252($sp)
lw $t0 256($t1)
sw $t0 256($sp)
lw $t0 260($t1)
sw $t0 260($sp)
lw $t0 264($t1)
sw $t0 264($sp)
lw $t0 268($t1)
sw $t0 268($sp)
lw $t0 272($t1)
sw $t0 272($sp)
lw $t0 276($t1)
sw $t0 276($sp)
lw $t0 280($t1)
sw $t0 280($sp)
lw $t0 284($t1)
sw $t0 284($sp)
lw $t0 288($t1)
sw $t0 288($sp)
lw $t0 292($t1)
sw $t0 292($sp)
lw $t0 296($t1)
sw $t0 296($sp)
lw $t0 300($t1)
sw $t0 300($sp)
lw $t0 304($t1)
sw $t0 304($sp)
lw $t0 308($t1)
sw $t0 308($sp)
lw $t0 312($t1)
sw $t0 312($sp)
lw $t0 316($t1)
sw $t0 316($sp)
lw $t0 320($t1)
sw $t0 320($sp)
lw $t0 324($t1)
sw $t0 324($sp)
lw $t0 328($t1)
sw $t0 328($sp)
lw $t0 332($t1)
sw $t0 332($sp)
lw $t0 336($t1)
sw $t0 336($sp)
lw $t0 340($t1)
sw $t0 340($sp)
lw $t0 344($t1)
sw $t0 344($sp)
lw $t0 348($t1)
sw $t0 348($sp)
lw $t0 352($t1)
sw $t0 352($sp)
lw $t0 356($t1)
sw $t0 356($sp)
lw $t0 360($t1)
sw $t0 360($sp)
lw $t0 364($t1)
sw $t0 364($sp)
lw $t0 368($t1)
sw $t0 368($sp)
lw $t0 372($t1)
sw $t0 372($sp)
lw $t0 376($t1)
sw $t0 376($sp)
lw $t0 380($t1)
sw $t0 380($sp)
lw $t0 384($t1)
sw $t0 384($sp)
lw $t0 388($t1)
sw $t0 388($sp)
lw $t0 392($t1)
sw $t0 392($sp)
lw $t0 396($t1)
sw $t0 396($sp)
lw $t0 400($t1)
sw $t0 400($sp)
jal print
lw $fp 504($sp)
la $t1 4($gp)
lw $t0 0($sp) 
sw $t0 0($t1) 
lw $t0 4($sp) 
sw $t0 4($t1) 
lw $t0 8($sp) 
sw $t0 8($t1) 
lw $t0 12($sp) 
sw $t0 12($t1) 
lw $t0 16($sp) 
sw $t0 16($t1) 
lw $t0 20($sp) 
sw $t0 20($t1) 
lw $t0 24($sp) 
sw $t0 24($t1) 
lw $t0 28($sp) 
sw $t0 28($t1) 
lw $t0 32($sp) 
sw $t0 32($t1) 
lw $t0 36($sp) 
sw $t0 36($t1) 
lw $t0 40($sp) 
sw $t0 40($t1) 
lw $t0 44($sp) 
sw $t0 44($t1) 
lw $t0 48($sp) 
sw $t0 48($t1) 
lw $t0 52($sp) 
sw $t0 52($t1) 
lw $t0 56($sp) 
sw $t0 56($t1) 
lw $t0 60($sp) 
sw $t0 60($t1) 
lw $t0 64($sp) 
sw $t0 64($t1) 
lw $t0 68($sp) 
sw $t0 68($t1) 
lw $t0 72($sp) 
sw $t0 72($t1) 
lw $t0 76($sp) 
sw $t0 76($t1) 
lw $t0 80($sp) 
sw $t0 80($t1) 
lw $t0 84($sp) 
sw $t0 84($t1) 
lw $t0 88($sp) 
sw $t0 88($t1) 
lw $t0 92($sp) 
sw $t0 92($t1) 
lw $t0 96($sp) 
sw $t0 96($t1) 
lw $t0 100($sp) 
sw $t0 100($t1) 
lw $t0 104($sp) 
sw $t0 104($t1) 
lw $t0 108($sp) 
sw $t0 108($t1) 
lw $t0 112($sp) 
sw $t0 112($t1) 
lw $t0 116($sp) 
sw $t0 116($t1) 
lw $t0 120($sp) 
sw $t0 120($t1) 
lw $t0 124($sp) 
sw $t0 124($t1) 
lw $t0 128($sp) 
sw $t0 128($t1) 
lw $t0 132($sp) 
sw $t0 132($t1) 
lw $t0 136($sp) 
sw $t0 136($t1) 
lw $t0 140($sp) 
sw $t0 140($t1) 
lw $t0 144($sp) 
sw $t0 144($t1) 
lw $t0 148($sp) 
sw $t0 148($t1) 
lw $t0 152($sp) 
sw $t0 152($t1) 
lw $t0 156($sp) 
sw $t0 156($t1) 
lw $t0 160($sp) 
sw $t0 160($t1) 
lw $t0 164($sp) 
sw $t0 164($t1) 
lw $t0 168($sp) 
sw $t0 168($t1) 
lw $t0 172($sp) 
sw $t0 172($t1) 
lw $t0 176($sp) 
sw $t0 176($t1) 
lw $t0 180($sp) 
sw $t0 180($t1) 
lw $t0 184($sp) 
sw $t0 184($t1) 
lw $t0 188($sp) 
sw $t0 188($t1) 
lw $t0 192($sp) 
sw $t0 192($t1) 
lw $t0 196($sp) 
sw $t0 196($t1) 
lw $t0 200($sp) 
sw $t0 200($t1) 
lw $t0 204($sp) 
sw $t0 204($t1) 
lw $t0 208($sp) 
sw $t0 208($t1) 
lw $t0 212($sp) 
sw $t0 212($t1) 
lw $t0 216($sp) 
sw $t0 216($t1) 
lw $t0 220($sp) 
sw $t0 220($t1) 
lw $t0 224($sp) 
sw $t0 224($t1) 
lw $t0 228($sp) 
sw $t0 228($t1) 
lw $t0 232($sp) 
sw $t0 232($t1) 
lw $t0 236($sp) 
sw $t0 236($t1) 
lw $t0 240($sp) 
sw $t0 240($t1) 
lw $t0 244($sp) 
sw $t0 244($t1) 
lw $t0 248($sp) 
sw $t0 248($t1) 
lw $t0 252($sp) 
sw $t0 252($t1) 
lw $t0 256($sp) 
sw $t0 256($t1) 
lw $t0 260($sp) 
sw $t0 260($t1) 
lw $t0 264($sp) 
sw $t0 264($t1) 
lw $t0 268($sp) 
sw $t0 268($t1) 
lw $t0 272($sp) 
sw $t0 272($t1) 
lw $t0 276($sp) 
sw $t0 276($t1) 
lw $t0 280($sp) 
sw $t0 280($t1) 
lw $t0 284($sp) 
sw $t0 284($t1) 
lw $t0 288($sp) 
sw $t0 288($t1) 
lw $t0 292($sp) 
sw $t0 292($t1) 
lw $t0 296($sp) 
sw $t0 296($t1) 
lw $t0 300($sp) 
sw $t0 300($t1) 
lw $t0 304($sp) 
sw $t0 304($t1) 
lw $t0 308($sp) 
sw $t0 308($t1) 
lw $t0 312($sp) 
sw $t0 312($t1) 
lw $t0 316($sp) 
sw $t0 316($t1) 
lw $t0 320($sp) 
sw $t0 320($t1) 
lw $t0 324($sp) 
sw $t0 324($t1) 
lw $t0 328($sp) 
sw $t0 328($t1) 
lw $t0 332($sp) 
sw $t0 332($t1) 
lw $t0 336($sp) 
sw $t0 336($t1) 
lw $t0 340($sp) 
sw $t0 340($t1) 
lw $t0 344($sp) 
sw $t0 344($t1) 
lw $t0 348($sp) 
sw $t0 348($t1) 
lw $t0 352($sp) 
sw $t0 352($t1) 
lw $t0 356($sp) 
sw $t0 356($t1) 
lw $t0 360($sp) 
sw $t0 360($t1) 
lw $t0 364($sp) 
sw $t0 364($t1) 
lw $t0 368($sp) 
sw $t0 368($t1) 
lw $t0 372($sp) 
sw $t0 372($t1) 
lw $t0 376($sp) 
sw $t0 376($t1) 
lw $t0 380($sp) 
sw $t0 380($t1) 
lw $t0 384($sp) 
sw $t0 384($t1) 
lw $t0 388($sp) 
sw $t0 388($t1) 
lw $t0 392($sp) 
sw $t0 392($t1) 
lw $t0 396($sp) 
sw $t0 396($t1) 
lw $t0 400($sp) 
sw $t0 400($t1) 
addi $sp $sp 404

# UNSPILLING REGISTERS 
lw $t9 0($sp)
lw $t8 4($sp)
lw $t7 8($sp)
lw $t6 12($sp)
lw $t5 16($sp)
lw $t4 20($sp)
lw $t3 24($sp)
lw $t2 28($sp)
lw $t1 32($sp)
lw $t0 36($sp)
lw $s7 40($sp)
lw $s6 44($sp)
lw $s5 48($sp)
lw $s4 52($sp)
lw $s3 56($sp)
lw $s2 60($sp)
lw $s1 64($sp)
lw $s0 68($sp)
lw $a3 72($sp)
lw $a2 76($sp)
lw $a1 80($sp)
lw $a0 84($sp)
lw $v1 88($sp)
lw $v0 92($sp)
lw $ra 96($sp)
lw $fp 100($sp)
addi $sp $sp 104

#WRITE(_ASCIIVAL_=> 10)
li $t1 '\n'
li $v0 11
move $a0 $t1
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
string0:    .asciiz    "Random: "
string1:    .asciiz    "\nSorted: "


.align 2

    Global_Area:

