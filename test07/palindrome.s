# read a line and print whether it is a palindrom

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    li  $t0, 0          #i = 0
while0:
    la  $t1, line
    add $t1, $t1, $t0
    lb  $t2, ($t1)
    beqz $t2, end_while0

    addi $t0, $t0, 1

    j  while0
end_while0:
    li $t3, 0       # j = 0
    move $t4, $t0   #k = i
    sub  $t4, $t4, 2  # k = i - 2

while1:
    bge $t3, $t4, true

    la  $t5, line   
    la $t6, line
    add $t5, $t5, $t3
    add $t6, $t6, $t4

    lb $t5, ($t5)
    lb $t6, ($t6)
    bne $t6, $t5, false

    addi $t3, $t3, 1
    sub  $t4, $t4, 1
    j while1
false:
    la   $a0, not_palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31
true:
    la   $a0, palindrome
    li   $v0, 4
    syscall

    li   $v0, 0          # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256

