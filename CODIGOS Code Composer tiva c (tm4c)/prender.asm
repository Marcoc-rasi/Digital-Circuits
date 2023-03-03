   .global main
	 .data
         .text



main


; habilitar el PORTM Y EL PORTK . Donde? pues en el bit 11  Y 9 RESPECTIVAMENTE , del RCGCGPIO
;rgcgcpio 0x400f.e608
	mov  r0,#0xe608;PARTE INFERIOR DE LA DIRECCION
	movt r0,#0x400f;PARTE SUPERIOR DE LA DIRECCION
    mov  r1,#0xa00;ESTE ES 11 0000 1010 0000 0000 DONDE ESTA M Y K
    str  r1,[r0]
;COMPRUEBA LA HABILITACION DE PORTM
;PRGPIO BASE 0x400F.E000
;OFFSET 0XA08
       mov  r0,#0xea08
       movt r0,#0x400f
eapk1   ldr  r1,[r0]
       ands r1,#0x800
;  ???? ???? ???? ????
;& 0000 1000 0000 0000
;----------------------
;  0000 1000 0000 0000
;   status register   N V Z C

;beq equal-zero  bz
;bnq not equal-not bnz
       beq eapk1
;COMPRUEBA LA HABILITACION DE PORTK
;PRGPIO BASE 0x400F.E000
;OFFSET 0XA08
       mov  r0,#0xea08
       movt r0,#0x400f
eapk2   ldr  r1,[r0]
       ands r1,#0x200
;  ???? ???? ???? ????
;& 0000 0010 0000 0000
;----------------------
;  0000 0010 0000 0000
;   status register   N V Z C

;beq equal-zero  bz
;bnq not equal-not bnz
       beq eapk2
;apagar todos los bits de K
;PORTK DATA offset 0x3fc

 	    mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x00 ;1111 1111
        str  r1,[r0]

;apagar todos los bits de M
;PORTK DATA offset 0x3fc

 	    mov  r0,#0x33fc
	    movt r0,#0x4006
        mov  r1,#0x00 ;1111 1111
        str  r1,[r0]

;direccion base de K 0X4006.1000
;direccion base de m 0x4006.3000

;configurar PORTK como salida en todos los bits
;offset de dir 0x400
;en que direccion esta DIR  0X4006.1000 + 0x400
;DIR está en la direccion 0x4006.1400


        mov  r0,#0x1400
	    movt r0,#0x4006
        mov  r1,#0xff ;1111 1111
        str  r1,[r0]
;configurar PORTM como salida en todos los bits
;offset de dir 0x400
;en que direccion esta DIR  0X4006.3000 + 0x400
;DIR está en la direccion 0x4006.3400


        mov  r0,#0x3400
	    movt r0,#0x4006
        mov  r1,#0xff ;1111 1111
        str  r1,[r0]

;configurar PORTK como digital en todos los bits
;offset de dir 0x51c
;en que direccion esta DIR  0X4006.1000 + 0x51c
;DIR está en la direccion 0x4006.151c


        mov  r0,#0x151c
	    movt r0,#0x4006
        mov  r1,#0xff ;1111 1111
        str  r1,[r0]

;configurar PORTM como digital en todos los bits
;offset de dir 0x51c
;en que direccion esta DIR  0X4006.3000 + 0x51c
;DIR está en la direccion 0x4006.351c


        mov  r0,#0x351c
	    movt r0,#0x4006
        mov  r1,#0xff ;1111 1111
        str  r1,[r0]
 ;mandar una letra al display
;para leer informacion de la memoria ram
;rs=1, rw=1 letra M codigo 0100 1101

        mov  r0,#0x33fc
	    movt r0,#0x4006;accedo a la direccion de memoria de los puertos m
	    mov r1,#0x01;0000 0001 activamos el primer puerto, m0=0,m1=0,m2=1
	    str  r1,[r0]
	    ;inicializamos la pantalla
	    mov r0,#0x13fc
	    movt r0,#0x4006
	    mov r1,#0x38;
	    str  r1,[r0]
	    ;inicializamos la pantalla
	    mov r0,#0x13fc
	    movt r0,#0x4006
	    mov r1,#0x80;
	    str  r1,[r0]
	    ;inicializamos la pantalla
	    mov r0,#0x13fc
	    movt r0,#0x4006
	    mov r1,#0x0c;
	    str  r1,[r0]
	    ;inicializamos la pantalla
	    mov r0,#0x13fc
	    movt r0,#0x4006
	    mov r1,#0x01;
	    str  r1,[r0]
	    ;modificamos los registros m para mandarle informacion a la ram
	    mov  r0,#0x33fc
	    movt r0,#0x4006;accedo a la direccion de memoria de los puertos m
	    mov r1,#0x07;0000 0111 activamos el primer puerto, m0=1,m1=1,m2=1
	    str  r1,[r0]
	    ;con esto leemos de memoria
	    mov r0,#0x13fc
	    movt r0,#0x4006
	    mov r1,#0x4d
        str  r1,[r0]
;enceder 0 el display

conteo  mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x40 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 1 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x79 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 2 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x24 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 3 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x30 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 4 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x19 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 5 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x12 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 6 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x02 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 7 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x38 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 8 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x00 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
;enceder 9 el display

        mov  r0,#0x13fc
	    movt r0,#0x4006
        mov  r1,#0x18 ;mov r1,#0xff cc
        str  r1,[r0]

        bl ret1s
alto	b conteo
;subrutinas
ret1s   mov  r5,#0xffff
        movt r5,#0x001f
ret1s1    subs r5,#0x01
        bne  ret1s1
        bx lr
