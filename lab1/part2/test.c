#include <stdio.h>
#include "types.h"

/* Your task: parse the unsigned int number into an Instruction
 * extract corresponding bits to fill the rtype struct fields
 */
Instruction parse_rtype(unsigned int number) {
  Instruction instr;
  instr.rtype.opcode = number & 0x7F; //7 :(num AND ...00000001111111) make all zero except the last 7 bits
  instr.rtype.rd = (number >> 7) & 0x1F; //5 right shift num 7 bits, then AND (..00011111)
  instr.rtype.funct3 = (number >> 12) & 0x7; //3
  instr.rtype.rs1 = (number >> 15) & 0x1F; //5
  instr.rtype.rs2 = (number >> 20) & 0x1F; //5
  instr.rtype.funct7 = (number >> 25) & 0x7F; //7
  return instr;
}

/* Your task: parse the unsigned int number into an Instruction
 * extract corresponding bits to fill the itype struct fields
 */
Instruction parse_itype(unsigned int number) {
  Instruction instr;
  instr.rtype.opcode = number & 0x7F; //7 (...0001111111)
  instr.itype.rd = (number >> 7) & 0x1F; //5 
  instr.itype.funct3 = (number >> 12) & 0x7; //3
  instr.itype.rs1 = (number >> 15) & 0x1F; //5
  instr.itype.imm = (number >> 20) & 0xFFF; //12
  return instr;
}

void print_rtype(Instruction instr) {
  printf("%d, ", instr.rtype.opcode);
  printf("%d, ", instr.rtype.rd);
  printf("%d, ", instr.rtype.funct3);
  printf("%d, ", instr.rtype.rs1);
  printf("%d, ", instr.rtype.rs2);
  printf("%d\n", instr.rtype.funct7);
}

void print_itype(Instruction instr) {
  printf("%d, ", instr.itype.opcode);
  printf("%d, ", instr.itype.rd);
  printf("%d, ", instr.itype.funct3);
  printf("%d, ", instr.itype.rs1);
  printf("%d\n", instr.itype.imm);
}

int main() {
  unsigned int numbers[4] = {0x015a04b3,0x009a84b3,0x00148493,0x00440413};
  Instruction instrs[4];

  //parse the above four numbers into corresponding instructions
  instrs[0] = parse_rtype(numbers[0]);
  print_rtype(instrs[0]);  
    
  instrs[1] = parse_rtype(numbers[1]);
  print_rtype(instrs[1]);  
    
  instrs[2] = parse_itype(numbers[2]);
  print_itype(instrs[2]);  
    
  instrs[3] = parse_itype(numbers[3]);
  print_itype(instrs[3]);  
    
  return 0;
}
