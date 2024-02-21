section .data
section .text
    global xmmBlend
xmmBlend:
    push ebp
    mov ebp,esp

    xor ebx,ebx     ;Limpiando registros
    xor eax,eax
    xor esi,esi
    xor ecx,ecx     ;contador

    mov eax,[ebp + 8]  ;imagen1 paramentroColor
    mov ebx,[ebp + 12]  ;imagen2 parametroColor
    mov edx,[ebp + 16]  ;cantCaracteres parametro
    pxor xmm4,xmm4  ;bitwise logical exclusive or. limpia el xmm4
    
ciclo:
    ;Los registros sse son de 128bits
    ;Los registro normales (ecx) son de 32bits
    ;32*4 = 128bits
    movups xmm1,[eax + ecx*4]  ;imagen1 Canal Color
    movups xmm2,[ebx + ecx*4]  ;imagen2 Canal Color
    punpcklbw xmm1,xmm4 
    punpcklbw xmm2,xmm4 ; desempaqueta

    pmullw xmm1,xmm2    ; multiply packed signed word integers and store low result

    psrlw xmm1,8 ;Shift words in xmm0 right by amount specified while shifting in 0s
    
    packuswb xmm1,xmm1 ; empaqueta

    movd [eax + ecx*4],xmm1 ;guarda resultado en parametro de la imagen1
    inc ecx
    cmp ecx,edx
    jnz ciclo

fin_ciclo:
    mov ebp,esp ;Reset Stack  (leave)
    pop ebp
    ret
    
