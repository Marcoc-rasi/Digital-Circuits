#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"




#define ValPLLFREQ0 0X00800060;
#define ValPLLFREQ1 0X00000004;

    uint32_t  ValorADC;
    uint32_t ui32Loop;
    float ValorADCf;

int main(void)
{

SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R12 |SYSCTL_RCGCGPIO_R3 | SYSCTL_RCGCGPIO_R4; //HAB PORTN,PORTD,PORTE
       //         0001 0000 0000 0000    0000 0000 0000 1000  0000 0000 0001 0000 = 0001 0000 0001 1000

            SYSCTL_RCGCTIMER_R |= 0X08; //HABILITA TIMER 3

                   SYSCTL_RCGCADC_R  |= SYSCTL_RCGCADC_R0;   //reloj para el adc

                   ValorADC=65565; //tiempo para que el reloj llegue a los modulos


            //CONFIGURAR LA TERMINAL DEL MODULO T3CCP0  Y T3CCP1
            //CORRESPONDIENTE A PD4(T3CCP0) Y PD5(T3CCP1)
                  // habilita el bit 4 como digital
                  // configura como salida
                  //

                 GPIO_PORTD_AHB_DEN_R |= 0x30; //BIT 4 Y 5 DIGITAL   0011 0000
                  GPIO_PORTD_AHB_DIR_R |= 0x30; //bit 4 Y 5 SALIDA
                  GPIO_PORTD_AHB_DATA_R = 0x00; // SALIDA A 0
                  GPIO_PORTD_AHB_AFSEL_R = 0x30; //FUNCION ALTERNA EN BIT 4 0011 0000
                  GPIO_PORTD_AHB_PCTL_R = 0x00330000; //DIRIGIDO A T3CCP0

        //0000 0000 0011 0011 0000 0000 0000 0000 PCTL


            TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
            TIMER3_CFG_R= 0X00000004; //CONFIGURAR PARA 16 BITS
            TIMER3_TAMR_R= 0X0000000A; //CONFIGURAR PARA MODO PWM, MODO PERIODICO CUENTA HACIA ABAJO
            TIMER3_TBMR_R= 0X0000000A; //CONFIGURAR PARA MODO PWM, MODO PERIODICO CUENTA HACIA ABAJO


    //para el servomotor el valor de ilr debe ser 320,000 hex=4e200
                // 0xe200 ->ilr
                //0x04  -> pr
            //   04 e200
            //   pr  ilr

            // 16000 - 20000 24000- 28000 32000
            //   izq     45g  cen    135g   der
            //16000 = 0x3e80
            // 32000 = 0x7d00
             //  280000 - 304000

            TIMER3_TAILR_R= 0xfff; // VALOR DE RECARGA 3.906 KHz
            TIMER3_TBILR_R= 0xfff; // VALOR DE RECARGA 3.906 KHz
            TIMER3_TAMATCHR_R =0x3ff; // 50 %
            TIMER3_TBMATCHR_R =0x3ff; // 50 %
                //tapmatch
            TIMER3_TAPR_R= 0X00; // RELOJ 16 MHZ
            TIMER3_TBPR_R= 0X00; // RELOJ 16 MHZ
            TIMER3_CTL_R |= 0X00004141; //HABILITA TIMER A Y TIMER B
       //    xxxxxxxxx pol 5 4 3 2  1  EN
       //       0       1   0 0 0 0 0  1
         //   TIMER3_TAILR_R= 16000; // VALOR DE RECARGA 1 KHz
          //  TIMER3_TAMATCHR_R =15800; // 75 %
          //  TIMER3_TAPR_R= 0X00; // RELOJ 16 MHZ
          //  TIMER3_CTL_R |= 0X00000001; //HABILITA TIMER A


    //esto se usa en conjunto con la línea 50 si es que se quiere usar el VCO como fuente del ADC
    //SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
      // SYSCTL_CFG_VCO_480), 120000000);


    SYSCTL_PLLFREQ1_R = ValPLLFREQ1;
    SYSCTL_PLLFREQ0_R = ValPLLFREQ0;
    while((SYSCTL_PLLSTAT_R&0x01)==0);


 //inicializar PE.4 para que sea AIN9
                                                          //          PE3         PE4      PE4 Y PE3
     GPIO_PORTE_AHB_AMSEL_R |=0X18;  //habilita modulo analogico  0000 1000  / 0001 0000/ 0001 1000
     GPIO_PORTE_AHB_DEN_R &= ~0X18;  //desahabilita buffer digital



     GPIO_PORTN_DATA_R = 0X00; //PREPARA PUERTO n LEDS 0 Y 1
     GPIO_PORTN_DEN_R = 0X03; //PARA SEÑALIZAR LA
     GPIO_PORTN_DIR_R = 0X03; //ENTRADA DE VOLTAJE



// inicializar adc
     ADC0_SSPRI_R=0X00003210; //se queda con las mismas prioridades p1099
     //ADC0_CC_R=0X170; //RELOJ DEL ADC EL VCO del PLL /24
     ADC0_PC_R=0x07;//1Ms/S velocidad de la muestra  p1159
    //ADC0_ACTSS_R   &= ~8;      //deshabilitar SS3 (o todos los secuenciadores)
     ADC0_ACTSS_R   = 0;        //durante la configuración  p1077
    //ADC0_EMUX_R   &= ~0XF000;   //conversión por software para todos los secuenciadores
    ADC0_EMUX_R   = 0X0000;   //inicio de la conversión por software con bit SSn en el ADCPSSI, p1091
    ADC0_SSEMUX3_R  = 0; //0001        //obtener entrada del primer grupo de 16 canales (0 al 15) p1146
    ADC0_SSMUX3_R  = 9; //0000  0000 1001       //obtener entrada del canal 0 p1141  0000 1001
    
    ADC0_SSEMUX2_R  = 0; //0001        //obtener entrada del primer grupo de 16 canales (0 al 15) p1146
    ADC0_SSMUX2_R  = 0; //0000  0000 1001       //obtener entrada del canal 0 p1141  0000 1001
    
    ADC0_SSCTL3_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
    ADC0_SSCTL2_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
  
   //SEC3  XXXX XXXX XXXX XXXX XXXX XXXX XXXX T IE LC D
   //                                         0  0  1 0    
   //SEC2  XXXX XXXX XXXX XXXX  T IE LC D   T IE LC D   T IE LC D   T IE LC D  
    //                          X  X  X  X  X  X  X  X   X  X X  X0  0  0  0 0 
    
    //ADC0_SSCTL3_R   |= 0x0a;       //tomar lectura del sensor de temperatura
    ADC0_ACTSS_R   |= 0X0C;        //habilitar secuenciador 3 del ADC0  p1077  XXXX 1100
    SYSCTL_PLLFREQ0_R=0; //DESHABILITA EL PLL
    SYSCTL_PLLFREQ1_R=0;


    while(1)
              {

       // ADC0_SSEMUX3_R  = 0;         //obtener entrada del primer grupo de 16 canales (0 al 15) p1146
         //  ADC0_SSMUX3_R  = 9;

     ADC0_PSSI_R   |= 8;               //EMPEZAR SECUENCIA DE CONVERSION 3 p1103  XXXX 0000
     while((ADC0_RIS_R & 8 == 0));  //espera por conversión completa  p1079
     ValorADC  = ADC0_SSFIFO3_R ;       //leer el resultado de la conversion p1118

     TIMER3_TAMATCHR_R= ValorADC;



   //  TIMER3_TAMATCHR_R= ADC0_SSFIFO3_R;


    ADC0_ISC_R   = 8;                      //limpiar bandera


   // ADC0_SSEMUX3_R  = 0;         //obtener entrada del primer grupo de 16 canales (0 al 15) p1146
     //        ADC0_SSMUX3_R  = 0;

       ADC0_PSSI_R   |= 4;               //EMPEZAR SECUENCIA DE CONVERSION 3 p1103  XXXX 0100
       while((ADC0_RIS_R & 4 == 0));  //espera por conversión completa  p1079       XXXX 0000
       ValorADC  = ADC0_SSFIFO2_R ;       //leer el resultado de la conversion p1118

       TIMER3_TBMATCHR_R= ValorADC;



     //  TIMER3_TAMATCHR_R= ADC0_SSFIFO3_R;


      ADC0_ISC_R   = 4;                      //limpiar bandera SEC 2

               }



            while(1);


    }


//seguir los pasos de configuración
//en la sección 15.4.1 de la pagina 1072 y la 15.4.2
//de la pag 1073.
//poner especial atención en el punto 15.3.2.7 Module Clocking

//para generar el reloj de la conversion se usan en conjunto las lineas
//20 a 22 y la 50 o las lineas 25 a 27  y 61 a 62. solo se usa alguno
//de esos grupos y no los dos
//este programa enciende los leds de la tarjeta comforme varia el voltaje
//del potenciometro alambrado a AIN0 (PE3), pero
//tiene un problema, no apaga el led 1 completamente.
//Modificarlo para que se cumplan estas condiones:
//                 led1  led0
// 0.0<=Vin<0.5     0     0
// 0.5<=Vin<1.7     0     1
// 1.7<=Vin<2.2     1     0
// Vin>=2.2         0     1


/*
//*********************************************
// CONFIGURACIÓN PARA TIMER DE 16 BITS
 main(void) {

     uint32_t ui32Loop;
     //habilita PORTN
      SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R12;

         SYSCTL_RCGCTIMER_R |= 0X08; //HABILITA TIMER 3

         //retardo para que el reloj alcance el PORTN Y TIMER 3
         ui32Loop = SYSCTL_RCGCGPIO_R;
         TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
         TIMER3_CFG_R= 0X00000004; //CONFIGURAR PARA 16 BITS
         TIMER3_TAMR_R= 0X00000002; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ABAJO
         //TIMER3_TAMR_R= 0X00000012; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ARRIBA
         TIMER3_TAILR_R= 0X001200; // VALOR DE RECARGA
         TIMER3_TAPR_R= 0X7a; // 16 MHZ /16 =1MHz
         TIMER3_ICR_R= 0X00000001 ; //LIMPIA PISOBLE BANDERA PENDIENTE DE TIMER3
         //TIMER3_IMR_R |= 0X00000001; //ACTIVA INTRRUPCION DE TIMEOUT
         //NVIC_EN1_R= 1<<(35-32); //HABILITA LA INTERRUPCION DE  TIMER3
         TIMER3_CTL_R |= 0X00000001; //HABILITA TIMERA EN LA CONFIGURACION


         //
         // habilita el bit 0 como digital
         // configura como salida
         //
         GPIO_PORTN_DIR_R = 0x01;
         GPIO_PORTN_DEN_R = 0x01;
         GPIO_PORTN_DATA_R = 0x00;

        // IntMasterEnable();

         while(1)
               {
              while((TIMER3_RIS_R&0X01)==0);
              TIMER3_ICR_R= 0X00000001;
              GPIO_PORTN_DATA_R ^= 0x01;
               }

         while(1);

}
//*******************************************************************************************

*/

/*
//*********************************************
// CONFIGURACIÓN PARA TIMER DE 32 BITS
 main(void) {

     uint32_t ui32Loop;
     //habilita PORTN
      SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R12;

         SYSCTL_RCGCTIMER_R |= 0X08; //HABILITA TIMER 3   0000 1000

         //retardo para que el reloj alcance el PORTN Y TIMER 3
         ui32Loop = SYSCTL_RCGCGPIO_R;
         TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
         TIMER3_CFG_R= 0X00000000; //CONFIGURAR PARA 32 BITS
         //TIMER3_TAMR_R= 0X00000002; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ABAJO
         TIMER3_TAMR_R= 0X00000012; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ARRIBA
         TIMER3_TAILR_R= 0X00FFFFFF; // VALOR DE RECARGA
         TIMER3_TAPR_R= 0X00; // SOLO PARA MODOS DE 16 BITS
         TIMER3_ICR_R= 0X00000001 ; //LIMPIA PISOBLE BANDERA PENDIENTE DE TIMER3
         //TIMER3_IMR_R |= 0X00000000; //ACTIVA INTRRUPCION DE TIMEOUT
        // NVIC_EN1_R= 1<<(35-32); //HABILITA LA INTERRUPCION DE  TIMER3

         GPIO_PORTN_DIR_R = 0x01;
         GPIO_PORTN_DEN_R = 0x01;
         GPIO_PORTN_DATA_R = 0x00;

         TIMER3_CTL_R |= 0X00000001; //HABILITA TIMER EN LA CONFIGURACION



         //
         // habilita el bit 0 como digital
         // configura como salida
         //


        // IntMasterEnable();

          while(1)
          {
         while((TIMER3_RIS_R&0X01)==0);
         TIMER3_ICR_R= 0X00000001;
         GPIO_PORTN_DATA_R ^= 0x01;
          }

         while(1);

}
//*******************************************************************************************

/*
//*********************************************
// CONFIGURACIÓN PARA PWM
 main(void) {

     uint32_t ui32Loop;
     //habilita PORTN Y PORTD

      SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R12 |SYSCTL_RCGCGPIO_R3; //HABILITA PORTN Y PORTD

         SYSCTL_RCGCTIMER_R |= 0X08; //HABILITA TIMER 3


         //retardo para que el reloj alcance el PORTN, PORTD  Y TIMER 3
         ui32Loop = SYSCTL_RCGCGPIO_R;

         //CONFIGURAR LA TERMINAL DEL MODULO T3CCP0
         //CORRESPONDIENTE A PD4
               // habilita el bit 4 como digital
               // configura como salida
               //

              GPIO_PORTD_AHB_DEN_R |= 0x10; //BIT 4 DIGITAL
               GPIO_PORTD_AHB_DIR_R |= 0x10; //bit 4 SALIDA
               GPIO_PORTD_AHB_DATA_R = 0x00; // SALIDA A 0
               GPIO_PORTD_AHB_AFSEL_R = 0x10; //FUNCION ALTERNA EN BIT 4 0001 0000
               GPIO_PORTD_AHB_PCTL_R = 0x00030000; //DIRIGIDO A T3CCP0


         TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
         TIMER3_CFG_R= 0X00000004; //CONFIGURAR PARA 16 BITS
         TIMER3_TAMR_R= 0X0000000A; //CONFIGURAR PARA MODO PWM, MODO PERIODICO CUENTA HACIA ABAJO

 //para el servomotor el valor de ilr debe ser 320,000 hex=4e200
             // 0xe200 ->ilr
             //0x04  -> pr
         //   04 e200
         //   pr  ilr

         // 16000 - 20000 24000- 28000 32000
         //   izq     45g  cen    135g   der
         //16000 = 0x3e80
         // 32000 = 0x7d00
          //  280000 - 304000

         TIMER3_TAILR_R= 0xe200; // VALOR DE RECARGA 1 KHz
         TIMER3_TAMATCHR_R =0x3e00; // 75 %
             //tapmatch
         TIMER3_TAPR_R= 0X04; // RELOJ 16 MHZ
         TIMER3_CTL_R |= 0X00000041; //HABILITA TIMER A
    //    xxxxxxxxx pol 5 4 3 2  1  EN
    //       0       1   0 0 0 0 0  1
      //   TIMER3_TAILR_R= 16000; // VALOR DE RECARGA 1 KHz
       //  TIMER3_TAMATCHR_R =15800; // 75 %
       //  TIMER3_TAPR_R= 0X00; // RELOJ 16 MHZ
       //  TIMER3_CTL_R |= 0X00000001; //HABILITA TIMER A


         while(1);

}
//*******************************************************************************************
 *
 */
 //*/
