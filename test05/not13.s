main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    li $t3, 0           # int i = x + 1
    add $t3, $t0, 1     #
while:
    bge $t3, $t1 end    # while(i >= y) jump to end
    bne $t3, 13 if      # if(i != 13)
    add $t3, $t3, 1     # i++
    j while   

if:
    move $a0, $t3       #   printf("%d", i);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t3, $t3, 1     # i++
    j while             
end:

    li $v0, 0           # return 0
    jr $31
