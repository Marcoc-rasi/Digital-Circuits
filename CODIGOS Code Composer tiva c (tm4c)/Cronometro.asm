  .global main
		.data
		.text

main

;Tenemos que ir al RCGCGPIO, que nos permite encender o apagar los puertos de la tarjeta
;encenderemos los puertos k y m
;Obtenemos la direccion de RCGCGPIO, del manual de la tarjeta
;RCGCGPIO
;Base 0x400F.E000
;Offset 0x608
;El esquema rebajo representa el orden de los puertos dentro de RCGCGPIO
;estado inicial
                                        ;n mlkj hgfe dcba
;                                0000 0000 0000 0000 0000
;puerto k y m encendidos
;                                0000 0000 1010 0000 0000  en HEX A00

epk  mov r0,#0xe608
     movt r0,#0x400f
     mov  r1,#0xa00
     str  r1,[r0]

;Una vez que tenemos los puertos encencidos, tenemos que asegurarnos que esten activos
;Ya que este encendido no es inmediato
;El prgpio nos permite saber que puertos estan activos
;Obtenemos la direccion de prgpio, del manual de la tarjeta
;Base 0x400F.E000
;Offset 0xA08
                                        ;n mlkj hgfe dcba
;                                0000 0000 0000 0000 0000
;puerto k y m encendidos
;                                0000 0000 1000 0000 0000  en HEX 800
;                                0000 0000 0010 0000 0000  en HEX 200
;si rcgcgpio es distinto de #0x200 enotnces el puerto K esta apagado aun
;200 porque obtiene la multiplicacion de "and" bit a bit, encontrara el primero  puerto encendido "k" y saltara la bandera
;usualmente cuando se activan mas de 1 puerto a la vez, una vez que uno este activo
;se puede asegurar que los demas lo estan por igual
;obtenemos la direccion de prgpio
	 mov r0,#0xea08
	 movt r0,#0x400f

;Copiamos el valor que contenga la direccion en  el registro r1
eapk ldr r1,[r0];

;EJECUTAMOS la compuerta and
;La compuerta And dara como resultado el mismo numero, solo si r1 = #0xa00
;Cuando esta operacion sucede, sabemos que los numeros son iguales
;y se levanta la bandera Z=1,
;ya que son iguales la bandera beq es verdadera por lo tanto avanza la instruccion
     ands r1,#0xa00
	 beq eapk

;GPIO Direction (GPIODIR), offset 0x400
;GPIO Port K (AHB) base: 0x4006.1000
;GPIO Port K (AHB) base + offset : 0x4006.1400
;registro dir    0 = entrada  1 = salida
;1111 1111, asi ponemos todos puertos k en salida
     mov r0,#0x1400
     movt r0,#0x4006
     mov  r1,#0xff  ;1111 1111
     str  r1,[r0]


;GPIO Digital Enable (GPIODEN), offset 0x51C
;GPIO Port K (AHB) base: 0x4006.1000
;GPIO Port K (AHB) base + offset : 0x4006.151c
;registro DEN   0 = analog   1 = digital
;1111 1111, asi ponemos todos puertos k en digital
     mov  r0,#0x151c
     movt r0,#0x4006
     mov  r1,#0xff  ;1111 1111
     str  r1,[r0]


;GPIO Direction (GPIODIR), offset 0x400
;GPIO Port m (AHB) base: 0x4006.3000
;GPIO Port m (AHB) base + offset : 0x4006.3400
;registro dir    0 = entrada  1 = salida
;1111 1111, asi ponemos todos puertos m en salida
	 mov  r2,#0x3400
     movt r2,#0x4006
     mov  r1,#0xff  ;1111 1111
     str  r1,[r2]


;GPIO Digital Enable (GPIODEN), offset 0x51C
;GPIO Port m (AHB) base: 0x4006.3000
;GPIO Port m (AHB) base + offset : 0x4006.351c
;registro DEN   0 = analog   1 = digital
;1111 1111, asi ponemos todos puertos m en digital
     mov  r2,#0x351c   ;pm0 a pm7 sean digitales
     movt r2,#0x4006   ;registro DEN   0 = analog   1 = digital
     mov  r1,#0xff  ;1111 1111
     str  r1,[r2]


;Vamos al registro dedatos
enci mov  r0, #0x13fc   ; Encender display
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x0c  ;0000 1100
     str  r1,[r0]

     bl pulsc ; subrrutina pulso comando

	 bl ret1s ; subrrutina retardo

rece mov  r0, #0x13fc   ; Recet display
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x01  ;0000 0001
     str  r1,[r0]

     bl pulsc ; subrrutina pulso comando

	 bl ret1s ; subrrutina retardo

;********************************************************************

     mov  r0, #0x13fc   ; T
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x54  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ; E
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x45  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ; ESPACIO
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x20  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ; A
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x41 ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ; M
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x4d ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

  mov  r0, #0x13fc   ; O
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x4f  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ; ESPACIO
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x20  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ;B
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x42  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ; O
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x4F  ;
     str  r1,[r0]


     bl puls ; subrrutina pulso ingresar dato



	 mov  r0, #0x13fc   ;L
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x4C  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato

     mov  r0, #0x13fc   ;A
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x41  ;
     str  r1,[r0]

     bl puls ; subrrutina pulso ingresar dato


cero     b cero

;****************************
; Subrrutinas de retardo
ret1s	 mov r3,#0xffff
	 	 movt r3,#0x0001f
ret1 	 subs r3,#0x01; retrasa perdiendo el tiempo restando de uno en uno a r2
	 	 bne ret1   ; cuando r3 es = 0 salta a la siguiente instruccion
		 bx lr

ret2s	 mov r3,#0x0fff
	 	 movt r3,#0x0000
ret2 	 subs r3,#0x01; retrasa perdiendo el tiempo restando de uno en uno a r2
	 	 bne ret2   ; cuando r2 es = 0 salta a la siguiente instruccion
		 bx lr
;*******************************
; Subrrutinas de pulso
puls  mov  r2, #0x33fc   ; Pulso para ingresar dato
     movt r2,#0x4006   ;registro datos
     mov  r1,#0x05  ;0000 0101
     str  r1,[r2]

     push{lr}
	 bl ret1s ; subrrutina retardo
     pop{lr}

 	 mov  r2, #0x33fc   ;
     movt r2,#0x4006   ;registro datos
     mov  r1,#0x01  ;0000 0001
     str  r1,[r2]

     bx lr

pulsc  mov  r2, #0x33fc   ; Pulso para ingresar comando
     movt r2,#0x4006   ;registro datos
     mov  r1,#0x04  ;0000 0100
     str  r1,[r2]

     push{lr}
	 bl ret1s ; subrrutina retardo
     pop{lr}

 	 mov  r2, #0x33fc   ;
     movt r2,#0x4006   ;registro datos
     mov  r1,#0x00  ;0000 0000
     str  r1,[r2]

     bx lr
     .end
