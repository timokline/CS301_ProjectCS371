;WINDOWS x64
section .text ; makes this executable
bits 64 ; allow 64-bit register names

global critCalc ; makes this visible to linker
critCalc:
	mov		rax, rcx
	and  	rax, rdx
	ret

	global typeCalc ; makes this visible to linker
typeCalc:
	mov		rax, rcx
	sub  	rax, rdx
	ret