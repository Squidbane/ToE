.globl main
.text
Hanoi:
	addi	$sp, $sp, -16
	sw	$a1, -12($sp)
	sw	$a2, -8($sp)
	sw	$a3, -4($sp)
	sw	$ra, 0($sp)

	addi	$t0, $zero, 1
	beq	$t0, $a1, skip1
	addi	$a1, $a1, -1
	#mov	$a2, $a2
	addi	$t1, $zero, 6
	add	$t0, $a2, $a3
	sub	$t0, $t1, $t0
	jal 	Hanoi
skip1:

	addi	$v0, $zero, 4
	la	$a0, one
	syscall				# cout << "move "

	addi	$v0, $zero, 1
	addi	$a0, $a2, 0
	syscall				# cout << origin

	addi	$v0, $zero, 4
	la	$a0, two
	syscall				# cout << " to "

	addi	$v0, $zero, 1
	addi	$a0, $a3, 0
	syscall				# cout << dest

	addi	$v0, $zero, 4
	la	$a0, three
	syscall				# cout << "\n"


	lw	$ra, 0($sp)
	lw	$a3, -4($sp)
	lw	$a2, -8($sp)
	lw	$a1, -12($sp)
	addi	$sp, $sp, 16		# This may be premature

	addi	$t0, $zero, 1
	beq	$t0, $a1, skip2
	jal	Hanoi

skip2:
	addi $sp, sp, -16		# undoing premature stack shrinkage
	jr	$ra

main:
	addi	$v0, $zero, 4
	la	$a0, please
	syscall			
	# cout << "One pos int please"
	
	addi	$v0, $zero, 5
	syscall				# cin >> n;

	addi	$a1, $v0, 0
	addi	$a2, $zero, 1
	addi	$a3, $zero, 2
	jal Hanoi			# hanoi(n,0,1);

.data
please:	.asciiz "One positive integer please: \n"
one:	.asciiz "move "
two:	.asciiz " to "
three:	.asciiz "\n"
.end