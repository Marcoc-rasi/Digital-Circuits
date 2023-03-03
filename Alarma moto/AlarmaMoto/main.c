#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"




#define ValPLLFREQ0 0X00800060;
#define ValPLLFREQ1 0X00000004;

    uint32_t  ValorADC;
    uint32_t ui32Loop;
    uint32_t lm35=0;
    uint32_t Fotoresistencia=0;
    uint32_t AcelerometroX=0;
    uint32_t AcelerometroY=0;
    int promediolm35=0;
    int promedioFotoresistencia=0;
    int promedioAcelerometroX=0;
    int promedioAcelerometroY=0;
    float ValorADCf;
    char Codigo="a";
    int c=0;
    int r=0;
#define brs 0b00000001
#define brw 0b00000010
#define benable 0x04 //0b00000100
#define vartmpDecenas 0x00//esta variable inicializa el tiempo en 0
#define vartmpUniades 0x00//esta variable inicializa el tiempo en 0
//
//FUNCIONES//
//configuracionPuertos habilita los poertos, los dispone como salidas digitales
//inicializamos rs y rw en  0, asi como todos los puertos k
 void configuracionPuertos()
 {
     /*; habilitar el PORTK y PORTM. bits 11 y 9 del RCGCGPIO 0000 1010 0000 0000

        inipro nop

         ;rgcgcpio 0x400f.e608
            mov  r0,#0xe608
            movt r0,#0x400f
                mov  r1,#0xa00  ;0000 1010 0000 0000
                str  r1,[r0]

        ;prgpio Base 0x400F.E000
        ;Offset 0xA08

               mov  r0,#0xea08 ;espera a que los puertos k y m estén habilitados
               movt r0,#0x400f
        eapkm  ldr  r1,[r0]
               ands r1,#0xa00
               ;cmp r1,#0xa00
               ;bne eapkm
               beq  eapkm*/
        //#define SYSCTL_RCGCGPIO_R9 Y SYSCTL_RCGCGPIO_R11, K Y M RESPECTIVAMENTE 0B0000 1010 0000 0000
        //TENEMOS QUE ACTIVAR LOS DOS PUERTOS Y ESPERAR A QUE UNO ESTE ABIERTO
        //el SYSCTL_RCGCGPIO_R va a guardar la informacion de los puertos a encender
        //si le das el valos directo en hexadecimal a 8 bits exacto de los puertos que quieres tambien
        //los activa
        //primero enmascaro con or el valor que quiero que tenga, asi no afecto el valor de los demas registros
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R9 ;
        //comparo con un and
        //todos los bitsque tengan cero obtendran cero de resultado
        //todos los bits que estenen 1, si la otra variable es 1, deja el 1
        //asi el resultado ya no es 0
        //aun asi esta operacion se realiza bit a bit por lo que cuando tetecte el primer puerto encencido
        //ya no verificara el segundo
        while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R9) == 0);
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11 ;
        while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R11) == 0);
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1 ;
        while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R1) == 0);

        /*
              ;direccion base de K 0X4006.1000

              ;configurar PORTK como salida en todos los bits
              ;offset de dir 0x400

                      mov  r0,#0x1400
                      movt r0,#0x4006
                      mov  r1,#0xff ;1111 1111
                      str  r1,[r0]

              ;configurar PORTK como digital en todos los bits
              ;offset de den 0x51c  DEN


                      mov  r0,#0x151c
                      movt r0,#0x4006
                      mov  r1,#0xff ;
                      str  r1,[r0]

               ;direccion  base PORTK 0x4006.1000
               ;ENCENDER (poner a 1)los PRIMEROS DOS bits de N
               ;PORTK DATA offset 0x3fc

                mov  r0,#0x13fc
                movt r0,#0x4006
                mov  r1,#0x00 ;
                str  r1,[r0] */
        // pongo el puerto k como salida y digital
        //todos sus puertos
        GPIO_PORTK_DIR_R = 0B11111111;
        GPIO_PORTK_DEN_R = 0B11111111;
        GPIO_PORTK_DATA_R = 0X00;
        //Pongo el puerto m como salida y digital
        // solo los puertos 0 y 2
        GPIO_PORTM_DIR_R = 0B00000101;
        GPIO_PORTM_DEN_R = 0B00000101;
        GPIO_PORTM_DATA_R = 0X05;
        //CONFIGURACION PUERTOS B
        GPIO_PORTB_AHB_DIR_R = 0B00000000;
        GPIO_PORTB_AHB_DEN_R = 0B00000011;
        GPIO_PORTB_AHB_DATA_R = 0X00;
  }
 void Cronometro(float seg)
 {
         //Escribimos en el puerto 0000 0000
         GPIO_PORTK_DATA_R |=0X00;
         float VelCPU = 62.5*(10E-9);//A 16 Mhz T=62.5 nS
         int TICKS = seg/VelCPU;//obtenemos el numero para el systick
         NVIC_ST_RELOAD_R=TICKS;
         //Ponemos A NUESTRA DISPOSICION CLOCK SOURC, SIN INTERRUPCIONES(INTEN), Y ACTIVADO (ENABLE)
         NVIC_ST_CTRL_R=0X05;    //CLK_SRC  INTEN  EN 0101
       // checamos la bandera de count posicion 16
         while (( NVIC_ST_CTRL_R&0x10000)==0); // 0001 0000 0000 0000 0000
      //Cuando pase este ciclo el tiempo acabara
 }

 void clearPorts()
 {
     /*;esta rutina pone a cero todos los
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
             bx LR*/

      GPIO_PORTK_DATA_R = 0X00;
      GPIO_PORTM_DATA_R = 0X00;
 }
//esta funcion manda el comando al display el dato ya tiene que estar registrado en el registro destino
void EscribirComando()
{
    GPIO_PORTM_DATA_R |= 0x04;
    Cronometro(0.02);
    GPIO_PORTM_DATA_R &= 0xfb;
}
void inicioDisplay()
{
    /*;Esta rutino asegura el inicio seguro del display segun el manual
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
           bx   lr*/

    //eL PRIMER PASO ES  PRENDER EL DISPLAY
    GPIO_PORTK_DATA_R = 0X0f;
    EscribirComando();
    //tenemos que esperar mas de 15 ml, lo calcule a 20ms
    Cronometro(0.02);
    EscribirComando();
    //tenemos que poner en funcion set
    //enviaremos 0011 1000 = 38
    GPIO_PORTK_DATA_R = 0X38;
    EscribirComando();
    //;esperamos 4.1 microsegundos, que son =0.0041ms
    //;usaremos 20ms
    Cronometro(0.02);
    EscribirComando();
    //;tenemos que poner en funcion set
    //;enviaremos 0011 1000 = 38
    GPIO_PORTK_DATA_R = 0X38;
    EscribirComando();
    //;esperamos 100 microsegundos, que son =0.1ms
    //;usaremos 20ms
    Cronometro(0.02);
    EscribirComando();
    //;tenemos que poner en funcion set
    //;enviaremos 0011 1000 = 38
    GPIO_PORTK_DATA_R = 0X38;
    EscribirComando();
    //;tenemos que poner en funcion set
    //;enviaremos 0011 1000 = 38
    GPIO_PORTK_DATA_R = 0X38;
    EscribirComando();
    //;tenemos que mandar Display ON
    //;0000 1110 = 0c
    GPIO_PORTK_DATA_R = 0X0c;
    EscribirComando();
    //;tenemos que mandar Display Clear
    //;0000 0001 = 01
    GPIO_PORTK_DATA_R = 0X01;
    EscribirComando();
    //;tenemos que mandar Entry Mode Set
    //;0000 0110 = 06
    GPIO_PORTK_DATA_R = 0X06;
    EscribirComando();
}
void EscribirDatos()
{

    GPIO_PORTM_DATA_R |= brs;
    GPIO_PORTM_DATA_R |= benable;
    Cronometro(0.02);
    GPIO_PORTM_DATA_R &= 0xfa;
}

void Abecedario(char letra)
{
    int e=0;
    switch( letra )
    {
        case 'A':
            GPIO_PORTK_DATA_R = 0x41;
            EscribirDatos();
            break;
        case 'a':
            GPIO_PORTK_DATA_R = 0x61;
            EscribirDatos();
            break;
        case 'B':
            GPIO_PORTK_DATA_R = 0x42;
            EscribirDatos();
            break;
        case 'b':
            GPIO_PORTK_DATA_R = 0x62;
            EscribirDatos();
            break;
        case 'C':
            GPIO_PORTK_DATA_R = 0x43;
            EscribirDatos();
            break;
        case 'c':
            GPIO_PORTK_DATA_R = 0x63;
            EscribirDatos();
            break;
        case 'D':
            GPIO_PORTK_DATA_R = 0x44;
            EscribirDatos();
            break;
        case 'd':
            GPIO_PORTK_DATA_R = 0x64;
            EscribirDatos();
            break;
        case 'E':
            GPIO_PORTK_DATA_R = 0x45;
            EscribirDatos();
            break;
        case 'e':
            GPIO_PORTK_DATA_R = 0x65;
            EscribirDatos();
            break;
        case 'F':
            GPIO_PORTK_DATA_R = 0x46;
            EscribirDatos();
            break;
        case 'f':
            GPIO_PORTK_DATA_R = 0x66;
            EscribirDatos();
            break;
        case 'G':
            GPIO_PORTK_DATA_R = 0x47;
            EscribirDatos();
            break;
        case 'g':
            GPIO_PORTK_DATA_R = 0x67;
            EscribirDatos();
            break;
        case 'H':
            GPIO_PORTK_DATA_R = 0x48;
            EscribirDatos();
            break;
        case 'h':
            GPIO_PORTK_DATA_R = 0x68;
            EscribirDatos();
            break;
        case 'I':
            GPIO_PORTK_DATA_R = 0x49;
            EscribirDatos();
            break;
        case 'i':
            GPIO_PORTK_DATA_R = 0x69;
            EscribirDatos();
            break;
        case 'J':
            GPIO_PORTK_DATA_R = 0x4a;
            EscribirDatos();
            break;
        case 'j':
            GPIO_PORTK_DATA_R = 0x6a;
            EscribirDatos();
            break;
        case 'K':
            GPIO_PORTK_DATA_R = 0x4b;
            EscribirDatos();
            break;
        case 'k':
            GPIO_PORTK_DATA_R = 0x6b;
            EscribirDatos();
            break;
        case 'L':
            GPIO_PORTK_DATA_R = 0x4c;
            EscribirDatos();
            break;
        case 'l':
            GPIO_PORTK_DATA_R = 0x6c;
            EscribirDatos();
            break;
        case 'M':
            GPIO_PORTK_DATA_R = 0x4d;
            EscribirDatos();
            break;
        case 'm':
            GPIO_PORTK_DATA_R = 0x6d;
            EscribirDatos();
            break;
        case 'N':
            GPIO_PORTK_DATA_R = 0x4e;
            EscribirDatos();
            break;
        case 'n':
            GPIO_PORTK_DATA_R = 0x6e;
            EscribirDatos();
            break;
        case 'O':
            GPIO_PORTK_DATA_R = 0x4f;
            EscribirDatos();
            break;
        case 'o':
            GPIO_PORTK_DATA_R = 0x6f;
            EscribirDatos();
            break;
        case 'P':
            GPIO_PORTK_DATA_R = 0x50;
            EscribirDatos();
            break;
        case 'p':
            GPIO_PORTK_DATA_R = 0x70;
            EscribirDatos();
            break;
        case 'Q':
            GPIO_PORTK_DATA_R = 0x51;
            EscribirDatos();
            break;
        case 'q':
            GPIO_PORTK_DATA_R = 0x71;
            EscribirDatos();
            break;
        case 'R':
            GPIO_PORTK_DATA_R = 0x52;
            EscribirDatos();
            break;
        case 'r':
            GPIO_PORTK_DATA_R = 0x72;
            EscribirDatos();
            break;
        case 'S':
            GPIO_PORTK_DATA_R = 0x53;
            EscribirDatos();
            break;
        case 's':
            GPIO_PORTK_DATA_R = 0x73;
            EscribirDatos();
            break;
        case 'T':
            GPIO_PORTK_DATA_R = 0x54;
            EscribirDatos();
            break;
        case 't':
            GPIO_PORTK_DATA_R = 0x74;
            EscribirDatos();
            break;
        case 'U':
            GPIO_PORTK_DATA_R = 0x55;
            EscribirDatos();
            break;
        case 'u':
            GPIO_PORTK_DATA_R = 0x75;
            EscribirDatos();
            break;
        case 'V':
            GPIO_PORTK_DATA_R = 0x56;
            EscribirDatos();
            break;
        case 'v':
            GPIO_PORTK_DATA_R = 0x76;
            EscribirDatos();
            break;
        case 'W':
            GPIO_PORTK_DATA_R = 0x57;
            EscribirDatos();
            break;
        case 'w':
            GPIO_PORTK_DATA_R = 0x77;
            EscribirDatos();
            break;
        case 'X':
            GPIO_PORTK_DATA_R = 0x58;
            EscribirDatos();
            break;
        case 'x':
            GPIO_PORTK_DATA_R = 0x78;
            EscribirDatos();
            break;
        case 'Y':
            GPIO_PORTK_DATA_R = 0x59;
            EscribirDatos();
            break;
        case 'y':
            GPIO_PORTK_DATA_R = 0x79;
            EscribirDatos();
            break;
        case 'Z':
            GPIO_PORTK_DATA_R = 0x5a;
            EscribirDatos();
            break;
        case 'z':
            GPIO_PORTK_DATA_R = 0x7a;
            EscribirDatos();
            break;
        case ' ':
            GPIO_PORTK_DATA_R = 0x20;
            EscribirDatos();
            break;
        default :
            e++;
    }

}
void EscribirDisplay(char texto[])
{
    //GPIO_PORTK_DATA_R = 0X84;
    //EscribirComando();
    //GPIO_PORTK_DATA_R = 0xc7;
    char DatoArreglo = texto[0];
    int i=0;

    GPIO_PORTK_DATA_R = 0X80;
    EscribirComando();
    while(DatoArreglo!='\0')
      {

        //UART0_DR_R=DatoArreglo;
        Abecedario(DatoArreglo);
        i++;
        DatoArreglo = texto[i];
        if(i==16)
        {
            GPIO_PORTK_DATA_R = 0Xc0;
            EscribirComando();
        }
      }

}


void inicioLucesYMov()
{
    //habilitamos el puerto p0
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R13;
    ValorADC=65565;
    GPIO_PORTP_DATA_R = 0X00;
    GPIO_PORTP_DEN_R = 0X03; //HABILITO EL PIN DIGITAL p0 y p1
    GPIO_PORTP_DIR_R = 0X01; //lo uso como salida p0 y como entrada p1
    GPIO_PORTP_DATA_R = 0X00;
}
void inicioServo()
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;//habilito el puerto D
    SYSCTL_RCGCTIMER_R |= 0X01;//habilito el timer 0 correspondiente a d0 t0ccp0

    GPIO_PORTD_AHB_DEN_R |= 0x01; //BIT 1 DIGITAL
    GPIO_PORTD_AHB_DIR_R |= 0x01; //bit 1 SALIDA
    GPIO_PORTD_AHB_DATA_R = 0x00; // SALIDA A 0
    GPIO_PORTD_AHB_AFSEL_R = 0x01; //FUNCION ALTERNA EN BIT 1 0000 0001
    GPIO_PORTD_AHB_PCTL_R = 0x00000003; //DIRIGIDO A T0CCP0

    TIMER0_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
    TIMER0_CFG_R= 0X00000004; //CONFIGURAR PARA 16 BITS
    TIMER0_TAMR_R= 0X0000000A; //CONFIGURAR PARA MODO PWM, MODO PERIODICO CUENTA HACIA ABAJO
    TIMER0_TBMR_R= 0X0000000A; //CONFIGURAR PARA MODO PWM, MODO PERIODICO CUENTA HACIA ABAJO
    //Para configurara el pmw se tomaron en cuenta las siguients consideraciones
    //1/20ms=50 hz, esa es la frecuencia que nececitamos
    // 16000000/50 = 320000 = 4e200
    //Con ese valor Ya tengo la señal de 20 ms que me pide el fabricante pero como hago para girarlo
    //me dicen que para que gire tengo que mandarle un pulso con cierta duracion
    //con 1ms gira completamente a la izquierda
    //con 1.5ms gira al centro
    //con 2ms se va completamente a la derecha
    //Sacando los porcentajes de la señal de 20 ms
    //1ms = 5% de 20 ms
    //1.5ms = 7.5% de 20 ms
    //2 ms = 10% de 20 ms
    //Para calcular el valor del match tenemos que sacarlo de su valor
    //320*0.1=32000 = 10%
    //320*0.075 =24000 = 7.5%
    //320*0.05 =16000 = 5%
    // En hexacecimal
    //16000 = 3e80
    //24000 = 5DC0
    // 32000 = 7D00
    TIMER0_TAILR_R= 0xe200; //
    TIMER0_TAMATCHR_R =0x3e80; // 100 %
    TIMER0_TAPR_R= 0X04; // preescalador
    TIMER0_CTL_R |= 0X00000041; //HABILITA TIMER A
}
void inicioDispositivosAnalogicos()
{
    //Habilito los puertos E
    //voy a usar desde E0-E5
    SYSCTL_RCGCGPIO_R |=  SYSCTL_RCGCGPIO_R4;
    //reloj para el adc
    SYSCTL_RCGCADC_R  |= SYSCTL_RCGCADC_R0;
    ValorADC=65565; //tiempo para que el reloj llegue a los modulos
    //EL PLL es necesario activarlo, asi lo pide TexasInstruments
    SYSCTL_PLLFREQ1_R = ValPLLFREQ1;
    SYSCTL_PLLFREQ0_R = ValPLLFREQ0;
    while((SYSCTL_PLLSTAT_R&0x01)==0);
    //Esto no se porque se repite
    SYSCTL_RCGCGPIO_R  |= SYSCTL_RCGCGPIO_R4;
    SYSCTL_RCGCADC_R  |= SYSCTL_RCGCADC_R0;
    ValorADC=65565; //tiempo para que el reloj llegue a los modulos

    //inicializar PE.0 para que sea AIN3
    //inicializar PE.1 para que sea AIN2
    //inicializar PE.2 para que sea AIN1
    //inicializar PE.3 para que sea AIN0
    //inicializar PE.4 para que sea AIN9
    //inicializar PE.5 para que sea AIN8

    GPIO_PORTE_AHB_AMSEL_R |=0X3f;  //habilita modulo analogico de E0-E5 0011 1111
    GPIO_PORTE_AHB_DEN_R &= ~0X3f;  //desahabilita buffer digital

    // inicializar adc
    ADC0_SSPRI_R=0X00003210; //se queda con las mismas prioridades p1099
    //ADC0_CC_R=0X170; //RELOJ DEL ADC EL VCO del PLL /24
    ADC0_PC_R=0x07;//1Ms/S velocidad de la muestra  p1159
    //ADC0_ACTSS_R   &= ~8;      //deshabilitar SS3 (o todos los secuenciadores)
    ADC0_ACTSS_R   = 0;        //durante la configuración  p1077
    //ADC0_EMUX_R   &= ~0XF000;   //conversión por software para todos los secuenciadores
    ADC0_EMUX_R   = 0X0000;   //inicio de la conversión por software con bit SSn en el ADCPSSI, p1091
    //aqui establece el secuenciador coneccion con el pin AIN, para hacer sus conversiones,
    //si eemux3 es 0, el valor del bit corresponde al valor de ainx,[0-15], For example, if the
    //MUX3 field is 0x0, AIN0 is selected.
    //si eemux3 es 1, el valor del bit corresponde al valor de ainx [16-19]
    //For example, if the
    //MUX3 field is 0x0, AIN16 is selected.
    ADC0_SSEMUX0_R  = 0;      //una vez establecido, el conteo, hacia arriba
    ADC0_SSMUX0_R  = 0;          //ain0 seleccionado
    ADC0_SSEMUX1_R  = 0;        //una vez establecido, el conteo, hacia arriba
    ADC0_SSMUX1_R  = 1;         //ain1 seleccionado
    ADC0_SSEMUX2_R  = 0;        //una vez establecido, el conteo, hacia arriba
    ADC0_SSMUX2_R  = 2;         //ain2 seleccionado
    ADC0_SSEMUX3_R  = 0;        //una vez establecido, el conteo, hacia arriba
    ADC0_SSMUX3_R  = 3;         //ain3 seleccionado
    ADC0_SSCTL0_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
    ADC0_SSCTL1_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
    ADC0_SSCTL2_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
    ADC0_SSCTL3_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
    //ADC0_SSCTL2_R   |= 0x0a;       //tomar lectura del sensor de temperatura
    ADC0_ACTSS_R   |= 0X0f;        //habilitar secuenciador 0 del ADC0  p1077
    SYSCTL_PLLFREQ0_R=0; //DESHABILITA EL PLL
    SYSCTL_PLLFREQ1_R=0;
}
void LeerPuertosAnalogicos()
{
    /*uint32_t lm35=0;
    uint32_t Fotoresistencia=0;
    uint32_t AcelerometroX=0;
    uint32_t AcelerometroY=0;
    */
    ADC0_PSSI_R   |= 0x0f;               //EMPEZAR SECUENCIA DE CONVERSION de todos los secuenciadores p1103
    while((ADC0_RIS_R & 0x0f == 0));  //espera por conversión completa  p1079
    Fotoresistencia=ADC0_SSFIFO0_R;
    lm35= ADC0_SSFIFO1_R;
    AcelerometroX=ADC0_SSFIFO2_R;
    AcelerometroY=ADC0_SSFIFO3_R;
    ADC0_ISC_R   = 0x0f;
}
void prenderLuces()
{
    GPIO_PORTP_DATA_R = 0X01;
}
void apagarLuces()
{
    GPIO_PORTP_DATA_R = 0X00;
}

void vigilarMovimiento()
{


        //EscribirDisplay("    Se Roban       la moto");
        if(GPIO_PORTP_DATA_R == 0x02){
        prenderLuces();
        SysCtlDelay(4800);
        apagarLuces();
        SysCtlDelay(4800);}



}
void girarServoIzquierda()
{
    //TIMER0_CTL_R |= 0X00000041; //HABILITA TIMER A
    SysCtlDelay(10000);
    TIMER0_TAMATCHR_R=0x3e80;
    SysCtlDelay(10000);
    //TIMER0_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
}
void girarServoDerecha()
{
    //TIMER0_CTL_R |= 0X00000041; //HABILITA TIMER A
    SysCtlDelay(10000);
    TIMER0_TAMATCHR_R=0x7D00;
    SysCtlDelay(10000);
    //TIMER0_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
}


void AbrirCajuela()
{
    EscribirDisplay("    Codigo");
    CaracterisarTeclado();

}
void PromediarValoresAnalogicos()
{
   /* int promediolm35=0;
    int promedioFotoresistencia=0;
    int promedioAcelerometroX=0;
    int promedioAcelerometroY=0;
    uint32_t lm35=0;
    uint32_t Fotoresistencia=0;
    uint32_t AcelerometroX=0;
    uint32_t AcelerometroY=0;*/
    int i=0;
    for(i=0;i<10;i++)
    {
        LeerPuertosAnalogicos();
        promedioAcelerometroX+=AcelerometroX;
        promedioAcelerometroY+=AcelerometroY;
    }
    promedioAcelerometroY=promedioAcelerometroY/10;
    promedioAcelerometroX= promedioAcelerometroX/10;

}
void alarma()
{

    EscribirDisplay("Protegido");

    vigilarMovimiento();
    //PromediarValoresAnalogicos();
    LeerPuertosAnalogicos();
    /*if(AcelerometroY>2000 | AcelerometroY<1300)
    {
        EscribirDisplay("    Se Roban       la moto");
        while(GPIO_PORTB_AHB_DATA_R  != 0x03){
        prenderLuces();
        SysCtlDelay(4800);
        apagarLuces();
        SysCtlDelay(4800);
        }
    }*/
    if(AcelerometroX>400 | AcelerometroX<200){

       //EscribirDisplay("    Se Roban       la moto");

            prenderLuces();
            SysCtlDelay(4800);
            apagarLuces();
            SysCtlDelay(4800);
    }
}
void tiempo(){
    int i=0;
    while(i<1500000){i++;}



}
void LeerPosicionColumna(int Columna)
{
    //while(1){
    int Dato="";
    Dato = GPIO_PORTH_AHB_DATA_R;
    switch(Columna) {
    case 0:
        if(Dato == 1){//ES 1
            Codigo='1';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 2){//ES 4
            Codigo='4';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 4){//ES 7
            Codigo='7';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 8){//ES *
            Codigo='*';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        break;
    case 1:
            if(Dato == 1){//ES 1
                Codigo='2';
                VerificarCodigo(Codigo);
                c++;
                tiempo();
            }
            if(Dato == 2){//ES 4
                Codigo='5';
                VerificarCodigo(Codigo);
                c++;
                tiempo();
            }
            if(Dato == 4){//ES 7
                Codigo='8';
                VerificarCodigo(Codigo);
                c++;
                tiempo();
            }
            if(Dato == 8){//ES *
                Codigo='0';
                VerificarCodigo(Codigo);
                c++;
                tiempo();
            }
            break;
    case 2:
        if(Dato == 1){//ES 1
            Codigo='3';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 2){//ES 4
            Codigo='6';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 4){//ES 7
            Codigo='9';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 8){//ES *
            Codigo='#';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        break;
    case 3:
        if(Dato == 1){//ES 1
            Codigo='A';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 2){//ES 4
            Codigo='B';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 4){//ES 7
            Codigo='C';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        if(Dato == 8){//ES *
            Codigo='D';
            VerificarCodigo(Codigo);
            c++;
            tiempo();
        }
        break;
     default: Columna=0;
    }

    //}
}
void VerificarCodigo(char dato)
{
char Codigo1[]="5712";
//int i=0;

    if(dato== Codigo1[c]){
    r++;}
   // i++;


  if(r==4)
  {
      GPIO_PORTK_DATA_R = 0X01;
      EscribirComando();
      EscribirDisplay("Abierta");
      girarServoIzquierda();

      SysCtlDelay(10000);
      girarServoDerecha();
      c=-1;
      r=0;
  }
  if(c==4)
    {
        GPIO_PORTK_DATA_R = 0X01;
        EscribirComando();
        EscribirDisplay("Mal");
        SysCtlDelay(10000);
        girarServoDerecha();
        girarServoIzquierda();
        c=-1;
        r=0;
    }
}
void TecladoIni()
{
    SYSCTL_RCGCGPIO_R  |= SYSCTL_RCGCGPIO_R7 |SYSCTL_RCGCGPIO_R14;
    //Configuracion puerto H
    GPIO_PORTH_AHB_DATA_R = 0X00; //PREPARA PUERTO n LEDS 0 Y 1
    GPIO_PORTH_AHB_DEN_R = 0X0f; //Habilita los bits 0000 1111
    GPIO_PORTH_AHB_DIR_R = 0X00; //En 0 los bits son de entrada (input)

    //Configuracion puerto Q
    GPIO_PORTQ_DATA_R = 0X00; //PREPARA PUERTO n LEDS 0 Y 1
    GPIO_PORTQ_DEN_R = 0X0f; //Habilita los bits 0000 1111
    GPIO_PORTQ_DIR_R = 0X0f; //En 1 los bits son de salida
}
void CaracterisarTeclado()
{
    //while(1)
        //{
            GPIO_PORTQ_DATA_R = 0X01;
            LeerPosicionColumna(0);
            GPIO_PORTQ_DATA_R = 0X00;
            GPIO_PORTQ_DATA_R = 0X02;
            LeerPosicionColumna(1);
            GPIO_PORTQ_DATA_R = 0X00;
            GPIO_PORTQ_DATA_R = 0X04;
            LeerPosicionColumna(2);
            GPIO_PORTQ_DATA_R = 0X00;
            GPIO_PORTQ_DATA_R = 0X08;
            LeerPosicionColumna(3);
            GPIO_PORTQ_DATA_R = 0X00;
        //}
}
int main(void)
{
    inicioDispositivosAnalogicos();
    inicioServo();
    inicioLucesYMov();
    configuracionPuertos();
    clearPorts();
    inicioDisplay();
    TecladoIni();

    //LeerPuertosAnalogicos()
    //prenderLuces()
    //apagarLuces()
    //vigilarMovimiento()
    //girarServoIzquierda()
    //girarServoDerecha()
    while(1)
    {
    if(GPIO_PORTB_AHB_DATA_R  == 0x01)
    {
        alarma();
    }
    if(GPIO_PORTB_AHB_DATA_R  == 0x00)
    {
        AbrirCajuela();
    }
    }
}
