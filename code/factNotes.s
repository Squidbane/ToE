.text
.globl main
fact:   addi $v0, $zero, 120
                add $s1, $a0, $zero
                jr $ra
main:
                addi $sp, $sp, -4   # save the $ra
                sw   $ra, 0($sp)
                addi $a0, $zero, 5  # set parameter
                jal fact                        # call fact funtion
                add $s0, $v0, $zero # save result
                lw   $ra, 0($sp)        # restore $ra
                addi $sp, $sp, 4
                addi $v0, $zero, 4  # print Hello
                add $a0, $zero, hello
                jr $ra
                # addi $v0, $zero, 10 # make exit system call
                # syscall
.data
hello: .asciiz "Hello program"
.end