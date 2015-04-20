#include "asm.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"

# By convention, the _start symbol specifies the ELF entry point.
# Since we haven't set up virtual memory yet, our entry point is
# the physical address of 'entry'.
.globl _start
_start = V2P_WO(entry)

# Entering xv6 on boot processor, with paging off.
.globl entry
entry:
  movl %cr4, %eax
  orl $(CR4_PSE), %eax
  movl %eax, %cr4

  movl $(V2P_WO(entrypgdir)), %eax
  movl %eax, %cr3

  movl %cr0, %eax
  orl $(CR0_PG|CR0_WP), %eax
  movl %eax, %cr0

  movl $(stack + KSTACKSIZE), %esp

  mov $main, %eax
  jmp *%eax

.comm stack, KSTACKSIZE
