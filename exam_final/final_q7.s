# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

main:
    li   $t0, 0        # i = $t0 = 0
    li   $t1, 0        # sum = $t1 = 0
    li   $t4, 42       # $t4 = 42
while1:
    bge  $t1, $t4, while2  
    mul  $t3, $t0, 4   # offset

    li   $v0, 5        # scanf("%d", &x);
    syscall            #

    move $t6, $v0

    la   $t5, array
    add  $t5, $t5, $t3 
    sw   $t6, ($t5)

    addi $t0, $t0, 1
    add  $t1, $t1, $t6

    j   while1 
while2:
    ble  $t0, $0, end_while2
    sub  $t0, $t0, 1
    
    mul  $t3, $t0, 4   # offset
    la   $t5, array
    add  $t5, $t5, $t3 
    lw   $t6, ($t5)

    move $a0, $t6      #   printf("%d", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    j while2
end_while2:
    li   $v0, 0        # return 0
    jr   $ra

    .data
array:  
    .space 4000