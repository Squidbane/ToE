.globl main
.text
 
Hanoi:
        addi    $t0, $zero, 1
        beq     $t0, $a1, skip1
 
        addi    $sp, $sp, -16
        sw      $a3, 12($sp)
        sw      $a2, 8($sp)
        sw      $a1, 4($sp)
        sw      $ra, 0($sp)
 
        addi    $a1, $a1, -1            # $a1 = $a1 - 1
                                        # mov   $a2, $a2
        addi    $t1, $zero, 6
        add     $t0, $a2, $a3
        sub     $a3, $t1, $t0           # $a3 = 6 - ($a2 + $a3)
 
        jal     Hanoi
 
        lw      $a3, 12($sp)
        lw      $a2, 8($sp)
        lw      $a1, 4($sp)
        lw      $ra, 0($sp)
        addi    $sp, $sp, 16
skip1:
        addi    $v0, $zero, 4
        la      $a0, one
        syscall                         # cout << "move "
 
        addi    $v0, $zero, 1
        addi    $a0, $a2, 0
        syscall                         # cout << origin
 
        addi    $v0, $zero, 4
        la      $a0, two
        syscall                         # cout << " to "
 
        addi    $v0, $zero, 1
        addi    $a0, $a3, 0
        syscall                         # cout << dest
 
        addi    $v0, $zero, 4
        la      $a0, three
        syscall                         # cout << "\n"
 
 
        addi    $t0, $zero, 1
        beq     $t0, $a1, skip2
 
        addi    $sp, $sp, -16
        sw      $a3, 12($sp)
        sw      $a2, 8($sp)
        sw      $a1, 4($sp)
        sw      $ra, 0($sp)
 
        addi    $a1, $a1, -1            # $a1 = $a1 - 1
                                        # mov   $a3, $a3
        addi    $t1, $zero, 6
        add     $t0, $a2, $a3
        sub     $a2, $t1, $t0           # $a2 = 6 - ($a2 + $a3)
        jal     Hanoi
 
        lw      $a3, 12($sp)
        lw      $a2, 8($sp)
        lw      $a1, 4($sp)
        lw      $ra, 0($sp)
        addi    $sp, $sp, 16
 
skip2:
        jr      $ra
 
main:
        move    $s7, $ra
        addi    $v0, $zero, 4
        la      $a0, please
        syscall                         # cout << "One pos int please"
       
        addi    $v0, $zero, 5
        syscall                         # cin >> n;
 
        addi    $a1, $v0, 0
        addi    $a2, $zero, 1
 
        addi    $a3, $zero, 2
        jal Hanoi                       # hanoi(n,1,2);
        jr      $s7
 
.data
please: .asciiz "One positive integer please: \n"
one:    .asciiz "move "
two:    .asciiz " to "
three:  .asciiz "\n"
.end