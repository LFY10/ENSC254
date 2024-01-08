#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* Unpacks the 32-bit machine code instruction given into the correct
 * type within the instruction struct */
Instruction parse_instruction(uint32_t instruction_bits) {
  /* YOUR CODE HERE */
  Instruction instruction;
  // add x9, x20, x21   hex: 01 5A 04 B3, binary = 0000 0001 0101 1010 0000 0100 1011 0011
  // Opcode: 0110011 (0x33) Get the Opcode by &ing 0x1111111, bottom 7 bits
  instruction.opcode = instruction_bits & ((1U << 7) - 1);

  // Shift right to move to pointer to interpret next fields in instruction.
  instruction_bits >>= 7;

  switch (instruction.opcode) {
  // R-Type
  case 0x33:
    // instruction: 0000 0001 0101 1010 0000 0100 1, destination : 01001
    instruction.rtype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.rtype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.rtype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, src2: 10101
    instruction.rtype.rs2 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // funct7: 0000 000
    instruction.rtype.funct7 = instruction_bits & ((1U << 7) - 1);
    break;
  // cases for other types of instructions
  /* YOUR CODE HERE */
  
  // I-Type
  case 0X03:
    // instruction: 0000 0001 0101 1010 0000 0100 1, destination : 01001
    instruction.itype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.itype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.itype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, imm: 0000 0001 0101
    instruction.itype.imm = instruction_bits & ((1U << 12) - 1);
    break;
  // I-Type
  case 0x13:
     // instruction: 0000 0001 0101 1010 0000 0100 1, destination : 01001
    instruction.itype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.itype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.itype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, imm: 0000 0001 0101
    instruction.itype.imm = instruction_bits & ((1U << 12) - 1);
    break;
  // I-Type
  case 0x73:
     // instruction: 0000 0001 0101 1010 0000 0100 1, destination : 01001
    instruction.itype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.itype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.itype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, imm: 0000 0001 0101
    instruction.itype.imm = instruction_bits & ((1U << 12) - 1);
    break;

  // S-Type
  case 0x23:
    // instruction: 0000 0001 0101 1010 0000 0100 1, imm5 : 01001
    instruction.stype.imm5 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.stype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.stype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, src2: 10101
    instruction.stype.rs2 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // imm7: 0000 000
    instruction.stype.imm7 = instruction_bits & ((1U << 7) - 1);
    break;

  //Sb-Type
  case 0x63:
    // instruction: 0000 0001 0101 1010 0000 0100 1, imm5 : 01001
    instruction.sbtype.imm5 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, func3 : 000
    instruction.sbtype.funct3 = instruction_bits & ((1U << 3) - 1);
    instruction_bits >>= 3;

    // instruction: 0000 0001 0101 1010 0, src1: 10100
    instruction.sbtype.rs1 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101, src2: 10101
    instruction.sbtype.rs2 = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // imm7: 0000 000
    instruction.sbtype.imm7 = instruction_bits & ((1U << 7) - 1);
    break;

  //U-Type
  case 0x37:
  // instruction: 0000 0001 0101 1010 0000 0100 1, rd : 01001
    instruction.utype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    // instruction: 0000 0001 0101 1010 0000, imm : 0000 0001 0101 1010 0000
    instruction.utype.imm = instruction_bits & ((1U << 20) - 1);
    break;

  //UJ-Type
  case 0x6f:
  // instruction: 0000 0001 0101 1010 0000 0100 1, rd : 01001
    instruction.ujtype.rd = instruction_bits & ((1U << 5) - 1);
    instruction_bits >>= 5;

    /*
    // instruction: 0000 0001 0101 1010 0000 0100 1, imm[20] : 0
    // instruction: 0000 0001 0101 1010 0000 0100 1, imm[10:1] : 0101101101
    // instruction: 0000 0001 0101 1010 0000 0100 1, imm[11] : 1
    // instruction: 0000 0001 0101 1010 0000 0100 1, imm[19:12] : 00000000
    instruction.ujtype.imm = ((instruction_bits >> 20) & 0xFFF) | 
                              (((instruction_bits >> 9) & 1) << 11) | 
                              (((instruction_bits >> 8) & 0x3F) << 1) | (((instruction_bits >> 18) & 1) << 12);*/
    // instruction: 0000 0001 0101 1010 0000, imm : 0000 0001 0101 1010 0000
    instruction.utype.imm = instruction_bits & ((1U << 20) - 1);
    //instruction.utype.imm = instruction_bits & (((1U << 9)|(1U << 1)|(1U<<7)|(1U<<1))-1);
    break;
  #ifndef TESTING
  default:
    exit(EXIT_FAILURE);
  #endif
  }
  return instruction;
}

/************************Helper functions************************/
/* Here, you will need to implement a few common helper functions, 
 * which you will call in other functions when parsing, printing, 
 * or executing the instructions. */

/* Sign extends the given field to a 32-bit integer where field is
 * interpreted an n-bit integer. */
int sign_extend_number(unsigned int field, unsigned int n) {
  /* YOUR CODE HERE */
  // Check if the field is negative
  // eg: field = 1101, 1<< (n-1) = 001000. Then add both, 1 and 1 will give 1, so != 0
  if ((field & (1 << (n - 1))) != 0) {
    // Field is negative, so sign extend by setting all the higher bits to 1
    unsigned int extension = (0xFFFFFFFF << n) | field;
    return extension;
  } else {
    // Field is positive, no need sign extension
    return field;
  }
}


/* Return the number of bytes (from the current PC) to the branch label using
 * the given branch instruction */
int get_branch_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  int imm5 = instruction.sbtype.imm5;
  int imm7 = instruction.sbtype.imm7;
  int imm = imm7 << 5| imm5;
  int var1 = (imm & (((1U << 4) - 1) << 1)) >> 1; //4:1
  int var2 = (imm & (((1U << 1) - 1))) << 10; //11
  int var3 = (imm & (((1U << 6) - 1) << 5)) >> 1; //10:5
  int var4 = (imm & (((1U << 1) - 1) << 11));  //12
  //int var1 = (imm5&((1U << 1)-1))<<12; //11
  //int var2 = (imm5&((1U <<4)-1)<<1);//4:1
  //int var3 = (imm7&((1U << 6)-1));//10:5
  //int var4 = (imm7&((1U << 1)-1)<<11)<<1;//12
  int final = var1 | var2 | var3| var4;
  return sign_extend_number(final << 1,12);
}

 

/* Returns the number of bytes (from the current PC) to the jump label using the
 * given jump instruction */
int get_jump_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  /*
  int imm = instruction.ujtype.imm;
  int var1 = (imm & (((1U << 10)-1) << 9))>>8 ;//1:10
  int var2 = (imm & (((1U << 1)-1) << 9))<<3;//11
  int var3 = (imm & (((1U << 8) - 1)<<1))<<12;//12:19
  int var4 = (imm & (((1U << 1)-1) << 19))<<1;//20
  int final = var1 | var2 | var3| var4;
  return sign_extend_number(final,20);*/

  int imm = instruction.ujtype.imm;
  int var1 = (imm & (((1U << 10)-1) << 9))>>9 ;//1:10
  int var2 = (imm & (((1U << 1)-1) << 8))<<2;//11
  int var3 = (imm & (((1U << 8) - 1)))<<11;//12:19
  int var4 = (imm & (((1U << 1)-1) << 19));//20
  int final = var1 | var2 | var3| var4;
  return sign_extend_number(final << 1,20);
}

/* Returns the number of bytes (from the current PC) to the base address using the
 * given store instruction */
int get_store_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  int a = instruction.stype.imm5;
  int b = instruction.stype.imm7;
  return sign_extend_number(a|b<<5,12);
}
/************************Helper functions************************/

void handle_invalid_instruction(Instruction instruction) {
  printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}

void handle_invalid_read(Address address) {
  printf("Bad Read. Address: 0x%08x\n", address);
  exit(-1);
}

void handle_invalid_write(Address address) {
  printf("Bad Write. Address: 0x%08x\n", address);
  exit(-1);
}
unsigned int reverse_bits(unsigned int num) {
    unsigned int NO_OF_BITS = sizeof(num) * 8; // Number of bits in an integer
    
    // Initialize result to 0
    unsigned int reverseNum = 0;
    
    // Iterate through each bit
    for (int i = 0; i < NO_OF_BITS; i++) {
        // Left shift the result
        reverseNum <<= 1;
        
        // Check if the current bit is set in the input number
        if (num & 1)
            reverseNum |= 1;
        
        // Right shift the input number to process the next bit
        num >>= 1;
    }
    
    return reverseNum;
} 

