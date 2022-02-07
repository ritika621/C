# -*- mode: text -*-
#Name:  Ritika Sabharwal
#TerpConnect ID: rsabharw 
#University ID: 117272918
#Discussion Section: 0107 
#
#This file reads integers for length, width, and height, and caluclates the 
#area of prism based on these dimensions.This is all done in the main() function
#It only uses global variables. It also stores the caluclate prism area in 
#the variable and prints it followed by a newline.

       .data

length:  .word 0
width:   .word 0
height:  .word 0
ans:     .word 0

      .text

main:   li $t0, -1		#ans = -1
        sw $t0, ans

        li $v0, 5               #scanf("%d", &length)
        syscall
        move $t1, $v0
        sw $t1, length

        li $v0, 5		#scanf("%d", &width)
        syscall
        move $t2, $v0
        sw   $t2, width

        li $v0, 5		#scanf("%d", &height)
        syscall
        move $t3, $v0
        sw $t3, height

        blez $t1, print		#if(length <= 0), ans should be printed as -1 
	     	  		#without calculating the area
	blez $t2, print		#if(width <= 0), and should be printed as -1 
	     	  		#without calculating the area
	blez $t3, print		#if(height <= 0), ans should be printed as -1
	     	  		#without calculating the area
        mul $t5, $t1, $t2	#stores length * width in reigster t5
        mul $t6, $t2, $t3	#stores width * height in register t6
        mul $t7, $t3, $t1	#stores height * length in register t7
        add $t0, $t5, $t6	# length*width +  width*height 
        add $t0, $t0, $t7	#length*width + width*height + height*length
        mul $t0, $t0, 2		#2*(length*width + width*height + height*length)

print:  move $a0, $t0 		#printf("%d", ans)
        li   $v0, 1
        syscall

        li $v0, 11		#printf("\n")
	li $a0, 10		
	syscall
	
        li $v0, 10		#quits the program
        syscall
