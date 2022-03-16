# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
main:
    li  $t0, 0  # int i = 0
while0:
    bge $t0, 1000 end_while0    # while I< 1000
    la  $t1, prime      # la of prime
    li  $t2, 4          # size of byte
    mul $t2, $t2, $t0   # i times the size of byte
    add $t1, $t1, $t2   # add to address
    li  $t3, 1
    sw  $t3, ($t1)      # prime[i] = 1


    addi $t0, $t0, 1    #i++
    j   while0
end_while0:
    li $t0, 2           # i = 2
while1:
    bge $t0, 1000 return0   # while i < 1000
    la  $t1, prime          # find adress
    li  $t2, 4
    mul $t2, $t2, $t0
    add $t1, $t1, $t2 
    lw  $t3, ($t1)
    bnez $t3 if0            # if(prime[i])
end_while1:
    addi $t0, $t0, 1        # i++
    j   while1
if0:
    move$a0, $t0            # printf(i)
    li  $v0, 1 
    syscall
    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall
    li  $t4, 2              # j = 2
    mul $t4, $t4, $t0       # j = j * i
while2:
    bge $t4, 1000 end_while1
    la $t1, prime
    li $t6, 4
    mul $t6, $t6 $t4
    add $t1, $t1, $t6
    li $t7, 0
    sw $t7, ($t1)
    add $t4, $t4, $t0       # j = j + i

    j while2
return0:
    li $v0, 0           # return 0
    jr $31

.data
prime:
    .space 1000