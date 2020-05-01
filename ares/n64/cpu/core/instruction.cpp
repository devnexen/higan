auto CPU::exception(uint type) -> void {
}

auto CPU::instruction() -> void {
  pipeline.instruction = bus.readWord(PC);

  if(IP) {
    PC = IP();
    IP = nothing;
  } else {
    PC += 4;
  }

#if 1
static uint counter = 0;
if(++counter < 1000) {
  print(hex(PC, 8L), "  ", hex(pipeline.instruction, 8L), "  ", disassembleInstruction(), "\n");
}
#endif

  switch(pipeline.instruction >> 26) {
  case 0x00: return instructionSPECIAL();
  case 0x01: return instructionREGIMM();
  case 0x02: return instructionJ();
  case 0x03: return instructionJAL();
  case 0x04: return instructionBEQ();
  case 0x05: return instructionBNE();
  case 0x06: return instructionBLEZ();
  case 0x07: return instructionBGTZ();
  case 0x08: return instructionADDI();
  case 0x09: return instructionADDIU();
  case 0x0a: return instructionSLTI();
  case 0x0b: return instructionSLTIU();
  case 0x0c: return instructionANDI();
  case 0x0d: return instructionORI();
  case 0x0e: return instructionXORI();
  case 0x0f: return instructionLUI();
  case 0x10: return instructionCOP0();
  case 0x11: return instructionCOP1();
  case 0x12: return instructionCOP2();
  case 0x13: return instructionCOP3();
  case 0x14: return instructionBEQL();
  case 0x15: return instructionBNEL();
  case 0x16: return instructionBLEZL();
  case 0x17: return instructionBGTZL();
  case 0x18: return instructionDADDI();
  case 0x19: return instructionDADDIU();
  case 0x1a: return instructionLDL();
  case 0x1b: return instructionLDR();
  case 0x1c: break;
  case 0x1d: break;
  case 0x1e: break;
  case 0x1f: break;
  case 0x20: return instructionLB();
  case 0x21: return instructionLH();
  case 0x22: return instructionLWL();
  case 0x23: return instructionLW();
  case 0x24: return instructionLBU();
  case 0x25: return instructionLHU();
  case 0x26: return instructionLWR();
  case 0x27: return instructionLWU();
  case 0x28: return instructionSB();
  case 0x29: return instructionSH();
  case 0x2a: return instructionSWL();
  case 0x2b: return instructionSW();
  case 0x2c: return instructionSDL();
  case 0x2d: return instructionSDR();
  case 0x2e: return instructionSWR();
  case 0x2f: return instructionCACHE();
  case 0x30: return instructionLL();
  case 0x31: return instructionLWC1();
  case 0x32: return instructionLWC2();
  case 0x33: return instructionLWC3();
  case 0x34: return instructionLLD();
  case 0x35: return instructionLDC1();
  case 0x36: return instructionLDC2();
  case 0x37: return instructionLD();
  case 0x38: return instructionSC();
  case 0x39: return instructionSWC1();
  case 0x3a: return instructionSWC2();
  case 0x3b: return instructionSWC3();
  case 0x3c: return instructionSCD();
  case 0x3d: return instructionSDC1();
  case 0x3e: return instructionSDC2();
  case 0x3f: return instructionSD();
  }
  exception(InvalidInstruction);
}

auto CPU::instructionSPECIAL() -> void {
  switch(pipeline.instruction & 0x3f) {
  case 0x00: return instructionSLL();
  case 0x01: break;
  case 0x02: return instructionSRL();
  case 0x03: return instructionSRA();
  case 0x04: return instructionSLLV();
  case 0x05: break;
  case 0x06: return instructionSRLV();
  case 0x07: return instructionSRAV();
  case 0x08: return instructionJR();
  case 0x09: return instructionJALR();
  case 0x0a: break;
  case 0x0b: break;
  case 0x0c: return instructionSYSCALL();
  case 0x0d: return instructionBREAK();
  case 0x0e: break;
  case 0x0f: return instructionSYNC();
  case 0x10: return instructionMFHI();
  case 0x11: return instructionMTHI();
  case 0x12: return instructionMFLO();
  case 0x13: return instructionMTLO();
  case 0x14: return instructionDSLLV();
  case 0x15: break;
  case 0x16: return instructionDSRLV();
  case 0x17: return instructionDSRAV();
  case 0x18: return instructionMULT();
  case 0x19: return instructionMULTU();
  case 0x1a: return instructionDIV();
  case 0x1b: return instructionDIVU();
  case 0x1c: return instructionDMULT();
  case 0x1d: return instructionDMULTU();
  case 0x1e: return instructionDDIV();
  case 0x1f: return instructionDDIVU();
  case 0x20: return instructionADD();
  case 0x21: return instructionADDU();
  case 0x22: return instructionSUB();
  case 0x23: return instructionSUBU();
  case 0x24: return instructionAND();
  case 0x25: return instructionOR();
  case 0x26: return instructionXOR();
  case 0x27: return instructionNOR();
  case 0x28: break;
  case 0x29: break;
  case 0x2a: return instructionSLT();
  case 0x2b: return instructionSLTU();
  case 0x2c: return instructionDADD();
  case 0x2d: return instructionDADDU();
  case 0x2e: return instructionDSUB();
  case 0x2f: return instructionDSUBU();
  case 0x30: return instructionTGE();
  case 0x31: return instructionTGEU();
  case 0x32: return instructionTLT();
  case 0x33: return instructionTLTU();
  case 0x34: return instructionTEQ();
  case 0x35: break;
  case 0x36: return instructionTNE();
  case 0x37: break;
  case 0x38: return instructionDSLL();
  case 0x39: break;
  case 0x3a: return instructionDSRL();
  case 0x3b: return instructionDSRA();
  case 0x3c: return instructionDSLL32();
  case 0x3d: break;
  case 0x3e: return instructionDSRL32();
  case 0x3f: return instructionDSRA32();
  }
  exception(InvalidInstruction);
}

auto CPU::instructionREGIMM() -> void {
  switch(pipeline.instruction >> 16 & 0x1f) {
  case 0x00: return instructionBLTZ();
  case 0x01: return instructionBGEZ();
  case 0x02: return instructionBLTZL();
  case 0x03: return instructionBGEZL();
  case 0x04: break;
  case 0x05: break;
  case 0x06: break;
  case 0x07: break;
  case 0x08: return instructionTGEI();
  case 0x09: return instructionTGEIU();
  case 0x0a: return instructionTLTI();
  case 0x0b: return instructionTLTIU();
  case 0x0c: return instructionTEQI();
  case 0x0d: break;
  case 0x0e: return instructionTNEI();
  case 0x0f: break;
  case 0x10: return instructionBLTZAL();
  case 0x11: return instructionBGEZAL();
  case 0x12: return instructionBLTZALL();
  case 0x13: return instructionBGEZALL();
  case 0x14: break;
  case 0x15: break;
  case 0x16: break;
  case 0x17: break;
  case 0x18: break;
  case 0x19: break;
  case 0x1a: break;
  case 0x1b: break;
  case 0x1c: break;
  case 0x1d: break;
  case 0x1e: break;
  case 0x1f: break;
  }
  exception(InvalidInstruction);
}

auto CPU::instructionCOP0() -> void {
  if(!STATUS_COP0) return exception(CoprocessorUnusable);
  switch(pipeline.instruction >> 21 & 31) {
  case 0x00: return instructionMFC0();
  case 0x01: return instructionDMFC0();
  case 0x02: return instructionCFC0();
  case 0x04: return instructionMTC0();
  case 0x05: return instructionDMTC0();
  case 0x06: return instructionCTC0();
  case 0x08: switch(pipeline.instruction >> 16 & 3) {
    case 0x00: return instructionBC0F();
    case 0x01: return instructionBC0T();
    case 0x02: return instructionBC0FL();
    case 0x03: return instructionBC0TL();
    }
  }
  if(!(pipeline.instruction >> 25 & 1)) return exception(InvalidInstruction);
  switch(pipeline.instruction & 0x3f) {
  case 0x01: return instructionTLBR();
  case 0x02: return instructionTLBWI();
  case 0x06: return instructionTLBWR();
  case 0x08: return instructionTLBP();
  }
  exception(InvalidInstruction);
}

auto CPU::instructionCOP1() -> void {
  if(!STATUS_COP1) return exception(CoprocessorUnusable);
  switch(pipeline.instruction >> 21 & 31) {
  case 0x00: return instructionMFC1();
  case 0x01: return instructionDMFC1();
  case 0x02: return instructionCFC1();
  case 0x04: return instructionMTC1();
  case 0x05: return instructionDMTC1();
  case 0x06: return instructionCTC1();
  case 0x08: switch(pipeline.instruction >> 16 & 3) {
    case 0x00: return instructionBC1F();
    case 0x01: return instructionBC1T();
    case 0x02: return instructionBC1FL();
    case 0x03: return instructionBC1TL();
    }
  }
  switch(pipeline.instruction & 0x3f) {
  case 0x00: return instructionFADD();
  case 0x01: return instructionFSUB();
  case 0x02: return instructionFMUL();
  case 0x03: return instructionFDIV();
  case 0x04: return instructionFSQRT();
  case 0x05: return instructionFABS();
  case 0x06: return instructionFMOV();
  case 0x07: return instructionFNEG();
  case 0x08: return instructionFROUNDL();
  case 0x09: return instructionFTRUNCL();
  case 0x0a: return instructionFCEILL();
  case 0x0b: return instructionFFLOORL();
  case 0x0c: return instructionFROUNDW();
  case 0x0d: return instructionFTRUNCW();
  case 0x0e: return instructionFCEILW();
  case 0x0f: return instructionFFLOORW();
  case 0x20: return instructionFCVTS();
  case 0x21: return instructionFCVTD();
  case 0x24: return instructionFCVTW();
  case 0x25: return instructionFCVTL();
  case 0x30: case 0x38: return instructionFCF();
  case 0x31: case 0x39: return instructionFCUN();
  case 0x32: case 0x3a: return instructionFCEQ();
  case 0x33: case 0x3b: return instructionFCUEQ();
  case 0x34: case 0x3c: return instructionFCOLT();
  case 0x35: case 0x3d: return instructionFCULT();
  case 0x36: case 0x3e: return instructionFCOLE();
  case 0x37: case 0x3f: return instructionFCULE();
  }
  exception(InvalidInstruction);
}

auto CPU::instructionCOP2() -> void {
  if(!STATUS_COP2) return exception(CoprocessorUnusable);
  exception(InvalidInstruction);
}

auto CPU::instructionCOP3() -> void {
  if(!STATUS_COP3) return exception(CoprocessorUnusable);
  exception(InvalidInstruction);
}