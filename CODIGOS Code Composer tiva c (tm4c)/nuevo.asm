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

vartmp .equ 0x00

main
    mov r7,#0x20
    lsr r7,r7,#4
;alta b alta

    b inipro


; habilitar el PORTK y PORTM. bits 11 y 9 del RCGCGPIO 0000 1010 0000 0000

inipro nop

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



      bl clrports

*************************************
;encendemos el display
tstloop   bl iniciodisplay
		  bl cronos



tstdato  mov r6,#'0'
tstdat1  bl	 esdat
         bl	 ret1s
         mov r6,#'1'
         bl	 esdat
         bl	 ret1s
         mov r6,#'2'
         bl	 esdat
         bl	 ret1s
         mov r6,#'3'
         bl	 esdat
         bl	 ret1s
;me voy a mover a la linea 2 posicion 4b
;1100 0000
         mov r6,#0xc0
         bl	 escom
         bl	 ret1s
         mov r6,#0xc6
         bl	 escom
         bl	 ret1s
         mov r6,#0x80
         bl	 escom
         bl	 ret1s
         bl	 ret1s
         bl	 ret1s
;inicializamos el display
cronos  nop

;j j j j j T i e m p o j j j
;Se escribe en la posision 5- 0000 0011
;pero se le añade el bit de instruccion
;1000 0011-85
         mov r6,#0x85
         bl	 escom

         mov r6,#'T'
         bl	 esdat

         mov r6,#'i'
         bl	 esdat

         mov r6,#'e'
         bl	 esdat

         mov r6,#'m'
         bl	 esdat

         mov r6,#'p'
         bl	 esdat

         mov r6,#'o'
         bl	 esdat
;j j j j j T i e m p o j j j
;Se escribe en la posision 47- 0100 0111
;pero se le añade el bit de instruccion
;1100 0111-c7
         mov r6,#0xc7
	     bl escom
;despliega tiempo, tiempo comienza en 0

;vartmp es mi tiempo que empiesa en 0-0x00
         ;pop   {r9}
         ;convertir a ascii
;los registros bajos son de r7 a r0
;los registros altos son de r8 a  r12
;lsr solo opera con registros bajos
;aqui desplaza los bits de lad decenas hacia la izquierda
destmp mov r9,#vartmp
destmp1 mov r6,r9
         bl compararNumero
         lsr   r6,r6,#4
;suma los 30 para convertir a ascci
         add   r6,#0x30
         bl		esdat  ;escribe nibble alto
;recuperamos el valor del tiempo
         mov  r6,r9
         bl compararNumero
;dejamos vivos solo los bits de unidades
         and  r6,#0x0f
;sumamos 30 para ascci
         add   r6,#0x30
         bl		esdat   ;escribe nibble bajo
;volvemos a al nibble alto
         mov  r6,#0xc7
		 bl   escom

         push {lr}
         bl	retdisp
         pop {lr}
;sumamos 1 al tiempo

         adds   r9,#0x01  ;sub

         cmp	r9,#0x3c; a r9 le resta 99, el resultado salta la bandera iguales

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

         bl destmp1




;alto b alto

alto nop
destmp22 mov r2,r9
         bl compararNumero2
         lsr   r2,r2,#4
;suma los 30 para convertir a ascci
         add   r2,#0x30
         bl		esdat2  ;escribe nibble alto
;recuperamos el valor del tiempo
         mov  r2,r9
         bl compararNumero2
;dejamos vivos solo los bits de unidades
         and  r2,#0x0f
;sumamos 30 para ascci
         add   r2,#0x30
         bl		esdat2   ;escribe nibble bajo
;volvemos a al nibble alto
         mov  r2,#0xc7
		 bl   escom2

         push {lr}
         bl	retdisp
         pop {lr}
;sumamos 1 al tiempo

         adds   r9,#0x01  ;sub

         cmp	r9,#0x63; a r9 le resta 99, el resultado salta la bandera iguales

         beq alto2


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

         bl destmp22

alto2 b alto2
         ;b   tstdato
       ; push {LR}
       ; pop {LR}
;************************************
;Esta subrutina convierte un numero exadecimal por encima de 9
;a su equivalente en decimal
compararNumero nop
;compara si esta antes que 9
;suma 0
		cmp r6,#0x0a
		push {lr}
		bmi suma0
		pop {lr}
;compara si esta antes que 20
;suma 06
		cmp r6,#0x14
		push {lr}
		bmi suma6
		pop {lr}
;compara si esta antes que 30
;suma 0C
		cmp r6,#0x1E
		push {lr}
		bmi suma0C
		pop {lr}
;compara si esta antes que 40
;suma 12
		cmp r6,#0x28
		push {lr}
		bmi suma12
		pop {lr}
;compara si esta antes que 50
;suma 18
		cmp r6,#0x32
		push {lr}
		bmi suma18
		pop {lr}
;compara si esta antes que 60
;suma 1e
		cmp r6,#0x3c
		push {lr}
		bmi suma1e
		pop {lr}
;compara si esta antes que 70
;suma 24
		cmp r6,#0x46
		push {lr}
		bmi suma24
		pop {lr}
;compara si esta antes que 80
;suma 2a
		cmp r6,#0x50
		push {lr}
		bmi suma2a
		pop {lr}
;compara si esta antes que 90
;suma 30
		cmp r6,#0x5a
		push {lr}
		bmi suma30
		pop {lr}
;compara si esta antes que 100
;suma 36
		cmp r6,#0x64
		push {lr}
		bmi suma36
		pop {lr}
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


;rutina de retardo de 450 nS
;todas las instrucciones tardan, y ciclo en ejecutarse
;16mhz 16000000
;1/16000000 =  t = 62.5 ns

;esta instruccion es de tiempo fijo porque solo se ejecuta una vez en la subrutina
ret450n  mov  r5,#50
ret450a subs r5,#0x01
        bne  ret450a

;esta instruccion es de tiempo fijo porque solo se ejecuta una vez en la subrutina
        bx   lr
; si cada tiempo fijo vale 62.5 y tenemos 2 tiempos fijos
;El tiempo fijo total es 62.5*2=125 ns

;si cada tiempo variable vale 62.5 y tenemos 2 tiempos variables
;El tiempo variable total es 62.5*2=125 ns
;pero esta rutina se repite el numero de veces que se ejecute la resta r5-1
;sin que r5 sea 0
; por lo tanto, El tiempo variable total es 125*50 = 6250
;La suma total es el quivalente a Tiempo fijo + tiempo variable
;Tiempo total =6250+125=6500


;Para que el lcd lea un dato eneble tiene que estaren estado alto por lo menos 450 ns
;nosotros ponemos usamos 6500 mucho mas tiempo por lo que aseguramos que sobrepase el tiempo minimo


;subrutina de retardo de 1 segundo
;8,000,000=003d 0900 3D0900
ret1s   mov  r5,#0x1200
        movt r5,#0x0008
ret1s1  subs r5,#0x01
        bne  ret1s1
        bx   lr
;si cada tiempo fijo vale 62.5 y tenemos 3 tiempos fijos
;El tiempo fijo total es 62.5*3=187.5 ns
;si cada tiempo variable vale 62.5 y tenemos 2 tiempos variables
;El tiempo variable total de una sola subrutina es 62.5*2=125 ns
;pero esta rutina se repite el numero de veces que se ejecute la resta r5-1
;sin que r5 sea 0
; por lo tanto, El tiempo variable total es 125*4,000,000 = 500,000,000
;La suma total es el quivalente a Tiempo fijo + tiempo variable
;Tiempo total =1,000,000,000+187.5= 1,000,000,187 ns
;aproximadamente un segundo
; 1 seg = 1,000,000,000


;subrutina de retardo de 20 milisegundo
;16,000=0000 3e80
retdisp   mov  r5,#0x7100
        movt r5,#0x0003
retdisp1  subs r5,#0x01
        bne  retdisp1
        bx   lr
;si cada tiempo fijo vale 62.5 y tenemos 3 tiempos fijos
;El tiempo fijo total es 62.5*3=187.5 ns
;si cada tiempo variable vale 62.5 y tenemos 2 tiempos variables
;El tiempo variable total de una sola subrutina es 62.5*2=125 ns
;pero esta rutina se repite el numero de veces que se ejecute la resta r5-1
;sin que r5 sea 0
; por lo tanto, El tiempo variable total es 125*160000 = 20,000,000
;La suma total es el quivalente a Tiempo fijo + tiempo variable
;Tiempo total =20,000,000+187.5= 2,000,187 ns
;aproximadamente un segundo
; 20 miliseg = 2,000,000 ns

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



;esta rutina escribe al PORTK lo que ponga en R2
escportk mov  r0,#0x13fc ;r2 a K
	    movt r0,#0x4006
        str  r6,[r0]
        bx	lr


;esta rutina escribe al PORTM lo que ponga en R2
escportm mov  r0,#0x33fc ;r2 a M
	    movt r0,#0x4006
       str  r6,[r0]
        bx	lr



;esta rutina escribe un dato al display
;usa a R2 como registro del dato que se escribira al display
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
****************************************************************
;************************************
;Esta subrutina convierte un numero exadecimal por encima de 9
;a su equivalente en decimal
compararNumero2 nop
;compara si esta antes que 9
;suma 0
		cmp r2,#0x0a
		push {lr}
		bmi suma0r
		pop {lr}
;compara si esta antes que 20
;suma 06
		cmp r2,#0x14
		push {lr}
		bmi suma6r
		pop {lr}
;compara si esta antes que 30
;suma 0C
		cmp r2,#0x1E
		push {lr}
		bmi suma0Cr
		pop {lr}
;compara si esta antes que 40
;suma 12
		cmp r2,#0x28
		push {lr}
		bmi suma12r
		pop {lr}
;compara si esta antes que 50
;suma 18
		cmp r2,#0x32
		push {lr}
		bmi suma18r
		pop {lr}
;compara si esta antes que 60
;suma 1e
		cmp r2,#0x3c
		push {lr}
		bmi suma1er
		pop {lr}
;compara si esta antes que 70
;suma 24
		cmp r2,#0x46
		push {lr}
		bmi suma24r
		pop {lr}
;compara si esta antes que 80
;suma 2a
		cmp r2,#0x50
		push {lr}
		bmi suma2ar
		pop {lr}
;compara si esta antes que 90
;suma 30
		cmp r2,#0x5a
		push {lr}
		bmi suma30r
		pop {lr}
;compara si esta antes que 100
;suma 36
		cmp r2,#0x64
		push {lr}
		bmi suma36r
		pop {lr}
		bx lr


;esta rutina escribe un comando al display
;usa a R2 como registor del dato que se escribira al display
;RS=RW=0 , pulso en E
escom2  	mov  r0,#0x13fc ;apunta  a PORTK_DATA
	    movt r0,#0x4006
        str  r2,[r0] ;envia dato a bus de display
        push {lr}
	    bl pul_en
        pop {lr}
        push {lr}
        bl retdisp
        pop {lr}
	    bx	lr



;esta rutina escribe al PORTK lo que ponga en R2
escportk2 mov  r0,#0x13fc ;r2 a K
	    movt r0,#0x4006
        str  r2,[r0]
        bx	lr


;esta rutina escribe al PORTM lo que ponga en R2
escportm2 mov  r0,#0x33fc ;r2 a M
	    movt r0,#0x4006
       str  r2,[r0]
        bx	lr



;esta rutina escribe un dato al display
;usa a R2 como registro del dato que se escribira al display
;RS=1 RW=0 , pulso en E
esdat2  mov    r0,#0x33fc ; lee PORTM   ;PM2=E  PM0=RS
       movt r0,#0x4006
       ldr  r1,[r0]
       orrs r1,#brs
       str	r1,[r0]     ;RS=1

		mov  r0,#0x13fc ;apunta  a PORTK_DATA
	    movt r0,#0x4006
        str  r2,[r0] ;envia dato a bus de display
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


suma0r nop
		bx lr
suma6r add r2,#0x06
		bx lr
suma0Cr add r2,#0x0C
		bx lr
suma12r add r2,#0x12
		bx lr
suma18r add r2,#0x18
		bx lr
suma1er add r2,#0x1e
		bx lr
suma24r add r2,#0x24
		bx lr
suma2ar add r2,#0x2a
		bx lr
suma30r add r2,#0x30
		bx lr
suma36r add r2,#0x36
		bx lr
        .end
