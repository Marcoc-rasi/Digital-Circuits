;sintaxis de un programa

;dividir en campos

;label     op code               operand(s)   comments

;etiqueta codigo de operacion   operando(s)   comentarios
;          instrucción


;instrucciones  son las que ejecuta el procesador
;pseudouinstrucciones (directivas)  son las que ejecuta solo el ambiente de desarrollo


            .global	main  ;main es el nombre de la 1a linea del programa

            .data   ; aqui se pondrán valores de inicializacion que el programa requiera

            .text   ; en este campo se pone el programa


;etiqueta se le dice al nombre que le le damos a una linea de codigo
;la etiqueta debe comenzar en la 1a columna del renglon

main       mov  r0,#0x5678  ;cada registro del modelo de programacion es de 32 bits
       ;fuente=de donde se obtiene la informacion  destino=donde se guarda
          ;r0=???? ???? ???? ???? 0010 0011 0100 0101  ????2345
 ;#denota una constante
         ;mov r0,#12345678   r0= 1234  5678   mov parte baja
                             ;    top  bottom

         ; movetop
         movt  r0,#0x1234

       ;antes de la instruccion, r0 contiene 0xaf4b5c2d

        mov r0,#0x5678  ; pone a cero la parte alta

        ;despues de la instruccion r0 contiene 0x00005678

       ; movt solo afecta la parte alta y no modifica la baja

       movt r0,#0x1234
       ;despues de la instruccion r0 contiene 0x12345678

      mov r1,#0x23
      movt r1,#0x1001


      movt  r1,#0x2345
      mov   r1,#0xabcd


     ;addition

     add r0,#1

     add  r0,r1
epn  mov r0,#0xe608    ;en la localidad 0x400fe608      0000 0000 0000 0000 0000
     movt r0,#0x400f ;                                  0000 0001 0000 0000 0000          1000
     mov  r1,#0x1000  ;rcgcgpio
     str  r1,[r0]

     mov r0,#0x4400   ;pno y pn1 sean salidas
     movt r0,#0x4006  ;registro dir
      mov  r1,#0x03  ;0000 0011
     str  r1,[r0]

     mov  r0,#0x451c   ;pno y pn1 sean digitales
     movt r0,#0x4006   ;registro DEN
     mov  r1,#0x03  ;0000 0011
     str  r1,[r0]

cuen mov  r0, #0x43fc   ;
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x03  ;0000 0011
     str  r1,[r0]


     mov  r0, #0x43fc   ;
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x02  ;0000 0011
     str  r1,[r0]

     mov  r0, #0x43fc   ;
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x01  ;0000 0011
     str  r1,[r0]


     mov  r0, #0x43fc   ;
     movt r0,#0x4006   ;registro datos
     mov  r1,#0x00  ;0000 0011
     str  r1,[r0]
     b cuen
perro b    perro

      .end
