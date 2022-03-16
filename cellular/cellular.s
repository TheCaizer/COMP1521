########################################################################
# COMP1521 20T2 --- assignment 1: a cellular automaton renderer
#
# Written by Jackie Cai, July 2020.


# Maximum and minimum values for the 3 parameters.

MIN_WORLD_SIZE	=    1
MAX_WORLD_SIZE	=  128
MIN_GENERATIONS	= -256
MAX_GENERATIONS	=  256
MIN_RULE	=    0
MAX_RULE	=  255

# Characters used to print alive/dead cells.

ALIVE_CHAR	= '#'
DEAD_CHAR	= '.'

# Maximum number of bytes needs to store all generations of cells.

MAX_CELLS_BYTES	= (MAX_GENERATIONS + 1) * MAX_WORLD_SIZE

    .data

# `cells' is used to store successive generations.  Each byte will be 1
# if the cell is alive in that generation, and 0 otherwise.

cells:	.space MAX_CELLS_BYTES


# Some strings you'll need to use:

prompt_world_size:	.asciiz "Enter world size: "
error_world_size:	.asciiz "Invalid world size\n"
prompt_rule:		.asciiz "Enter rule: "
error_rule:		.asciiz "Invalid rule\n"
prompt_n_generations:	.asciiz "Enter how many generations: "
error_n_generations:	.asciiz "Invalid number of generations\n"

    .text
    #   $s0 = world_size
    #   $s1 = rule
    #   $s2 = n_generations
    #   $s3 = reverse
    #   $s4 = g
    #   $a1 = world_size for run_generation
    #   $a2 = which_generation for run_generation
    #   $a3 = rule for run generation
    #   $a1 = world_size for print_generation
    #   $a2 = which_generation for print genreation
    #   need to save $a0 for printf and putchar for print_generation
    #   $t6 = used for calculating and store numbers (temp)
    #   $t7 = used for address of cells (temp)
    #   t9 = temp register for number used for calculations
main:   
        sw      $fp, -4($sp)            # stackframe prolouge
        la      $fp, -4($sp)            #
        sw      $ra, -8($sp)            #
        sw      $s0, -12($sp)           #
        sw      $s1, -16($sp)           #
        sw      $s2, -20($sp)           #
        sw      $s3, -24($sp)           #
        sw      $s4, -28($sp)           #
        add     $sp, $sp, -28           #

        la  	$a0, prompt_world_size  # printf("Enter world size: ");
        li  	$v0, 4                  #
        syscall                     	#

        li  	$s0, 0                  # world size = 0;
        
        li  	$v0, 5                  # scanf("%d", &world_size);
        syscall                     	#

        move 	$s0, $v0               	# move world size into $s0
        blt 	$s0, MIN_WORLD_SIZE invalid_world   # if (world_size < MIN_WORLD_SIZE)
        bgt 	$s0, MAX_WORLD_SIZE invalid_world   # || world_size > MAX_WORLD_SIZE)

        la  	$a0, prompt_rule        # printf("Enter rule: ");
        li  	$v0, 4                  #
        syscall                     	#

        li  	$s1, 0                  # rule = 0;
        
        li  	$v0, 5                  # scanf("%d", &rule);
        syscall                     	#

        move 	$s1, $v0               	# move rule into $s1
        blt 	$s1, MIN_RULE invalid_rule  # if (rule < MIN_RULE
        bgt 	$s1, MAX_RULE invalid_rule  # rule > MAX_RULE)

        la  	$a0, prompt_n_generations   # printf("Enter how many generations: ");
        li  	$v0, 4                  #
        syscall                     	#

        li  	$s2, 0                  # n_generations = 0;
        
        li  	$v0, 5                  # scanf("%d", &n_generations);
        syscall                     	#

        move 	$s2, $v0               	# move n_generations into $s2
        blt 	$s2, MIN_GENERATIONS invalid_gen # if (n_generations < MIN_GENERATIONS
        bgt 	$s2, MAX_GENERATIONS invalid_gen # n_generations > MAX_GENERATIONS)

        li   	$a0, '\n'      		    # putchar('\n');
        li	    $v0, 11        		    #
        syscall             		    #

        li 	    $s3, 0           	    # int reverse = 0
if_n_generations:
        bltz 	$s2, end_if_n_gen       # if(n_generations < 0)

        la      $t7, cells              # load cell address
        li      $t9, 2                  # $t9 = 2
        div     $t6, $s0, $t9           # world_size/2
        add     $t7, $t7, $t6           # find address of cells[0][world_size/2]
        li      $t6, 1                  # store 1 in register $t6
        sb      $t6, ($t7)              # cells[0][world_size / 2] = 1;

        li      $s4, 1                  # int g = 1

for_loop_g:
        bgt     $s4, $s2 if_reverse     # g > n_generations go to if 
    
        move    $a0, $s0                # move world_size as first arg                
        move    $a1, $s4                # move g as second arg
        move    $a2, $s1                # move rule as third arg
        jal     run_generation          # run the function

        j       end_for_loop_g          #jump to end loop
if_reverse:
        move    $s4, $s2
        li      $t2, 1                  # int g = n_generations
        beq     $s3, $t2 reverse_true   # jump to reverse_true if reverse = 1
                                        # since reverse if false set g as zero
        li      $s4, 0                  # int g = 0
        beqz    $s3, reverse_false      # jump to reverse_false if reverse = 0

reverse_true:
        bltz    $s4  return0            # g < 0 jump to return0
        move    $a1, $s0                # move world_size
        move    $a2, $s4                # move g
        jal     print_generation        # use function

end_reverse_true:
        li      $t9, 1                  # $t9 = 1
        sub     $s4, $s4, $t9           # g--

        j       reverse_true            #

reverse_false:
        bgt     $s4, $s2, return0       # g > n_generations return0
        move    $a1, $s0                # move world_size
        move    $a2, $s4                # move g
        jal     print_generation        # use function

end_reverse_false:
        addi    $s4, $s4, 1             # g++
        j       reverse_false           #

return0:
        li  	$v0, 0                  # return 0
        j   	main_epilogue           #

return1:
        li 	    $v0, 1                  # return 1
        j       main_epilogue           #
main_epilogue:
        lw      $ra, -4($fp)            # stackframe epilogue
        lw      $s0, -8($fp)            #
        lw      $s1, -12($fp)           #
        lw      $s2, -16($fp)           #
        lw      $s3, -20($fp)           #
        lw      $s4, -24($fp)           #
        la      $sp, 4($fp)             #
        lw      $fp, ($fp)              #
        jr  	$ra                     #

invalid_world:
        la 	    $a0, error_world_size   # printf("Invalid world size\n");
        li 	    $v0, 4			        #
        syscall                     	#

        j       return1                 # jump to return1

invalid_rule:
        la 	    $a0, error_rule         # printf("Invliad rule\n");
        li 	    $v0, 4                  #
        syscall                     	#

        j       return1                 # jump to return1

invalid_gen:
        la      $a0, error_n_generations# printf("Invalid number of generations\n");
        li      $v0, 4                  #
        syscall                     	#

        j       return1                 # jump to return1

end_if_n_gen:
        li      $s3, 1                  # reverse = 1
        li      $t9, -1
        mul     $s2, $s2, $t9           # n_generations = -n_generations
        j	    if_n_generations	    # jump back to if statement
        
end_for_loop_g:    
        add     $s4, $s4, 1             # g++
        j       for_loop_g              # jump back to start of loop
                    
    # $a0 = world_size
    # $a1 = which_generation (g)
    # $a2 = rule
    # $t0 = cells address
    # $t1 = calcualting results (temp)
    # $t2 = register for numbers for calclating (temp)
    # $t3 = state
    # $t4 = bit
    # $t5 = x 
    # $t6 = left
    # $t7 = right
    # $t8 = centre
    # $t9 = set
run_generation:
        sw      $fp, -4($sp)    # stackframe prolouge
        la      $fp, -4($sp)    #
        sw      $ra, -8($sp)    #
        sw      $s0, -12($sp)   #
        sw      $s1, -16($sp)   #
        sw      $s2, -20($sp)   #
        sw      $s3, -24($sp)   #
        sw      $s4, -28($sp)   #
        add     $sp, $sp, -28   #

        li      $t5, 0          # x = 0
run_loop0:
        bge     $t5, $a0 end_run_generation #if x >= world_size go next loop
        li      $t6, 0          # left = 0
        bgtz    $t5, run_if0    # if (x > 0)
end_if0:
        la      $t0, cells      # put address of cells in $t0
        li      $t2, 1          # $t2 = 1
        sub     $t1, $a1, $t2   # whichgenerations - 1
        li      $t2, 128
        mul     $t1, $t1, $t2   # which_generation -1 * world_size
        add     $t0, $t0, $t1   # cells[address] = cells[address] + whichgenerations - 1
        add     $t0, $t0, $t5   # cells[address] = cells + x + [which_gen -1]
        lb      $t8, ($t0)      # centre = cells[address]

        li      $t7, 0          # right = 0

        li      $t2, 1          # $t2 = 1
        sub     $t1, $a0, $t2   # $t1 = world_size - 1

        blt     $t5, $t1, run_if1 # x < world_size -1 jump to run_if1

end_if1:
        sll     $t6, $t6, 2     # left = left << 2
        sll     $t8, $t8, 1     # centre = centre << 1
        sll     $t7, $t7, 0     # right = right << 0
        or      $t3, $t6, $t8   # state = left << 2 | centre << 1
        or      $t3, $t3, $t7   # state = state (left << 2 | centre << 1) | eight << 0

        li      $t2, 1          # $t2 = 1
        sllv    $t4, $t2, $t3   # int bit = 1 << state;
        and     $t9, $a2, $t4   # int set = rule & bit;

        bnez    $t9, run_if2    # if(set != 0) jump to if
                                # ELSE STATEMENT
        la      $t0, cells      # put address of cells in $t0
        li      $t2, 128
        mul     $t1, $a1, $t2   # which_generation * world_size
        add     $t0, $t0, $t1   # cells = cells + which_generations
        add     $t0, $t0, $t5   # cells = cells + which_generations +x
        li      $t2, 0
        sb      $t2, ($t0)      # cells[which_generation][x] = 0;

        j       end_run_loop0   #
run_if2:
        la      $t0, cells      # put address of cells in $t0
        li      $t2, 128
        mul     $t1, $a1, $t2   # which_generation * world_size
        add     $t0, $t0, $t1   # cells = cells + which_generations
        add     $t0, $t0, $t5   # cells = cells + which_generations +x
        li      $t2, 1
        sb      $t2, ($t0)      # cells[which_generation][x] = 1;

        j       end_run_loop0   #
run_if1:
        la      $t0, cells      #put address of cells in $t0
        li      $t2, 1          # $t2 = 1
        sub     $t1, $a1, $t2   # whichgenerations - 1
        li      $t2, 128
        mul     $t1, $t1, $t2   # which_generation -1 * world_size
        add     $t0, $t0, $t1   # cells[address] = cells[address] + whichgenerations - 1
        addi    $t1, $t5, 1     # reuse t1 for [x+1]
        add     $t0, $t0, $t1   # cell[adress] = [which_gen -1] + [x+1]
        lb      $t7, ($t0)      # right = cells[which_generation - 1][x + 1];

        j       end_if1         #
run_if0:
        la      $t0, cells      # put address of cells in $t0
        li      $t2, 1          # $t2 = 1
        sub     $t1, $a1, $t2   # whichgenerations - 1
        li      $t2, 128
        mul     $t1, $t1, $t2   # which_generation -1 * world_size
        add     $t0, $t0, $t1   # cells[address] = cells[address] + whichgenerations - 1
        li      $t2, 1
        sub     $t1, $t5, $t2   # reuse t1 for [x-1]
        add     $t0, $t0, $t1   # cell[adress] = [which_gen -1] + [x-1]
        lb      $t6, ($t0)      # left = cells[which_generation - 1][x - 1];

        j       end_if0         #
end_run_loop0:
        add     $t5, $t5, 1     # x++
        j       run_loop0       #

end_run_generation:
        lw      $ra, -4($fp)    # stackframe epilogue
        lw      $s0, -8($fp)    #
        lw      $s1, -12($fp)   #
        lw      $s2, -16($fp)   #
        lw      $s3, -20($fp)   #
        lw      $s4, -24($fp)   #
        la      $sp, 4($fp)     #
        lw      $fp, ($fp)      #
        jr  	$ra             #
    #
    # $a1 = world_size
    # $a2 = which_generation
    # $t0 = cells[address]
    # $t1 = 0 or 1 depending on the cell
    # $t2 = 1
    # $t3 = x

print_generation:
        sw      $fp, -4($sp)    # stackframe prolouge
        la      $fp, -4($sp)    #
        sw      $ra, -8($sp)    #
        sw      $s0, -12($sp)   #
        sw      $s1, -16($sp)   #
        sw      $s2, -20($sp)   #
        sw      $s3, -24($sp)   #
        sw      $s4, -28($sp)   #
        add     $sp, $sp, -28   #

        move    $a0, $a2        # move which_generation to print it
        li      $v0, 1          # printf("%d", which_generation);
        syscall                 #

        li   	$a0, '\t'       # putchar('\t');
        li	    $v0, 11         #
        syscall                 #

        li      $t2, 1          # $t2 = 1
        li      $t3, 0          # x = 0
print_for0:
        bge     $t3, $a1, end_print_for0 # if x >= world_size brach to end
        la      $t0, cells      # load adress into t0
        li      $t2, 128
        mul     $t1, $a2, $t2   # which_generation * world_size
        li      $t2, 1
        add     $t0, $t0, $t1   # cells = cells + which_generation
        add     $t0, $t0, $t3   # cells = cells + x
        lb      $t1, ($t0)      # load 0 or 1

        beqz    $t1, print_dead # print dead character

        li      $a0, ALIVE_CHAR # putchar(ALIVE_CHAR)
        li      $v0, 11         #
        syscall                 #

        addi    $t3, $t3, 1     # x++
        j       print_for0      #
end_print_for0:
        li   	$a0, '\n'       # putchar('\n');
        li	    $v0, 11        	#
        syscall             	#

        j       end_print_generation #

print_dead:
        li      $a0, DEAD_CHAR  # putchar(DEAD_CHAR)
        li      $v0, 11         #
        syscall                 #

        addi    $t3, $t3, 1     # x++
        j       print_for0      #
end_print_generation:
        lw      $ra, -4($fp)    # stackframe epilogue
        lw      $s0, -8($fp)    #
        lw      $s1, -12($fp)   #
        lw      $s2, -16($fp)   #
        lw      $s3, -20($fp)   #
        lw      $s4, -24($fp)   #
        la      $sp, 4($fp)     #
        lw      $fp, ($fp)      #
        jr  	$ra             #