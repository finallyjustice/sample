#!/usr/bin/env python3

from capstone import *
from elftools.elf.elffile import ELFFile
import sys

filename = "test"
with open(filename, "rb") as f:
    elf = ELFFile(f)

    arch = elf.get_machine_arch()
    if arch != "x64":
        print("Unexpected arch.")
        sys.exit()

    text_section = elf.get_section_by_name(".text")
    if not text_section:
        print("Unexpected section.")
        sys.exit()

    cs = Cs(CS_ARCH_X86, CS_MODE_64)

    text_data = text_section.data()
    text_addr = text_section['sh_addr']

    for instr in cs.disasm(text_data, text_addr):
        print(f"0x{instr.address}:\t{instr.mnemonic}\t{instr.op_str}")
