# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, main1   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }

main1:
    li $t0, 1           # i = 1
    li $t1, 0           # swapped = 0

loop1:
    bge $t0, 10, end0   # while(i < 10)
    
    mul $t3, $t0, 4     #calculate $numbers[i]
    la $t2, numbers     #
    add $t4, $t3, $t2   #
    lw  $t4, ($t4)

    mul $t3, $t0, 4     #calculate $numbers[i-1]
    la $t2, numbers     #
    add $t5, $t3, $t2   #
    sub $t5, $t5, 4
    lw $t5, ($t5)

    blt $t4, $t5, if_end#if(x < y)

    add $t0, $t0, 1     # i++;
    j loop1
end0:
    la $a0, ($t1)         # printf("%d", swapped)
    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31
if_end:
    li  $t1, 1          # swapped = 1
    j   end0
.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

