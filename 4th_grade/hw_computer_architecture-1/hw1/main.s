.data
	# Prompts and messages
    prompt_initial: .asciiz "Enter up to 10 numbers (space-separated): "
    prompt_cmd: .asciiz "\nEnter command (I/D/R/U/Q): "
    prompt_output: .asciiz "\nThe Modified Sequence: "
    
    error_incorrect_syntax: .asciiz "\nIncorrect Syntax, Input again!\n"
    error_out_of_bounds: .asciiz "\nOut of Bounds, Input again!\n"
    
    # for printing purpose
    newline: .asciiz "\n"
    comma_space: .asciiz ", "
    
    init_buffer: .space 100  # Buffer for input string
    cmd_buffer: .space 32  # Buffer for ui
.text
	#------------------------------------------------------------------------------
	# Important Constant here:
	# ASCII space --> 32
	# ASCII null (\0) --> 0
	# ASCII newline (\n) --> 10
	
	# Important variable here:
	# $s0 = arr.length
	# $s1 = &arr[0]
	# $sp = &arr[-1]
	# $s2 = current mode
	# $s3 = first value
	# $s4 = second value
	# $s5 = flag if first value is collected
	# $s6 = flag if second value is collected
	#------------------------------------------------------------------------------
	
	#------------------------------------------------------------------------------
	# Initialize Area
INITIALIZATION:
	# Print initial prompt
	li $v0, 4
	la $a0, prompt_initial
	syscall
    
    # Read input string
	li $v0, 8
	la $a0, init_buffer
	li $a1, 100
	syscall
   	
   	# Init important variables
   	li $s0, 0  # arr.length
   	addi $s1, $sp, -4  # &arr[0]
   	
    # Parse the input and count integers
	la $t0, init_buffer  # $t0 = address of current char
	li $t1, 0  # $t1 = count of integers
    li $t2, 0  # $t2 = current number being parsed
    li $t3, 0  # $t3 = flag: 1 if currently parsing a number

parse_loop_init:
    lb $t5, 0($t0)  # Load current character
    
    # Check for end of string (null or newline)
    beq $t5, $zero, parse_done_init
    beq $t5, 10, parse_done_init
    
    # Check if it's a space
    beq $t5, 32, handle_space_init
    
    # At this point, it has to be a number
    bgt $t5, 57, INITIALIZATION
    blt $t5, 48, INITIALIZATION
    
    # It's a digit - parse it
    li $t3, 1  # Set parsing flag
    addi $t5, $t5, -48  # Convert ASCII to integer
    mul $t2, $t2, 10  # Shift current number left (decimal)
    add $t2, $t2, $t5  # Add new digit
    j next_char_init
    
handle_space_init:
	beq $t3, 0, next_char_init  # double blank
    # Store the number in temp array
    addi $sp, $sp, -4
    sw $t2, ($sp)
    addi $t1, $t1, 1
    
    # Reset for next number
    li $t2, 0
    li $t3, 0
    
next_char_init:
    addi $t0, $t0, 1
    j parse_loop_init
    
parse_done_init:
	# Save last number if we were parsing one
    beq $t3, $zero, finish_init
    
    addi $sp, $sp, -4
    sw $t2, ($sp)
    addi $t1, $t1, 1
    
finish_init:
	bgt $t1, 10, INITIALIZATION  # at most 10 numbers
    addi $s0, $t1, 0  # set the init arr.length
    
    j end
	#------------------------------------------------------------------------------
	
	#------------------------------------------------------------------------------
    # The UI loop
ui_loop:
	# Print command prompt
    li $v0, 4
    la $a0, prompt_cmd
    syscall
    
    # Read command
    li $v0, 8
    la $a0, cmd_buffer
    li $a1, 32
    syscall
    
    # Parse the cmd, init variables
	la $t0, cmd_buffer  # $t0 = address to current char
	li $t1, 0  # $t1 = flag: 1 if entered a command type
	li $t2, 0  # $t2 = current number being parsed
    li $t3, 0  # $t3 = flag: 1 if currently parsing a number
	# $t5 is used as current byte value
    li $t7, 0  # $t6 = flag: 1 if process is finished
    
    li $s2, 0  # $s2 = current mode
    li $s3, 0  # $s3 = first value
    li $s4, 0  # $s4 = second value
    li $s5, 0  # $s5 = flag: 1 if collected the first value
    li $s6, 0  # $s6 = flag: 1 if collected the second value
    
parse_loop:
	beq $t7, 1, finish_cmd_parsing
    lb $t5, 0($t0)  # Load current character
    
    # Check for end of string (null or newline)
    beq $t5, $zero, parse_done
    beq $t5, 10, parse_done
    
    # Check if it's a 'I/D/R/U/Q'
    beq $t5, 73, mode_selection
    beq $t5, 68, mode_selection
    beq $t5, 82, mode_selection
    beq $t5, 85, mode_selection
    beq $t5, 81, EXIT
    
    # Check if it's a space
    beq $t5, 32, handle_space
    
    # At this point, it has to be a number
    bgt $t5, 57, incorrect_syntax
    blt $t5, 48, incorrect_syntax
    
    # It's a digit - parse it
    li $t3, 1  # Set parsing flag
    addi $t5, $t5, -48  # Convert ASCII to integer
    mul $t2, $t2, 10  # Shift current number left (decimal)
    add $t2, $t2, $t5  # Add new digit
    j next_char
    
mode_selection: 
	# check the flag to see if mode has already been selected
	beq $t1, 1, incorrect_syntax
	
	# save the mode
	addi $s2, $t5, 0
	li $t1, 1
	
	# add this because a blank MUST follow the mode
	addi $t0, $t0, 1
	j next_char
	
handle_space:
	beq $t3, 0, next_char  # double blank
    # Store the number
    # if we haven't collect the first one
    beq $s5, 0, save_first_value
    # if we haven't collect the second one
    beq $s6, 0, save_second_value
    
    # At this point, user input 3 numbers
    j incorrect_syntax
    
    save_first_value:
    	addi $s3, $t2, 0
    	li $s5, 1
    	j value_saved
    	
    save_second_value:
    	addi $s4, $t2, 0
    	li $s6, 1
    	j value_saved
    	
    value_saved:
    # Reset for next number
    li $t2, 0
    li $t3, 0
    
    j next_char
    
next_char:
    addi $t0, $t0, 1
    j parse_loop
    
parse_done:
	# Save last number if we were parsing one
    beq $t3, $zero, finish_cmd_parsing
    
    li $t7, 1  # set finish flag as 1
    # save the current number
    j handle_space
    
finish_cmd_parsing:
    #------------------------------------------------------------------------------
    
    # NOW WE HAVE THE FOLLOWING DATA ALL PREPARED
    # $s0 = arr.length
	# $s1 = &arr[0]
	# $sp = &arr[-1]
	# $s2 = current mode
	# $s3 = first value
	# $s4 = second value
	# $s5 = flag if first value is collected
	# $s6 = flag if second value is collected
	# start executing the main program
	# Check if it's 'I/D/R/U'
    beq $s2, 73, I_type
    beq $s2, 68, D_type
    beq $s2, 82, R_type
    beq $s2, 85, U_type
	#------------------------------------------------------------------------------
I_type:
    # check if it is incorrect syntax
    bne $s5, 1, incorrect_syntax
    bne $s6, 1, incorrect_syntax
    
    # check if it is out of bounds
    # position can be 0 ~ arr.length
    bgt $s3, $s0, out_of_bounds
    blt $s3, 0, out_of_bounds
    
    # at most 20 numbers
    bge $s0, 20, out_of_bounds
    
    # Start Inserting!!    
    addi $t0, $s3, 0  # $t0 is like i
    addi $t1, $sp, 0  # $t1 is the addr of the last number before inserting
    
	# allocate space
    addi $sp, $sp, -4
    # we need for (int i = first_input; i < arr.length; i ++) times
    I_loop:
    	bge $t0, $s0, exit_I_loop
    	
    	# copy the value in ($t1) to -4($t1)
    	lw $t2, ($t1)
    	sw $t2, -4($t1)
    	
    	# $t1 += 4
    	addi $t1, $t1, 4
    	# i ++
    	addi $t0, $t0, 1
    	
    	j I_loop
    	
    exit_I_loop:
    	# right now, we just need to copy the second input to the position which is -4($t1)
    	sw $s4, -4($t1)
    	
    # arr.length += 1
    addi $s0, $s0, 1
    
    j end
    #------------------------------------------------------------------------------

    #------------------------------------------------------------------------------
D_type:
    # check if it is incorrect syntax
    bne $s5, 1, incorrect_syntax
    bne $s6, 0, incorrect_syntax
    
    # check if it is out of bounds
    # position can be 0 ~ arr.length - 1
    bge $s3, $s0, out_of_bounds
    blt $s3, 0, out_of_bounds
    
    # Start deleting!!
    addi $t0, $s3, 1  # $t0 is like i
    sll $t1, $t0, 2
    sub $t1, $s1, $t1  # $t1 is the addr of the first target to copy to previous position
    
    # we need for (int i = first_input + 1; i < arr.length; i ++) times
    D_loop:
    	bge $t0, $s0, exit_D_loop
    	
    	# copy the value in ($t1) to 4($t1)
    	lw $t2, ($t1)
    	sw $t2, 4($t1)
    	
    	# $t1 -= 4
    	addi $t1, $t1, -4
    	# i ++
    	addi $t0, $t0, 1
    	
    	j D_loop
    	
    exit_D_loop:
    	
    # arr.length -= 1
    addi $s0, $s0, -1
    # free space
    addi $sp, $sp, 4
    
    j end
    #------------------------------------------------------------------------------

    #------------------------------------------------------------------------------
R_type:
    # check if it is incorrect syntax
    bne $s5, 1, incorrect_syntax
    bne $s6, 1, incorrect_syntax
    bgt $s3, $s4, incorrect_syntax
    
    # check if it is out of bounds
    # position can be 0 ~ arr.length - 1
    bge $s3, $s0, out_of_bounds
    blt $s3, 0, out_of_bounds
    bge $s4, $s0, out_of_bounds
    blt $s4, 0, out_of_bounds
    
    beq $s3, $s4, end  # do nothing
    
    # Start Reversing!!
    # locate the start position
    sll $t0, $s3, 2
    sub $t0, $s1, $t0
    
    # locate the stop position
    sll $t1, $s4, 2
    sub $t1, $s1, $t1
    
    # We need while ($t0 > $t1) { swap values }
    R_loop:
    	ble $t0, $t1, exit_R_loop
    	
    	# swap the values in ($t0) and ($t1)
    	lw $t2, ($t0)
    	lw $t3, ($t1)
    	sw $t2, ($t1)
    	sw $t3, ($t0)
    	
    	# $t0 goes down the stack, while $t1 goes up
    	addi $t0, $t0, -4
    	addi $t1, $t1, 4
    	
    	j R_loop
    	
    exit_R_loop:
    
    j end
    #------------------------------------------------------------------------------

    #------------------------------------------------------------------------------
U_type:
	# check if it is incorrect syntax
    bne $s5, 1, incorrect_syntax
    bne $s6, 0, incorrect_syntax
    
    # Start removing duplicates
    li $t0, 0  # flag if it is the second-seen
    li $t1, 0  # just like i
    addi $t2, $s1, 0  # set init base address
    
    # we need for (int i = 0; i < arr.length; i ++) where arr.length might 
    U_loop:
    	bge $t1, $s0, exit_U_loop
    	
    	lw $t3, ($t2)
    	beq $t3, $s3, pulling
    	
    	addi $t1, $t1, 1  # i ++
    	addi $t2, $t2, -4  # go to the next number
    	
    	j U_loop

    pulling:
    	beq $t0, 0, first_seen
    	
    	# discovering target, we keep i the same while pooling numbers after it
    	# We want for (int j = i + 1; j < arr.length; j ++), basically just like D_type but I am lazy to write function
    	addi $t3, $t1, 1  # $t3 is like j
    	sll $t4, $t3, 2
    	sub $t4, $s1, $t4  # $t4 is the addr of the first target to copy to previous position
    
    	pulling_loop:
    		bge $t3, $s0, exit_pulling_loop
    	
    		# copy the value in ($t4) to 4($t4)
    		lw $t5, ($t4)
    		sw $t5, 4($t4)
    	
    		# $t4 -= 4
    		addi $t4, $t4, -4
    		# j ++
    		addi $t3, $t3, 1
    	
    		j pulling_loop
    	
    	exit_pulling_loop:
    	
    	# arr.length -= 1
    	addi $s0, $s0, -1
    	# free space
    	addi $sp, $sp, 4
    	
    	j U_loop
    
    first_seen:
    	li $t0, 1  # set the flag
    	addi $t1, $t1, 1  # i ++
    	addi $t2, $t2, -4  # go to the next number
    	
    	j U_loop
    	
	exit_U_loop:
	
	j end
    #------------------------------------------------------------------------------
    
    #------------------------------------------------------------------------------
    # Error handler, ALWAYS JUMP BACK TO ui_loop
incorrect_syntax:
	# Print error msg
    li $v0, 4
    la $a0, error_incorrect_syntax
    syscall
    
    j ui_loop
    
out_of_bounds:
	# Print error msg
    li $v0, 4
    la $a0, error_out_of_bounds
    syscall
    
    j ui_loop
    #------------------------------------------------------------------------------

end:
    # print out to check
	li $t0, 0  # it's like i
	addi $t1, $s1, 0  # the base address
	
	# print output prompt
	li $v0, 4
	la $a0, prompt_output
	syscall

print_loop:
	bge $t0, $s0, exit_print_loop
	
	# print current
	lw $a0, ($t1)
	li $v0, 1
    syscall
    
    li $v0, 4
    la $a0, comma_space
    syscall
    
    addi $t1, $t1, -4
    addi $t0, $t0, 1
    j print_loop
	
exit_print_loop:
	# print a '\n'
	li $v0, 4
	la $a0, newline
	syscall
	
	j ui_loop
	
EXIT:
