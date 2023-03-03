;27 de Noviembre de 2020
;Circuitos Digitales
;Practica 6
;Configuracion de un LCD 16X2


         .global main
	     .data
         .text

;definicion de constantes para uso con bits de control
brs     .equ 0x01 ;0b00000001
brw     .equ 0x02 ;0b00000010
benable .equ 0x04 ;0b00000100
vartmp .equ 0x00;esta variable inicializa el tiempo en 0

main

inipro nop
; habilitar el PORTK y PORTM. bits 11 y 9 del RCGCGPIO 0000 1010 0000 0000
 ;rgcgcpio 0x400f.e608
	mov  r0,#0xe608
	movt r0,#0x400f
    mov  r1,#0xa00
    str  r1,[r0]

;prgpio Base 0x400F.E000
;Offset 0xA08

       mov  r0,#0xea08 ;espera a que los puertos k y m estén habilitados
       movt r0,#0x400f
eapkm  ldr  r1,[r0]
       ands r1,#0xa00
       beq  eapkm


;direccion  base PORTK 0x4006.1000
;apagar (poner a cero)  todos los bits de K
;PORTK DATA offset 0x3fc

 	mov  r0,#0x13fc
	movt r0,#0x4006
        mov  r1,#0x00 ;
        str  r1,[r0]



;direccion base de K 0X4006.1000

;configurar PORTK como salida en todos los bits
;offset de dir 0x400

        mov  r0,#0x1400
	movt r0,#0x4006
        mov  r1,#0xff ;1111 1111
        str  r1,[r0]

;configurar PORTK como digital en todos los bits
;offset de dir 0x51c


        mov  r0,#0x151c
	    movt r0,#0x4006
        mov  r1,#0xff ;
        str  r1,[r0]



;direccion base PORTM 0x4006.3000
;apagar (poner a cero)  todos bits  M2-M0
;PORTM DATA offset 0x3fc

 	mov  r0,#0x33fc
	movt r0,#0x4006
        mov  r1,#0x00 ;
        str  r1,[r0]



;direccion base de M 0X4006.3000

;configurar PORTM como salida en bits M2-M0
;offset de dir 0x400



        mov  r0,#0x3400
	movt r0,#0x4006
        mov  r1,#0x05 ;1111 1111
        str  r1,[r0]

;configurar PORTM como digital en bits M2-M0
;offset de dir 0x51c


        mov  r0,#0x351c
	    movt r0,#0x4006
        mov  r1,#0xff ;1111 1111
        str  r1,[r0]
	    push {lr}
        bl clrports
        pop {lr}

;;j j j j j T i e m p o j j j
;Se escribe en la posision 5- 0000 0011
;pero se le añade el bit de instruccion
;1000 0011-85

         push {lr}
         bl iniciodisplay
         pop {lr}
         mov r6,#0x85
         push {lr}
         bl	 escom
         pop {lr}

         mov r6,#'T'
         push {lr}
         bl	 esdat
         pop {lr}

         mov r6,#'i'
         push {lr}
         bl	 esdat
         pop {lr}

         mov r6,#'e'
         push {lr}
         bl	 esdat
         pop {lr}

         mov r6,#'m'
         push {lr}
         bl	 esdat
         pop {lr}

         mov r6,#'p'
         push {lr}
         bl	 esdat
         pop {lr}

         mov r6,#'o'
         push {lr}
         bl	 esdat
         pop {lr}


tstloop   push {lr}
		  bl cronos
		  pop {lr}
		  b tstloop
*********************************************
;subrutinas
cronos  nop

;j j j j j T i e m p o j j j
;Se escribe en la posision 47- 0100 0111
;pero se le añade el bit de instruccion
;1100 0111-c7
         mov r6,#0xc7
         push {lr}
	     bl escom
	     pop {lr}

;despliega tiempo, tiempo comienza en 0

;vartmp es mi tiempo que empiesa en 0-0x0
        mov r9,#vartmp
destmp1 mov r6,r9
		 push {lr}
         bl compararNumero
         pop {lr}
;los registros bajos son de r7 a r0
;los registros altos son de r8 a  r12
;lsr solo opera con registros bajos
;aqui desplaza los bits de lad decenas hacia la izquierda
         lsr   r6,r6,#4
;suma los 30 para convertir a ascci
         add   r6,#0x30
         push {lr}
         bl		esdat  ;escribe nibble alto(el lado de las decenas)
         pop {lr}
;recuperamos el valor del tiempo
         mov  r6,r9
         push {lr}
         bl compararNumero
         pop {lr}
;dejamos vivos solo los bits de unidades
         and  r6,#0x0f
;sumamos 30 para ascci
         add   r6,#0x30
         push {lr}
         bl		esdat   ;escribe nibble bajo
         pop {lr}
;volvemos a al nibble alto
         mov  r6,#0xc7
         push {lr}
		 bl  escom
		 pop {lr}
;esperamos
         push {lr}
         bl	retdisp
         pop {lr}
;sumamos 1 al tiempo

         adds   r9,#0x01  ;sub
;comparamos 64hex = 100 decimal
;cuando cmp haga la resta, salta la bandera igual a 0
         cmp	r9,#0x64; a r9 le resta 99, el resultado salta la bandera iguales

;si cmp es 0 beq va a "alto"
         beq alto


;buscar ajuste decimal

;    hhhh llll
;      0    0
;      0    1
;
;    mov rx,#0x25 2 decenas 5 unidades 0010 0101
;    and rx,#0xf0                     &1111 0000
;                            resultado 0010 0000
;                                 1->  0001 0000
;                                 1->  0000 1000
;                                 1->  0000 0100
;                                 1->  0000 0010
;                                 1->  0000 0001
;                                 4->  0010 0000 = 0000 0010
;si no fueron iguales, vuelvo a entrar y seguir sumando
         b destmp1

alto nop
          bx lr

;Esta subrutina convierte un numero exadecimal por encima de 9
;a su equivalente en decimal
compararNumero nop
;compara si esta antes que 9
;suma 0
		cmp r6,#0x0a
		bmi suma0
;compara si esta antes que 20
;suma 06
		cmp r6,#0x14
		bmi suma6
;compara si esta antes que 30
;suma 0C
		cmp r6,#0x1E
		bmi suma0C
;compara si esta antes que 40
;suma 12
		cmp r6,#0x28
		bmi suma12
;compara si esta antes que 50
;suma 18
		cmp r6,#0x32
		bmi suma18
;compara si esta antes que 60
;suma 1e
		cmp r6,#0x3c
		bmi suma1e
;compara si esta antes que 70
;suma 24
		cmp r6,#0x46
		bmi suma24
;compara si esta antes que 80
;suma 2a
		cmp r6,#0x50
		bmi suma2a
;compara si esta antes que 90
;suma 30
		cmp r6,#0x5a
		bmi suma30
;compara si esta antes que 100
;suma 36
		cmp r6,#0x64
		bmi suma36
		bx lr
suma0 nop
		bx lr
suma6 add r6,#0x06
		bx lr
suma0C add r6,#0x0C
		bx lr
suma12 add r6,#0x12
		bx lr
suma18 add r6,#0x18
		bx lr
suma1e add r6,#0x1e
		bx lr
suma24 add r6,#0x24
		bx lr
suma2a add r6,#0x2a
		bx lr
suma30 add r6,#0x30
		bx lr
suma36 add r6,#0x36
		bx lr

;Esta rutino asegura el inicio seguro del display segun el manual
;eL PRIMER PASO ES  PRENDER EL DISPLAY
iniciodisplay mov  r6,#0x0f
           push {lr}
           bl escom
           pop {lr}
;tenemos que esperar mas de 15 ml, lo calcule a 20ms
           push {lr}
           bl retdisp
           pop {lr}
;tenemos que poner en funcion set
;enviaremos 0011 1000 = 38
           mov  r6,#0x38
           push {lr}
           bl escom
           pop {lr}
;esperamos 4.1 microsegundos, que son =0.0041ms
;usaremos 20ms
		   push {lr}
           bl retdisp
           pop {lr}
;tenemos que poner en funcion set
;enviaremos 0011 1000 = 38
           mov  r6,#0x38
           push {lr}
           bl escom
           pop {lr}
;esperamos 100 microsegundos, que son =0.1ms
;usaremos 20ms
		   push {lr}
           bl retdisp
           pop {lr}
;tenemos que poner en funcion set
;enviaremos 0011 1000 = 38
           mov  r6,#0x38
           push {lr}
           bl escom
           pop {lr}

;tenemos que poner en funcion set
;enviaremos 0011 1000 = 38
           mov  r6,#0x38
           push {lr}
           bl escom
           pop {lr}
;tenemos que mandar Display ON
;0000 1110 = 0c
           mov  r6,#0x0f
           push {lr}
           bl escom
           pop {lr}
;tenemos que mandar Display Clear
;0000 0001 = 01
           mov  r6,#0x01
           push {lr}
           bl escom
           pop {lr}
;tenemos que mandar Entry Mode Set
;0000 0110 = 06
           mov  r6,#0x06
           push {lr}
           bl escom
           pop {lr}
           bx   lr

ret450n  mov  r5,#50
ret450a subs r5,#0x01
        bne  ret450a
        bx   lr

ret1s   mov  r5,#0x1200
        movt r5,#0x0008
ret1s1  subs r5,#0x01
        bne  ret1s1
        bx   lr

retdisp   mov  r5,#0x7100
        movt r5,#0x0003
retdisp1  subs r5,#0x01
        bne  retdisp1
        bx   lr

;esta rutina pone a cero todos los
;bits de los puertos utilizados
;direccion base PORTM 0x4006.3000
;PORTM DATA offset 0x3fc
clrports mov  r0,#0x33fc  ;cero a c
	    movt r0,#0x4006
        mov  r1,#0x00 ;
        str  r1,[r0]

;direccion base PORTk 0x4006.1000
;PORTM DATA offset 0x3fc
        mov  r0,#0x13fc ;cero a o
	    movt r0,#0x4006
        mov  r1,#0x00 ;
        str  r1,[r0]
        bx LR

;limpia los bits del puerto de control
;direccion base PORTM 0x4006.3000
;PORTM DATA offset 0x3fc
clrctrl mov  r0,#0x33fc  ;cero a M
	    movt r0,#0x4006
        mov  r1,#0x00 ;
        str  r1,[r0]
        bx lr


;lee PORTM
;direccion base PORTm 0x4006.3000
;PORTM DATA offset 0x3fc
;PM2=E PM0=RS
pul_en mov  r0,#0x33fc
       movt r0,#0x4006
;Aqui tenemos el valor de los puertos m y aplicaremos la operacion logica orr
;          r1 = ???? ????
;    #benable = 0000 0100
;         orr = ??? ?1??
;La operacion or establece que si una de sus entradas esta en nivel activo forza la salida a su nivel activo
;por lo tanto obligamos a activar el bit enable
       ldr  r1,[r0]
       orrs r1,#benable
       str  r1,[r0]
;OBLIGAMOS A PERMANECER AL PULSO MAS DE 450 NS COMO NOS INDICA EL MANUAL
       push {lr}
       bl ret450n
       pop {lr}
;esta operacion pone a cero los bits que la ETIQUETA esta proporcionando
; es decir, pone 0, EN LOS BITS QUE INDICA LA SIGUIENTE ETIQUETA
;"#ENABLE=#0B00000100 "
;??? ?1?? = R1
;Aplicamos "bic"
;??? ?0?? = R1
       bic  r1,#benable
;Devolvemos el valor a los puertos m para apagar enable
	   str  r1,[r0]
	   bx	lr



;lee PORTm
;direccion base PORTm 0x4006.3000
;PORTM DATA offset 0x3fc
;PM2=E PM0=RS
pul_RS mov  r0,#0x33fc
       movt r0,#0x4006
;Aqui tenemos el valor de los puertos m y aplicaremos la operacion logica orr
;          r1 = ???? ????
;        #brs = 0000 0001
;         orr = ??? ???1
;La operacion or establece que si una de sus entradas esta en nivel activo forza la salida a su nivel activo
;por lo tanto obligamos a activar el bit rs
       ldr  r1,[r0]
       orrs r1,#brs
       str  r1,[r0]
;OBLIGAMOS A PERMANECER AL PULSO MAS DE 450 NS COMO NOS INDICA EL MANUAL
       push {lr}
       bl ret450n
       pop {lr}
;esta operacion pone a cero los bits que la ETIQUETA esta proporcionando
; es decir, pone 0, EN LOS BITS QUE INDICA LA SIGUIENTE ETIQUETA
;"#rs=#0B00000001 "
;??? ???1 = R1
;Aplicamos "bic"
;??? ???0 = R1
       bic  r1,#brs
;Devolvemos el valor a los puertos m para apagar enable
	   str  r1,[r0]
	   bx	lr
;esta rutina escribe un comando al display
;usa a R6 como registor del dato que se escribira al display
;RS=RW=0 , pulso en E
escom  	mov  r0,#0x13fc ;apunta  a PORTK_DATA
	    movt r0,#0x4006
        str  r6,[r0] ;envia dato a bus de display
        push {lr}
	    bl pul_en
        pop {lr}
        push {lr}
        bl retdisp
        pop {lr}
	    bx	lr



;esta rutina escribe al PORTK lo que ponga en r6
escportk mov  r0,#0x13fc ;r2 a K
	    movt r0,#0x4006
        str  r6,[r0]
        bx	lr


;esta rutina escribe al PORTM lo que ponga en R6
escportm mov  r0,#0x33fc ;r2 a M
	    movt r0,#0x4006
       str  r6,[r0]
        bx	lr



;esta rutina escribe un dato al display
;usa a R6 como registro del dato que se escribira al display
;RS=1 RW=0 , pulso en E
esdat  mov    r0,#0x33fc ; lee PORTM   ;PM2=E  PM0=RS
       movt r0,#0x4006
       ldr  r1,[r0]
       orrs r1,#brs
       str	r1,[r0]     ;RS=1

		mov  r0,#0x13fc ;apunta  a PORTK_DATA
	    movt r0,#0x4006
        str  r6,[r0] ;envia dato a bus de display
        push  {lr}
	    bl pul_en;se activa el pulso enable, para dejar pasar los datos
        pop  {lr}

       mov  r0,#0x33fc ; lee PORTM   ;PM2=E  PM0=RS
       movt r0,#0x4006
       ldr  r1,[r0]
       bic  r1,#brs
       str	r1,[r0]     ;RS=0

	   push {lr}
       bl retdisp
	   pop {lr}

	    bx	lr



		  .end
