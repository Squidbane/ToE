.globl main
.text

sysOutText:				# Excessively procedural
	addi 	$v0, $zero, 4
	syscall
	jr	$ra

sysOutInt:				# Macros would probably be better
	addi 	$v0, $zero, 1
	syscall
	jr	$ra

sysInInt:				# Okay this is just ridiculous
	addi	$v0, $zero, 5
	syscall
	jr	$ra

sysoutint:				# Just for fun and 'cus I'm prone to typos
sysoutInt:
sysOutint:
	j	sysOutInt
sysinint:				
sysinInt:
sysInint:
	j	sysInInt
sysouttext:				
sysoutText:
sysOuttext:
	j	sysOutText

main:
	move	$s7, $ra
	addi	$s6, $zero, 42
loop:
	la 	$a0, please
	jal 	sysOutText
	jal 	sysInInt
	move	$s0, $v0

	la 	$a0, please2
	jal 	sysOutText
	jal 	sysInInt
	move	$s1, $v0

	add	$s2, $s1, $s0		# Blink and you'll miss it.

	move	$a0, $s0
	jal	sysOutInt
	la 	$a0, zero
	jal 	sysOutText

	move	$a0, $s1
	jal	sysOutInt
	la 	$a0, one
	jal 	sysOutText

	move	$a0, $s2
	jal	sysoutInt
	la 	$a0, two
	jal 	sysOutText
	
	bne	$s6, $s2, loop
	la 	$a0, free
	jal 	sysOutText
	jr	$s7
.data

please:	 .asciiz "Please enter an integer\n"
please2: .asciiz "Please enter another integer.\n"
zero:	 .asciiz " + "
one:	 .asciiz " = "
two:	 .asciiz "\n"
free:	 .asciiz "Congratulations! You found the secret code!\nNow you're free!"

.end