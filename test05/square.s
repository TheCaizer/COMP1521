main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0           # i = 0

while1:
    bge $t1, $t0 end    #while(i >= x) jump end

    li $t2, 0           # j = 0
while2:
    bge $t2, $t0 end0   # while(j >= x) jump to end0

    la $a0, aphos          #   printf("%d\n", 42);
    li $v0, 4
    syscall
    add $t2, $t2, 1
    j		while2				# jump to end0

end0:
    add  $t1, $t1, 1
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    j   while1

end:
    li $v0, 0           # return 0
    jr $31

    .data
aphos:
    .asciiz "*"        
