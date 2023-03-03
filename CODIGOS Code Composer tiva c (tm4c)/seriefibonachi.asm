 .global main

            .data


            .text

;store register in memory  STR

;  STR RegFuente,[RegDestino]

;       RegFuente contiene el valor que quiero guardar en memoria
 ;      RegDestino contiene la localidad de memoria donde se guarda el valor

;Load register from memory  LDR

  ;LDR RegDestino,[RegFuente]

       ;RegFuente contiene el valor de la localidad de memoria leida
       ;RegDestino registro donde se guardará el valor


;guardar en las localidades los valores semilla
;estas localidades seran la 0x2000.1000 y la 0x2000.1004

;0x2000.1000
;0x2000.1001
;0x2000.1002   guardar cero
;0x2000.1003

;0x2000.1004
;0x2000.1005   guardar 1
;0x2000.1006
;0x2000.1007

;r7 será el apuntador de memoria
;r3  el registro del dato

    ; rx    hhhh    llll
     ;       top   bottom


      ; r7   2000    1000
     ;       top   bottom

   ;       top   bottom


      ; r7   2000    1000
     ;       top   bottom

main    mov r7,#0x1000  ;apuntador de memoria a la localidad
        movt r7,#0x2000 ;0x2000.1000

        mov r3,#0x00    ;contiene un dato
        movt r3,#0x00

        str  r3,[r7]


        mov r6,#0x1004  ;apuntador de memoria a la localidad
        movt r6,#0x2000  ;0x2000.1004

        mov r3,#0x01    ;contiene un dato
        movt r3,#0x00

        str  r3,[r6]    ;

genf    ldr r5,[r7]
        ldr r0,[r6]

        add r5,r0

        add r6,#0x04
        add r7,#0x04

        str  r5,[r6]
        b genf















            .end
