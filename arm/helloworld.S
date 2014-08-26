# arm-none-eabi-as helloworld.S -o helloworld.o 
# arm-none-eabi-ld helloworld.o -o helloworld
# qemu-arm helloworld 

.data
	msg: .asciz "hello world\n"

.text
	.align 2
	.global _start

_start:
	ldr r1, =msg
	mov r0, #1
	mov r2, #12
	swi #0x900004
	mov r0, #0
	swi #0x900001
	.align 2
