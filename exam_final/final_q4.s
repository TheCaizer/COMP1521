# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum

main:
    li   $t2, 42
    bge  $t0, $t2, end

    li   $v0, 5        #   scanf("%d", &x);
    syscall            #

    move $t1, $v0

    add $t0, $t0, $t1

    j    main
end:
    move $a0, $t0       # prints the number
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        # return 0
    jr   $ra
