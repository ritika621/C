# -*- mode: text -*-
#Name:  Ritika Sabharwal
#TerpConnect ID: rsabharw
#University ID: 117272918
#Discussion Section: 0107

#This file contains the assembly language to calculate a jacobsthal number.
#It reads an integer inputed by the user, stores it in the local variable 
#number, and caluclates its jacobsthal number.
#jacobsthal() is a function that performs the calculation and is called in 
#main() with the number inputted as the argument. It then stores the 
#jacobsthal number in the local variable result of main, and prints it.
 
.data

number:      .word 0			#int number = 0
result:	     .word 0			#int result = 0

.text
main:	     li $v0, 5			#scanf("%d", &number)
	     syscall	
	     move $t0, $v0
	     sw $t0, number	

	     li $sp, 0x7ffffffc         #set up stack pointer

	     sw $t0, ($sp)		#push argument number onto stack
	     sub $sp, $sp, 4	        #updates stack pointer to one memory
	     	      	   		#location 
	    	 	      	        #below its current position
	
	     jal jacobsthal		#call jacobsthal

             add $sp, $sp, 4		#pop arg. number from the stack
	
	     sw $v0, result		#stores the return value of 
	     	     			#jacobsthal in result

	     move $a0, $v0		#printf(result)
       	     li $v0, 1
	     syscall

	     li $v0, 11			#printf('\n')
	     li $a0, 10
	     syscall

	     li $v0, 10			#quits the program
	     syscall
					#prologue
jacobsthal:  sub     $sp, $sp, 24      	# set new stack ptr
      	     sw      $ra, 24($sp)     	# save ret addr in stack
      	     sw      $fp, 20($sp)     	# save old frame ptr in stack
      	     add     $fp, $sp, 24     	# set new frame ptr

	     li $t1, -1	       		#adding ans to the stack, where ans=-1
	     sw $t1, 16($sp)		 

	     li $t2, 0			#adding prev to the stack, prev = 0
	     sw $t2, 12($sp)

	     li $t3, 0			#adding temp to the stack, temp = 0
	     sw $t3, 8($sp)

	     li $t4, 2			#adding i to the stack, i = 2
	     sw $t4, 4($sp)

	     bltz $t0, end		#if(n < 0), go to return statement, and
	     	       			#return ans back to main()
	
	     
	     bgt $t0, 1, else		#if(n > 1), it should perform what is in
	     	      	 		#the else statement
		
 	     sw $t0, 16($sp)		#ans = n 
	     
	     j end			#after doing ans = n, it should go to
	       				#the end of jacobsthal() and return ans

else:	     li $t1, 1			#ans = 1
	     sw $t1, 16($sp)

	     li $t2, 0			#prev = 0 ;
	     sw $t2, 12($sp)

loop:	     bgt $t4, $t0, end		#if(i > n), it should exit the loop and
	     	      	   		#go to the end of the function to return

	
	     sw $t2, ($sp)		#push argument prev onto stack
	     sub $sp, $sp, 4

	     sw $t1, ($sp)		# push argument ans onto stack
	     sub $sp, $sp, 4

	     jal helper			#call helper()

	     add $sp, $sp, 8		# pop ans and prev from stack
	     
	     sw $v0, 8($sp)		#temp = helper(prev, ans)
	     
	     sw $t1, 12($sp)		#prev = ans
	     lw $t2, 12($sp)		#register t2 has the updated value
	     	     			#of prev

	     lw, $t5, 8($sp)		#ans = temp
	     sw $t5, 16($sp)
	     
	     lw $t1, 16($sp)		#register t1 has the updated value of 
	     	     			#ans
	     
	     add $t4, $t4, 1		# i++
	     sw $t4, 4($sp)
	
	     j loop			#go to loop condition after 
  					#each iteration
	
	
					#prologue
helper:      sub $sp,$sp, 8		#set new stack ptr
	     sw $ra, 8($sp)		#save ret address in stack
	     sw $fp, 4($sp)		#save old frame ptr in stack
	     add $fp, $sp, 8		#set new frame ptr

	     lw $t5, 16($sp)		# 2 * x		
	     mul $t5, $t5, 2

	     lw $t6, 12($sp)		#2*x + y
	     add $t6, $t6, $t5

	     move $v0, $t6		#register v0 gets the return 
	     	       			#value of helper()

					#epilogue
	     lw $ra, 8($sp)		#load return address from stack
	     lw $fp, 4($sp)		#restore old frame pointer from	stack
	     add $sp, $sp, 8		#reset stack pointer
	     jr $ra   	   		#return to caller using saved
	     				#return address			
					
end:	     lw $t1, 16($sp)		#return ans
	     move $v0, $t1

					#epilogue
	     lw $ra, 24($sp)		#load return address from stack
	     lw $fp, 20($sp)		#restore old frame pointer from stack
	     add $sp, $sp, 24		#reset stack pointer
	     jr $ra   	   		#return to caller using saved 
	     				#return address

