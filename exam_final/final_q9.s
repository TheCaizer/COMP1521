# this code reads a line of input and prints 42
# change it to evaluate the arithmetic expression

main:
    la   $a0, line
    la   $a1, 10000
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

    move $t7, $v0       #s = line let s = $t7
    jal  expression     # call expression
    move $t6, $v0       #what is returned put in $t6

    move $a0, $t6         # printf("%d", 42);
    li   $v0, 1
    syscall

    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $31
expression:
    jal term
    move $t0, $v0       #left = term()
    li $t1, 43
    beq $t7, 43 end_expression
    jr  $t0
end_expression:
    addi $t7, $t7, 1    #s++
    jal expression 
    move $t3, $v0
    add  $t3, $t3, $t0  
    jr   $t3
term:
    jal number          #call number assuming $t7 is s
    move $t0, $v0       #$v0 is what jal returned store n in left
    li  $t1, 42         # 42 is '*' in ascii
if_term:
    beq $t7, $t1 end_ifterm
    jr  $t0     #return left
end_ifterm:
    addi $t7, $t7, 1  #s++
    jal term            #call term
    move $t2, $v0       #get twhat is returned to t2 as right
    mul $t2, $t2, $t0   #left * right
    jr  $t2

number:
    li  $t0, 0          #n = 0
while_number:
    li  $t1, 48 #ascii for 0
    li  $t2, 57 #ascii for 9
    ble $t7, $t1 end_whilenumber # *s >= '0' assuming a0 is *s
    bge $t7, $t2 end_whilenumber # *s <= '9'

    mul $t0, $t0, 10    # n = 10 * n
    sub $t4, $t7, $t1   # t4 = *s - '0'
    add $t0, $t0, $t4   # n = 10 * n + *s - '0'

    addi $t7, $t7, 1 

    j while_number
end_whilenumber:
    jr  $t0             #return n

.data
line:
    .space 10000

