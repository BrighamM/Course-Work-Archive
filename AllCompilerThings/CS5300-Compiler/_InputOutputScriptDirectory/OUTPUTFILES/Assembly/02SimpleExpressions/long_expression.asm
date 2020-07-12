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

#a := 3
li $t0 3
la $t1 0($gp)
sw $t0 ($t1) 

#b := 2
li $t0 2
la $t1 4($gp)
sw $t0 ($t1) 

#c := 1
li $t0 1
la $t1 8($gp)
sw $t0 ($t1) 

#d := 4
li $t0 4
la $t1 12($gp)
sw $t0 ($t1) 

#e := 5
li $t0 5
la $t1 16($gp)
sw $t0 ($t1) 

#f := 6
li $t0 6
la $t1 20($gp)
sw $t0 ($t1) 

#g := 7
li $t0 7
la $t1 24($gp)
sw $t0 ($t1) 

#h := 8
li $t0 8
la $t1 28($gp)
sw $t0 ($t1) 

#i := 9
li $t0 9
la $t1 32($gp)
sw $t0 ($t1) 

#j := 10
li $t0 10
la $t1 36($gp)
sw $t0 ($t1) 

#k := 11
li $t0 11
la $t1 40($gp)
sw $t0 ($t1) 

#l := 12
li $t0 12
la $t1 44($gp)
sw $t0 ($t1) 

#m := 13
li $t0 13
la $t1 48($gp)
sw $t0 ($t1) 

#n := 14
li $t0 14
la $t1 52($gp)
sw $t0 ($t1) 

#o := 15
li $t0 15
la $t1 56($gp)
sw $t0 ($t1) 

#p := 16
li $t0 16
la $t1 60($gp)
sw $t0 ($t1) 

#x := (((a+b)*(c+d))-((e+f)*(g+h)))/(((i+j)*(k+l))-((m+n)*(o+p)))
lw $t0 0($gp)
lw $t1 4($gp)
add $t0 $t0 $t1
lw $t1 8($gp)
lw $t2 12($gp)
add $t1 $t1 $t2
mult  $t0 $t1
mflo $t0
lw $t1 16($gp)
lw $t2 20($gp)
add $t1 $t1 $t2
lw $t2 24($gp)
lw $t3 28($gp)
add $t2 $t2 $t3
mult  $t1 $t2
mflo $t1
sub $t0 $t0 $t1
lw $t1 32($gp)
lw $t2 36($gp)
add $t1 $t1 $t2
lw $t2 40($gp)
lw $t3 44($gp)
add $t2 $t2 $t3
mult  $t1 $t2
mflo $t1
lw $t2 48($gp)
lw $t3 52($gp)
add $t2 $t2 $t3
lw $t3 56($gp)
lw $t4 60($gp)
add $t3 $t3 $t4
mult  $t2 $t3
mflo $t2
sub $t1 $t1 $t2
div  $t0 $t1
mflo $t0
la $t1 64($gp)
sw $t0 ($t1) 

#y := (a+(b+(c+(d+(e+(f+(g+(h+(i+(j+(k+(l+(m+(n+(o+(p))))))))))))))))
lw $t0 0($gp)
lw $t1 4($gp)
lw $t2 8($gp)
lw $t3 12($gp)
lw $t4 16($gp)
lw $t5 20($gp)
lw $t6 24($gp)
lw $t7 28($gp)
lw $t8 32($gp)
lw $t9 36($gp)
lw $s0 40($gp)
lw $s1 44($gp)
lw $s2 48($gp)
lw $s3 52($gp)
lw $s4 56($gp)
lw $s5 60($gp)
add $s4 $s4 $s5
add $s3 $s3 $s4
add $s2 $s2 $s3
add $s1 $s1 $s2
add $s0 $s0 $s1
add $t9 $t9 $s0
add $t8 $t8 $t9
add $t7 $t7 $t8
add $t6 $t6 $t7
add $t5 $t5 $t6
add $t4 $t4 $t5
add $t3 $t3 $t4
add $t2 $t2 $t3
add $t1 $t1 $t2
add $t0 $t0 $t1
la $t1 68($gp)
sw $t0 ($t1) 

#z := (a)/(b)+(a*a)/(b*b)+(a*a*a)/(b*b*b)+(a*a*a*a)/(b*b*b*b)+(a*a*a*a*a)/(b*b*b*b*b)+(a*a*a*a*a*a)/(b*b*b*b*b*b)+(a*a*a*a*a*a*a)/(b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b*b*b*b*b*b)+(a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a*a)/(b*b*b*b*b*b*b*b*b*b*b*b*b*b*b*b*b)
lw $t0 0($gp)
lw $t1 4($gp)
div  $t0 $t1
mflo $t0
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
lw $t1 0($gp)
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 0($gp)
mult  $t1 $t2
mflo $t1
lw $t2 4($gp)
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
lw $t3 4($gp)
mult  $t2 $t3
mflo $t2
div  $t1 $t2
mflo $t1
add $t0 $t0 $t1
la $t1 72($gp)
sw $t0 ($t1) 

#WRITE("x = ", x, "    should be 0", _ASCIIVAL_=> 10)
la $t0 string0
li $v0 4
move $a0 $t0
syscall
lw $t0 64($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string1
li $v0 4
move $a0 $t0
syscall
li $t0 '\n'
li $v0 11
move $a0 $t0
syscall

#WRITE("y = ", y, "  should be 136\n")
la $t0 string2
li $v0 4
move $a0 $t0
syscall
lw $t0 68($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string3
li $v0 4
move $a0 $t0
syscall

#WRITE("z = ", z, " should be 2944\n")
la $t0 string4
li $v0 4
move $a0 $t0
syscall
lw $t0 72($gp)
li $v0 1
or $a0 $t0 $zero
syscall
la $t0 string5
li $v0 4
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
string0:    .asciiz    "x = "
string1:    .asciiz    "    should be 0"
string2:    .asciiz    "y = "
string3:    .asciiz    "  should be 136\n"
string4:    .asciiz    "z = "
string5:    .asciiz    " should be 2944\n"


.align 2

    Global_Area:

