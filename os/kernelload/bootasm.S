#include "asm.h"
#include "memlayout.h"
#include "mmu.h"

.code16            # cpu in real mode
.global start
start:
  cli

  xor %ax, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %ss
  
#mov $output1, %ax
#mov %ax, %bp      # address of string
#mov $9, %cx       # length of string
#mov $0x1301, %ax  # ah=0x13 al=0x01
#mov $0x000c, %bx  # bh=0x0 bl=0x0c
#mov $12, %dh      # row
#mov $0, %dl       # column

#int $0x10

seta20.1:
  inb     $0x64, %al
  testb   $0x2, %al
  jnz     seta20.1

  movb    $0xd1, %al
  outb    %al, $0x64

seta20.2:
  inb     $0x64, %al
  testb   $0x2, %al
  jnz     seta20.2

  movb    $0xdf, %al
  outb    %al, $0x60

  lgdt gdtdesc
  movl %cr0, %eax
  orl  $CR0_PE, %eax
  movl %eax, %cr0

  ljmp    $(SEG_KCODE<<3), $start32

.code32
start32:
  movw    $(SEG_KDATA<<3), %ax    # Our data segment selector
  movw    %ax, %ds                # -> DS: Data Segment
  movw    %ax, %es                # -> ES: Extra Segment
  movw    %ax, %ss                # -> SS: Stack Segment
  movw    $0, %ax                 # Zero segments not ready for use
  movw    %ax, %fs                # -> FS

  movw $(SEG_KVIDEO<<3), %ax
  movw %ax, %gs

  mov     $((80*15+0)*2), %edi
  movb    $0xc, %ah
  mov     $14, %ecx
  mov     $0, %edx

echo:
  movb    output2(, %edx, 0x1), %al   #base(base, index, step) 
  movb    $0xc, %ah
  movw    %ax, %gs:(%edi)
  inc     %edx
  inc     %edi
  inc     %edi
#  loop echo

  # Set up the stack pointer and call into C.
  movl    $start, %esp
  call    bootmain

#spin:
#  jmp spin

output2:
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
