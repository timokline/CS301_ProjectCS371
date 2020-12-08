;WINDOWS x64
section .text ; makes this executable
bits 64 ; allow 64-bit register names

global critCalc ; makes this visible to linker
critCalc:
	mov		rax, rcx				;store signature #1
	and  	rax, rdx				;bitmask w/ signature #2
	ret								:return resulting mask

global typeCalc ; makes this visible to linker
typeCalc:	
	mov		rax, rcx				;store attributeW
	and  	rax, rdx				;compare attribW w/ enemy.type
	cmp		rax, 0b0000
	jg		Effective				;if a type matches.....

	;Otherwise, check if an ineffective weapon is being used..
	shl		rdx, 1					;..which differs by a bitshift
	cmp		rdx, 0b1000
	jne		NotEffective			;if resulting bitshift is kept in the 3 bit-space...
	shr		rdx, 3					;otherwise, wrap bits in the 3-bit space

	NotEffective:					;...set (dis)advantage to -2
		   ;mov rsi, 1		;for print
		mov		rax, -2				;for attack
		mov		rdi, rcx			;store attributeW again
		and		rdi, rdx			;compare attribW w/ bitshifted enemy.type
		cmp		rdi, 0b0000			;check if a type matches
		jg		Exit				;ideally, jmp to Print

	NoEffect:						;otherwise, set no advantage
		mov		rax, rdi			;assuming resulting bitmask is 0..
		jmp		Exit				;return
	
	Effective:						;.....set advantage to +2
		   ;mov rsi, 0		;for print
		mov		rax, 2				;for attack,
	
		;Print:						;Currently, works great on NetRun
			;push		rax
			;mov 		rdi,[Feedback+rsi*8]

			;extern 	puts
			;call		puts

			;pop		rax
		
	Exit:
		ret


											;array of responses
		;section .data
		;response1: db `SUPER EFFECTIVE\n`,0
		;response2: db `Not Very Effective.\n`,0

		;Feedback:
			;dq response1					;arr[0]
			;dq response2					;arr[1]