.code16
.global start
start:
  cli

  xor %ax, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %ss
  call display

cur:
  jmp cur 

display:
	mov $output, %ax
	mov %ax, %bp      # address of string
	mov $11, %cx      # length of string
	mov $0x1301, %ax  # ah=0x13 al=0x01
	mov $0x000c, %bx  # bh=0x0 bl=0x0c
	mov $12, %dh      # row
	mov $2, %dl       # column

	int $0x10
	ret

output:
	.ascii "Hello World"
