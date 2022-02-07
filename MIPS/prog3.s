# -*- mode: text -*-
#Name:  Ritika Sabharwal
#TerpConnect ID: rsabharw
#University ID: 117272918
#Discussion Section: 0107

#This file contains the assembly language to calculate a jacobsthal number.
#It reads an integer inputed by the user, stores it in the local variable
#number, and caluclates its jacobsthal number.
#jacobsthal() is a function that performs the calculation and is called in
#main() with the number inputted as the argument. It calls itself recursively
#to find the 2nd previous number and again to find the 1st previous number to
# the jacobsthal number needed to be calculated. The base case for the
#recursive calls is when the number is 0 or 1 as the jacobsthal number for 0
# is 0 and for 1 is 1. It saves 2 times the second previous jacobsthal number
#in temp1 and the first previous jacobsthal number in temp2. It then adds 
#temp1 and temp2 and saves it in ans and finally returns ans. 


.data

number:	      .word 0			#int number = 0
result:       .word 0       	 	#int result = 0

.text
main:	      li $v0, 5			#scanf("%d", &number)
              syscall
	      move $t0, $v0
              sw $t0, number

              li $sp, 0x7ffffffc	#set up stack pointer

       
              sw $t0, ($sp)		#push arg. number onto stack
              sub $sp, $sp, 4

              jal jacobsthal		#call jacobsthal
	      
	      add $sp, $sp, 4 		#pop arg. number from the stack
              
	      sw $v0, result		#result = jacobsthal(number)

              move $a0, $v0		#printf("%d", result)
              li $v0, 1
              syscall

              li $v0, 11		#printf("\n")
              li $a0, 10
              syscall

	      li $v0, 10		#quits the program
              syscall
                                        #prologue
jacobsthal:   sub     $sp, $sp, 20      # set new stack ptr
     	      sw      $ra, 20($sp)      # save ret addr in stack
      	      sw      $fp, 16($sp)      # save old frame ptr in stack
      	      add     $fp, $sp, 20      # set new frame ptr

              li $t1, -1    		#adding ans to the stack, where ans = -1
              sw $t1, 12($sp)

              li $t2, 0			#adding temp1 to the stack, temp1 = 0
              sw $t2, 8($sp)

              li $t3, 0			#adding temp2 to the stack, temp2 = 0
       	      sw $t3, 4($sp)

              bltz $t0, end		#if(n < 0), go to return statement at 
	      	   			# the end of the function
        
	      bgt $t0, 1, recursion	#if(n > 1), it should perform the 
	      	       	  		#recursion in the else statement
        
	      sw $t0, 12($sp)		#base case: ans = n
              
	      j end			#once base case has been reached, it 
	      				#should go to the return statement at 
					#the end of the function

					
recursion:   lw $t0, 4($fp)		#register t0 gets the value of n
	     sub $t0, $t0,2		#push n - 2 onto stack
	     sw $t0, ($sp)
	     sub $sp, $sp, 4
 
	     jal jacobsthal		#recursive call to jacobsthal()


	     add $sp, $sp, 4    	#pop argument n - 2 from stack

	     move $t2, $v0 		#temp1 = 2*jacobsthal(n-2)
	     mul $t2, $t2, 2
	     sw $t2, 8($sp)

	     lw $t0, 4($fp)		#push n - 1 onto stack
	     sub $t0, $t0, 1
	     sw $t0, ($sp)
	     sub $sp, $sp, 4

	     jal jacobsthal		#recursive call to jacobsthal

	     add $sp, $sp, 4  		# pop arg. n - 1 from stack
	     
	     move $t3, $v0		#temp2 = jacobsthal(n - 1)
	     sw $t3, 4($sp)

	     lw $t2, 8($sp)		#ans = temp2 + temp1
	     lw $t3, 4($sp)
	     add $t1, $t2, $t3
	     sw $t1, 12($sp)

end:         lw, $v0, 12($sp)		#register v0 gets the return value of 
	     	      			#the function
             
					#epilogue
	     lw $ra, 20($sp)		#load return addres from stack
             lw $fp, 16($sp)		#restore old frame pointer from stack
             add $sp, $sp, 20		#reset stack pointer
             jr $ra   	   		#return to caller using saved return
	     				#address
