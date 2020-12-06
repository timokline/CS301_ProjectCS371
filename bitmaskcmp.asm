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
	mov		rax, rcx	;store attributeW
	and  	rax, rdx	;compare attribW w/ enemy.type
	cmp		rax, 0x0000
	jg		Effective

	;Check if an ineffective weapon is being used
	shl		dx, 4
	cmp		dx, 0x1000
	jne		NotEffective
	shr		dx, 16		;wrap bits in the 12-bit 

	NotEffective:
		mov		rsi, 1		;for print
		mov		rax, -2		;for attack
		mov		rdi, rcx
		and		rdi, rdx
		cmp		rdi, 0x0000
		jg		Exit
		
		mov		rax, rdi
		jmp		Exit
	
	Effective:
		mov		rsi, 0		;for print
		mov		rax, 2		;for attack
	
	;Print:
		;push	rax
		;mov 	rdi,[Feedback+rsi*8]

		;extern 	puts
		;call 	puts

		;pop		rax
		
	Exit:
		ret


		;section .data
		;response1: db `SUPER EFFECTIVE\n`,0
		;response2: db `Not Very Effective.\n`,0

		;Feedback:
			;dq response1
			;dq response2