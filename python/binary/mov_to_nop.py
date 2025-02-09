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

    text_data = bytearray(text_section.data())
    text_addr = text_section['sh_addr']
    text_offset = text_section['sh_offset']

    for instr in cs.disasm(text_data, text_addr):
        if instr.mnemonic.startswith("mov"):
            print(f"0x{instr.address}:\t{instr.mnemonic}\t{instr.op_str}")
            instr_size = len(instr.bytes) 
            nop_bytes = b"\x90" * instr_size
            offset = instr.address - text_addr
            text_data[offset:offset+instr_size] = nop_bytes

    with open(filename, "rb") as f1:
        elf_data = bytearray(f1.read())

    elf_data[text_offset:text_offset+len(text_data)] = text_data

    with open(filename + ".patched", "wb") as fn:
        fn.write(elf_data)

    print(f"Generated {filename}.patched")
