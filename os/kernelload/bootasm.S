#include "asm.h"
#include "memlayout.h"
#include "mmu.h"

# Start the CPU: switch to 32-bit protected mode, jump into C.
# The BIOS loads this code from the first sector of the hard disk into
# memory at physical address 0x7c00 and starts executing in real mode
# with %cs=0 %ip=7c00.

.code16            # cpu in real mode
.global start
start:
  cli              # BIOS enabled interrupts; disable

  # Zero data segment registers DS, ES, and SS.
  xor %ax, %ax     # Set %ax to zero
  mov %ax, %ds     # -> Data Segment
  mov %ax, %es     # -> Extra Segment
  mov %ax, %ss     # -> Stack Segment

  # Physical address line A20 is tied to zero so that the first PCs 
  # with 2 MB would run software that assumed 1 MB.  Undo that.
seta20.1:
  inb     $0x64, %al   # Wait for not busy
  testb   $0x2, %al
  jnz     seta20.1

  movb    $0xd1, %al   # 0xd1 -> port 0x64
  outb    %al, $0x64

seta20.2:
  inb     $0x64, %al   # Wait for not busy
  testb   $0x2, %al
  jnz     seta20.2

  movb    $0xdf, %al   # 0xdf -> port 0x60
  outb    %al, $0x60

  # Switch from real to protected mode.  Use a bootstrap GDT that makes
  # virtual addresses map directly to physical addresses so that the
  # effective memory map doesn't change during the transition.
  lgdt gdtdesc
  movl %cr0, %eax
  orl  $CR0_PE, %eax
  movl %eax, %cr0

  # Complete transition to 32-bit protected mode by using long jmp
  # to reload %cs and %eip.  The segment descriptors are set up with no
  # translation, so that the mapping is still the identity mapping.
  ljmp    $(SEG_KCODE<<3), $start32

.code32  # Tell assembler to generate 32-bit code now (Protected Mode).
start32:
  # Set up the protected-mode data segment registers
  movw    $(SEG_KDATA<<3), %ax    # Our data segment selector
  movw    %ax, %ds                # -> DS: Data Segment
  movw    %ax, %es                # -> ES: Extra Segment
  movw    %ax, %ss                # -> SS: Stack Segment
  movw    $0, %ax                 # Zero segments not ready for use
  movw    %ax, %fs                # -> FS

  movw $(SEG_KVIDEO<<3), %ax      # Our Video segment selector
  movw %ax, %gs                   # -> GS

  mov     $((80*15+0)*2), %edi    # offset on screen(15-row, 0-column)
  mov     $14, %ecx               # length of string
  mov     $0, %edx                # index

echo:
  movb    output(, %edx, 0x1), %al   # base(base, index, step) 
  movb    $0xc, %ah                  # background and front color
  movw    %ax, %gs:(%edi)            # copy char to video buffer
  inc     %edx
  inc     %edi
  inc     %edi
  loop echo

  # Set up the stack pointer and call into C.
  movl    $start, %esp
  call    bootmain     # bootmain is in bootmain.c 

output:
  .ascii "Protected Mode"  # length is 14

.p2align 2 
gdt:
  SEG_NULLASM                            # null seg
  SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)  # code seg
  SEG_ASM(STA_W, 0x0, 0xffffffff)        # data seg
  SEG_ASM(STA_W|STA_R, 0xb8000, 0xfffff) # video seg	

gdtdesc:                                 # param for lgdt ins
  .word (gdtdesc - gdt - 1)	             # max index (not size) of gdt table
  .long gdt								 # base addr of gdt table
