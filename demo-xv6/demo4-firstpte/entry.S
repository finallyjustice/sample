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
  mov     $((80*18+0)*2), %edi     # offset on screen(15-row, 0-column)
  mov     $14, %ecx                # length of string
  mov     $0, %edx                 # index
echo:
  movb    msgp(, %edx, 0x1), %al   # base(base, index, step)
  movb    $0xc, %ah                # background and front color
  movw    %ax, %gs:(%edi)          # copy char to video buffer
  inc     %edx
  inc     %edi
  inc     %edi
  loop echo

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

#spin: 
#  jmp spin

msgp = V2P_WO(msgv)
msgv:
  .ascii "Booting Kernel"  # length is 14

.comm stack, KSTACKSIZE
