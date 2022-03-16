#  read numbers until a non-negative number entered
# x in $t0
main:
    la $a0, str0         # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5            # scanf("%d", &x);
    syscall              #
    move $t0, $v0

    bgez $t0    end

    la $a0, str2         
    li $v0, 4
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    j main
end:
    la $a0, str1         # printf("You entered: ");
    li $v0, 4
    syscall
    move $a0, $t0        # printf("%d", x);
    li $v0, 1
    syscall
    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall
    li $v0, 0            # return 0
    jr $31

.data
str0:
    .asciiz "Enter a number: "
str1:
    .asciiz "You entered: "
str2:
    .asciiz "Enter a positive number"