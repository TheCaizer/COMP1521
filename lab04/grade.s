# read a mark and print the corresponding UNSW grade

main:
    la $a0, prompt      # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", mark);
    syscall

    blt $v0, 50, iffl
    blt $v0, 65, ifps
    blt $v0, 75, ifcr
    blt $v0, 85, ifdn
    blt $v0, 101, ifhd


    jr $ra              # return

iffl:
    la $a0, fl          # printf("FL\n");
    li $v0, 4
    syscall

    jr $ra              # return

ifps:
    la $a0, ps          # printf("PS\n");
    li $v0, 4
    syscall

    jr $ra              # return

ifcr:
    la $a0, cr          # printf("CR\n");
    li $v0, 4
    syscall

    jr $ra              # return

ifdn:
    la $a0, dn         # printf("DN\n");
    li $v0, 4
    syscall

    jr $ra              # return

ifhd:
    la $a0, hd          # printf("HD\n");
    li $v0, 4
    syscall

    jr $ra              # return
    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"