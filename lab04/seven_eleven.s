# Read a number and print positive multiples of 7 or 11 < n

main:                  # int main(void) {

    la $a0, prompt     # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", number);
    syscall

    move $t1, $v0       #sets the variable in v0 to t1

    sub $t1, $t1, 1
    
    li $t0, 1           #i = 1;

loop:
    blt $t1, $t0 end   #while(i< number);

    remu $t4, $t0, 11
    beqz $t4, eleven

    remu $t3 , $t0, 7  
    beqz $t3, seven
    
    addi  $t0, $t0, 1   #   i++;

    b		loop			# branch to loop 

seven:
    move $a0, $t0       #printf("%d")
    li $v0, 1
    syscall 

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi  $t0, $t0, 1   #   i++;

    b       loop
eleven:
    move $a0, $t0       #printf("%d")
    li $v0, 1
    syscall 

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi  $t0, $t0, 1   #   i++;

    b       loop

end:
    jr   $ra           # return

    .data
prompt:
    .asciiz "Enter a number: "
