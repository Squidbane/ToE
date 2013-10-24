.globl main
                                    # I''m using the end of "The Stack" as a stack of 'max' values
maxpush:                            # Just like C, these functions don't run until&unless they're called
    addi    $sp, $sp, -4            # Extend the stack
    sw      $a0, 0($sp)             # Save $a0 onto the stack
    jr      $ra                     # To 'call' this function, main or some other function will execute
                                    # a "jal" instruction. Jumping to the label, and storing the
                                    # 'return address' in $ra. Now we just jump back.
maxpop:
    addi    $sp, $sp, 4             # Shrink the stack (we don't care about that old data)
    jr      $ra                     # Function complete. Let's go home.

maxread:
    lw      $v0, 0($sp)             # Read the top* value of the stack (*in MIPS-land, top is down)
    jr      $ra                     # Is that it? Did we really need a function for this? (Not really)

hanoi:                              # I'll be allocating space on the stack for an array to store moves.
                                    # min and max will designate the section of the array the program
                                    # is working with. The program will move through the array like a BST,
                                    # saving values as it traverses the nodes. ... It's hard to explain :(

    move    $s6, $ra                # save the $ra
    addi    $s0, $zero, 0           # s0 = min
                                    # a1 = number of disks (n)
    mul     $t0, $a0, $a0           # t0 = n^2
    addi    $s2, $t0, -1            # s2 = n^2 - 1 (moves)


    #sub    $sp, $sp, $s2           # I could do it this way to use only 32 bits per move,
                                    # but that would be slightly more work! Nuts to that!
                                    # There're only 6 possible moves so even a halfbyte each (4 bits)
                                    # would be more than sufficient as a unique identifier.
    addi    $t0, $zero, 8
    mul     $t0, $s2, $t0           # Instead I'm using 32 bits times 2 = 8 bytes
    sub     $sp, $sp, $t0           # Allocating space for the array on the stack ( 8 * moves )

    addi    $a0, $zero, -1          # Setting up argument to be saved by maxPush()
    jal     maxpush                 # Calling function maxpush.

    addi    $a0, $s2, 0             # When the top value of the stack is -1, my program will interpret
    jal     maxpush                 # that as an empty stack. The first true value is $s2 (ie. moves)
loop:
    jal     maxread
    bltz    $v0, finished
    move    $a0, $s2
    li      $v0, 1
    syscall
    jal     maxpop
    j       loop

finished:
    jr      $s6                     # Returning to main

main:
    move    $s7, $ra                # save the $ra

    addi    $v0, $zero, 4           # syscall interprets a 4 in $v0 as 'Read off some text'
    la      $a0, ask                # Loading up $a0 with the address of ask
    syscall                         # The system reads text from the address that $a0 points to

    addi    $v0, $zero, 5           # syscall reads a 5 in $v0 as 'Save a user input integer'
    syscall                         # The system replaces $v0 with a new user inputed integer

    move    $a0, $v0                # save the integer and setup argument for call
    jal     hanoi                   # call hanoi function

    addi    $v0, $zero, 4           # syscall interprets a 4 in $v0 as 'Read off some text'
    la      $a0, done                # Loading up $a0 with the address of done
    syscall                         # The system reads text from the address that $a0 points to

    jr      $s7                     # return from main
.data
ask:    .asciiz "How many disks should the tower of Hanoi have? "
done:   .asciiz "\nProgram finished."
.end
