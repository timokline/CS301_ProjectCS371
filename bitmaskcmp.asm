section .text ; makes this executable
bits 64 ; allow 64-bit register names

global attack ; makes this visible to linker
attack:
	mov		rax, rcx
	and  	rax, rdx
	ret
