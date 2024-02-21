section .data
section .text
    global multiplyBlend ;must be declared for linker (ld)
multiplyBlend:
    push ebp ;enter 0,0
	mov ebp,esp
	mov eax,[EBP+8] ;valor color1
	mov	edx, [EBP+12];valor color2

	mul edx 	;EAX*EDX en EDX:EAX
	mov esi,255
	div esi		;Divides EDX:EAX by ESI ;cociente en EAX
	
	mov ebp,esp
    	pop ebp
   	ret
