/* Name: Ritika Sabharwal
   TerpConnect ID: rsabharw
   University ID number: 117272918
   Discussion section: 0107
*/

/*I pledge on my honor that I have not given or received any unauthorized 
assistance on this assignment.*/
                                                                                
/*This file prints instructions with their opcode, extension(if any),registers
 used, and memory address. It also displays instructions with memory addresses
 starting from 0, printed in hexadecimals followed by the instructions.
 It also gives informtation of the first index where a register 
is set/modified and whether a program is safe or not, depending on the use of
 registers without values set to them before being used.*/



#include "machine.h"
#include <stdio.h>

/*defining symbolic constants for bitmasking*/
#define MASK_REGISTERS 7
#define MASK_MEMORY_ADDRESS 32767
#define MASK_SYS_EXT 7

/*defining symbolic constants for bit shifting*/
#define SHIFT_OPCODE 27
#define SHIFT_REGISTER_1 21
#define SHIFT_REGISTER_2 18
#define SHIFT_REGISTER_3 15
#define SHIFT_SYS_EXT 24

static int check_invalid(Wrd instruction);

/*This function prints out the instruction with its opcode, extension(if any),
 registers used and memory address if used. It also checks for invalid 
instructions.*/
                                                                               
unsigned short print_instruction (Wrd instruction)
{
  int opcode = 0;
  int i = 0;
  int sys_ext = 0;
  int register_1 = 0;
  int register_2 = 0;
  int register_3 = 0;
  int memory_address = 0;
  char op_codes[27][6] = {"plus", "minus", "times", "div", "mod", "neg", "abs", 
			  "shl","shr", "band", "bor", "bxor", "bneg", "and", 
			  "or", "not", "eq", "neq", "le", "lt", "ge", "gt",
			  "move", "lw", "sw", "li","sys"};

  if (check_invalid(instruction) == 0)
    return 0;

  else
    {
      /*shifting bits to the right and masking them with an &*/
      opcode = instruction >> SHIFT_OPCODE;
      sys_ext = MASK_SYS_EXT & (instruction >> SHIFT_SYS_EXT);
      memory_address = 32767 & instruction;
      register_1 = MASK_REGISTERS & (instruction >> SHIFT_REGISTER_1);
      register_2 = MASK_REGISTERS & ( instruction >> SHIFT_REGISTER_2);
      register_3 = MASK_REGISTERS & (instruction >> SHIFT_REGISTER_3);

    /*printing opcodes*/
    for (i = 0; i < 27; i++)
      if (i == opcode)
	printf("%s", op_codes[i]);

    /*printing sys extension is there is one*/
    if (opcode == 26)
     {
	printf ("\t%d", sys_ext);
	if (sys_ext != 4)
	  printf("\tR%d", register_1);
     }
	   
     else 
      printf("\tR%d", register_1);
		
    if (opcode < 23)
      printf("\tR%d", register_2);

    if (opcode < 15 && opcode != 5 && opcode !=12 && opcode != 6)
      printf("\tR%d", register_3);
	       
    if ((opcode > 15 && opcode <26) && opcode != 22) 
     {
       if (opcode != 25)
        printf("\t%05d", memory_address);
       else
        printf("\t%d", memory_address);
     }
   }
  
  return 1;    
}
                                                                                
/*This function prints the instructions with corresponding memory addresses 
starting from 0. It also checks if an instruction is invalid*/

unsigned short disassemble(const Wrd program[], unsigned short num_instrs, 
unsigned short *const bad_instr)
{
  int memory_count = 0;
  int i = 0;
  
  /*checks for error cases*/
  if (bad_instr == NULL || num_instrs == 0 || num_instrs > NUM_WORDS || 
      program == NULL)
        return 0;
                                                                                
  for (i = 0; i < num_instrs; i++)
    /*checks for invalid instructions using the helper function*/
    if (check_invalid(program[i]) == 0)
      {
	*bad_instr = i;
	return 0;
      }
  
  /*prints memory address in hexadecimal, the instructions, and increments
 the memory address by 4*/
  for (i = 0; i < num_instrs; i++)
   {	
     printf("%04x: ", memory_count);
     print_instruction(program[i]);
     printf("\n");
     memory_count += 4;
   }

   return 1;
  }
                                                                                
/*This is a helper function to check all invalid instructions. This can be used
 by other functions to check for invalid instructions. It returns 0 if an 
instruction is invalid and 1 if all instructions are valid.*/

static int check_invalid(Wrd instruction)
{
  int opcode = 0;
  int sys_ext =0;
  int register_1 = 0;
  int register_2 = 0;
  int register_3 = 0;
  int memory_address = 0;
  /*sys_r1 is 1 if sys uses register 1 and is 0 if sys doesn't use register 1*/
  int sys_r1 = 1;
                  
  /*shifting bits to the right then masking them with &*/
  opcode = instruction >> SHIFT_OPCODE;
  sys_ext = MASK_SYS_EXT & (instruction >> SHIFT_SYS_EXT);
  memory_address = MASK_MEMORY_ADDRESS & instruction;
  register_1 = MASK_REGISTERS & (instruction >> SHIFT_REGISTER_1);
  register_2 = MASK_REGISTERS & ( instruction >> SHIFT_REGISTER_2);
  register_3 = MASK_REGISTERS & (instruction >> SHIFT_REGISTER_3);

  /*checks if sys will use register 1 o not*/
  if (opcode == 26 && sys_ext == 4)
    sys_r1 = 0;

  /*checks for opcodes above 26.*/
  if (opcode > 26)
   return 0;
  
  /*checks for incorrect register numbers, that is for numbers not in the range
    0-6. Also only checks for instructions that use the register.*/
  else if ((register_1 > 6 && sys_r1 == 1) || (register_2 > 6 && opcode < 23)
	   || (register_3 > 6 && (opcode < 15 && opcode != 5 && opcode != 6 
	   && opcode != 12)))
   
      return 0;

  /*checks for incorrect memory address for those instructions that use the 
memory address.*/
  else if ((opcode > 16 && opcode < 25 && opcode != 22 ) && 
	   (memory_address%4 != 0))
   return 0;
                                                                                
  /*checks if the first register modifies R6. Only checks those instructions
   that modify the first register.*/
  else if ((opcode < 16 ||  opcode > 21) && opcode != 24 && register_1 == 6)
   { 
     /*checks the sys extension if the instructions has the opcode sys to see
       if the first register is modified*/
     if (opcode == 26)
      {
	if (sys_ext == 0 || sys_ext == 2)
         return 0;
      }
     else 
      return 0;
   }
  
  /*checks for invalid extensions for sys*/
  else if (opcode == 26 && (sys_ext < 0 || sys_ext > 4))
	return 0;

  return 1;
}

/*This function returns the index of the first place in the array of 
instruction that the register number was set/modified. If the 
register number hasn't been set or if the insturctions, reg_nbr
, or the program array is invalid, it returns -1.*/
                
short where_set(const Wrd program[], unsigned short num_words, 
unsigned short reg_nbr)
{
  int no_position = -1;
  int opcode = 0;
  int i =0;
  int register_1 = 0;
  int sys_ext = 0;

  /*checking invalid program array or beyond total possible
   instructions.*/
  if (program == NULL || num_words > NUM_WORDS)
    return -1;

  /*checking for invalid register numbers*/
  if (reg_nbr < 0 || reg_nbr >= 6)
    return -1;

  for (i = 0; i < num_words; i++)
    {
      opcode = program[i] >> SHIFT_OPCODE;
      register_1 = MASK_REGISTERS & (program[i] >> SHIFT_REGISTER_1);
      if (register_1 == reg_nbr)
       { 
        /*checking if the opcodes modify the register or not*/
       /*The index should be retured only if the opcode modifies the register*/
                                                                                
	 /*checks the sys_ext if the opcode is sys to see if it modifies
	   the first register*/
	 if (opcode == 26)
	 {
	   sys_ext = MASK_SYS_EXT & (program[i] >> SHIFT_SYS_EXT);
	   if (sys_ext == 0 || sys_ext == 2)
	     return i;
	 }

	 /*checks other opcodes instead of sys if they modify 
         the first register*/
	 else if ((opcode < 16 || opcode > 21) && opcode != 24)
	   return i;
     }
  }
  /*If the register number hasn't been set, it has no posiiton in the array*/
 return no_position;

}

                                                                                
/*This function checks to see if the register being used has been given a value 
prior to using any information from it. It uses where_set function to see if 
the index where the register was set is smaller than the index where it is
 used.*/

unsigned short is_safe(const Wrd program[], unsigned short pgm_size, unsigned
 short *const bad_instr)
{
  int i = 0;
  /* safe is 1 if the program is safe and 0 if the program is unsafe.*/
  int safe = 1;
  int register_2 = 0;
  int register_3 = 0;
  int register_1 = 0;
  int opcode = 0;
  int sys_ext = 0;

  /*checking for invalid cases*/
  if (program == NULL || bad_instr == NULL || pgm_size > NUM_WORDS)
    return 0;

  for(i = 0; i < pgm_size; i++)
   {
     /*checks for invalid instructions*/
     if (check_invalid(program[i])==0)
      return 0;
      
     /*Bitshifting and Bit masking to isolate bits*/
     opcode = program[i] >> SHIFT_OPCODE;
     register_1 = MASK_REGISTERS & (program[i] >> SHIFT_REGISTER_1);
     register_2 = MASK_REGISTERS & (program[i] >> SHIFT_REGISTER_2);
     register_3 = MASK_REGISTERS & (program[i] >> SHIFT_REGISTER_3);
     sys_ext = MASK_SYS_EXT & (program[i] >> SHIFT_SYS_EXT);

     /*checking codes that use register1*/
     if ((opcode > 15 && opcode < 22) || opcode == 24 || (opcode == 26 && 
	 (sys_ext == 0 || sys_ext == 2)))
       {
	 /*If where_set function returns an index after the current one,
	   the program is unsafe as the register hasn't been set yet.*/
	 if (where_set(program, pgm_size, register_1) > i)
	   safe = 0;
       }
       
     /*checking instructions that use register 2*/
     if (opcode < 23)
       { /*checking if register 2 hasn't been set yet.*/
	 if (where_set(program, pgm_size, register_2) > i) 
	      safe = 0;
       }

     /*checking instructions that use register 3*/
    if (opcode < 15 && opcode != 5 && opcode !=6 && opcode != 12)
      {
	/*checking if register 3 hasn't been set yet.*/
	if (where_set(program, pgm_size, register_3) > i)
	safe = 0;
      }
     
     if (safe == 0)
      {
	/*modifies bad_instr to point to the index where
	  the program is unsafe*/
	*bad_instr = i;
	return 0;
     }
   }
  return safe;
}



     
