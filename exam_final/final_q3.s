# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise

main:
    li   $v0, 5
    syscall

    # PUT YOUR CODE HERE
    move $t0, $v0       # move original to t0
    sll  $t1, $t0, 24   # lowest 2 bytes
    srl  $t1, $t1, 24
    sll  $t2, $t0, 16   # lowest four bytes
    srl  $t2, $t2, 24   # move lowest four bytes
    bne  $t2, $t1, print_0

print_1:
    li   $a0, 1
    li   $v0, 1
    syscall

    li   $a0, '\n'
    li   $v0, 11
    syscall

    li   $v0, 0
    jr   $ra

print_0:
    li   $a0, 0
    li   $v0, 1
    syscall

    li   $a0, '\n'
    li   $v0, 11
    syscall

    li   $v0, 0
    jr   $ra
