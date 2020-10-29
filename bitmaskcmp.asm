section .text ; makes this executable
bits 64 ; allow 64-bit register names

global bar ; makes this visible to linker
bar:
	mov		rax, rcx
	xor  	rax, rdx
	ret
