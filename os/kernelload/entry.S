#include "asm.h"
#include "memlayout.h"
#include "mmu.h"

# By convention, the _start symbol specifies the ELF entry point.
# Since we haven't set up virtual memory yet, our entry point is
# the physical address of 'entry'.
.globl _start
_start = V2P_WO(entry)

# Entering xv6 on boot processor, with paging off.
.globl entry
entry:
#mov     $((80*18+0)*2), %edi
# movb    $0xc, %ah
# mov     $14, %ecx
# mov     $0, %edx
#echo:
# movb    msg(, %edx, 0x1), %al   #base(base, index, step)
# movb    $0xc, %ah
# movw    %ax, %gs:(%edi)
# inc     %edx
# inc     %edi
# inc     %edi
# loop echo
cur: 
  jmp cur

msg:
  .ascii "Booting Kernel"  # length is 14


