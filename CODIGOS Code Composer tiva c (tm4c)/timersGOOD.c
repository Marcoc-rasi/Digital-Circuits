#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h"








void
complementa0(void)
{
    GPIO_PORTN_DATA_R ^= 0x01;
}

void
complementa1(void)
{
    GPIO_PORTN_DATA_R ^= 0x02;
}

/*
//*********************************
//**CONTADOR PARA LA FUNCION DE CUENTA POR FLANCO
void

Timer03AIntHandler(void)
{
    //LIMPIA BANDERA
    uint32_t ui32CLRBAN;
    TIMER3_ICR_R= 0X00000004 ; //LIMPIA BANDERA DE EVENTO DE CAPTURA
     ui32Cuenta++;


}

*/
void Timer03AIntHandler(void)
{
    //LIMPIA BANDERA
    uint32_t ui32CLRBAN;
    TIMER3_ICR_R= 0X00000001 ; //LIMPIA BANDERA DE TIMER3
    // llama a la función complemento de leds.
    //
    complementa0();
}

void Timer03BIntHandler(void)
{
    //LIMPIA BANDERA
    uint32_t ui32CLRBAN;
    TIMER3_ICR_R= 0X00000001 ; //LIMPIA BANDERA DE TIMER3
    // llama a la función complemento de leds.
    //
    complementa1();
}

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
         TIMER3_TAILR_R= 0X00FFFF; // VALOR DE RECARGA
         TIMER3_TAPR_R= 0X0F; // 16 MHZ /16 =1MHz
         TIMER3_ICR_R= 0X00000001 ; //LIMPIA PISOBLE BANDERA PENDIENTE DE TIMER3
         TIMER3_IMR_R |= 0X00000001; //ACTIVA INTRRUPCION DE TIMEOUT
         NVIC_EN1_R= 1<<(35-32); //HABILITA LA INTERRUPCION DE  TIMER3
         TIMER3_CTL_R |= 0X00000001; //HABILITA TIMERA EN LA CONFIGURACION


         //
         // habilita el bit 0 como digital
         // configura como salida
         //
         GPIO_PORTN_DIR_R = 0x01;
         GPIO_PORTN_DEN_R = 0x01;
         GPIO_PORTN_DATA_R = 0x00;

        // IntMasterEnable();

         while(1);

}
//*******************************************************************************************

*/


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
//************************************************************
// CONFIGURACIÓN PARA CAPTURA EN LA ENTRADA DEL TIMER 3A
 main(void) {

     uint32_t ui32Loop;
     uint32_t ui32Cuenta=0;
     //habilita PORTN
      SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R12 |SYSCTL_RCGCGPIO_R3; //HABILITA PORTN Y PORTD

         SYSCTL_RCGCTIMER_R |= 0X08; //HABILITA TIMER 3

         //retardo para que el reloj alcance el PORTN  PORTD Y TIMER 3
         ui32Loop = SYSCTL_RCGCGPIO_R;

         //CONFIGURAR LA TERMINAL DE ENTRADA DEL MODULO T3CCP0
         //CORRESPONDIENTE A PD4
               // habilita el bit 4 como digital
               // configura como entrada
               //
               GPIO_PORTD_AHB_DIR_R &= ~(0x10); //bit 4 entrada
               GPIO_PORTD_AHB_DEN_R |= 0x10; //BIT 4 DIGITAL
               GPIO_PORTD_AHB_DATA_R = 0x00; //RESTO DE SALIDAS A 0
               GPIO_PORTD_AHB_AFSEL_R = 0x10; //FUNCION ALTERNA EN BIT 4
               GPIO_PORTD_AHB_PCTL_R = 0x00030000; //DIRIGIDO A T3CCP0


         TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
         TIMER3_CFG_R= 0X00000004; //CONFIGURAR PARA 32 BITS
         TIMER3_TAMR_R= 0X00000007; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ABAJO MODO CAPTURA
        // TIMER3_TAMR_R= 0X00000017; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ARRIBA MODO CAPTURA
         TIMER3_CTL_R &=0XFFFFFFF3; // EVENTO FLANCO DE SUBIDA (CONSIDERANDO CONDICIONES INICIALES DE REGISTRO)
         TIMER3_ICR_R= 0X00000004 ; //LIMPIA POSIBLE BANDERA PENDIENTE DE CAPTURE
         TIMER3_IMR_R |= 0X00000004; //ACTIVA INTERRUPCION DE CAPTURA
         NVIC_EN1_R= 1<<(35-32); //HABILITA LA INTERRUPCION DE  TIMER 3
         TIMER3_CTL_R |= 0X00000001; //HABILITA TIMER EN LA CONFIGURACION




        // IntMasterEnable();

         while(1);

}

 */


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
               GPIO_PORTD_AHB_AFSEL_R = 0x10; //FUNCION ALTERNA EN BIT 4
               GPIO_PORTD_AHB_PCTL_R = 0x00030000; //DIRIGIDO A T3CCP0


         TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
         TIMER3_CFG_R= 0X00000004; //CONFIGURAR PARA 16 BITS
         TIMER3_TAMR_R= 0X0000000A; //CONFIGURAR PARA MODO PWM, MODO PERIODICO CUENTA HACIA ABAJO

         TIMER3_TAILR_R= 16000; // VALOR DE RECARGA 1 KHz
         TIMER3_TAMATCHR_R =8000; // 50 %
         TIMER3_TAPR_R= 0X00; // RELOJ 16 MHZ
         TIMER3_CTL_R |= 0X00000001; //HABILITA TIMER A


         while(1);

}
//*******************************************************************************************

*/


/*

//*********************************************
// CONFIGURACIÓN PARA TIMER DE 16 BITS, MODO COMPARACIÓN
 main(void) {

     uint32_t ui32Loop;
     //habilita PORTN
      SYSCTL_RCGCGPIO_R = SYSCTL_RCGCGPIO_R12 | SYSCTL_RCGCGPIO_R3; //HABILITA PORTN Y PORTD

         SYSCTL_RCGCTIMER_R |= 0X08; //HABILITA TIMER 3

         //retardo para que el reloj alcance el PORTN Y TIMER 3
         ui32Loop = SYSCTL_RCGCGPIO_R;

         //
                 // habilita el bit 0 como digital
                 // configura como salida
                 //
                 GPIO_PORTN_DIR_R = 0x01;
                 GPIO_PORTN_DEN_R = 0x01;
                 GPIO_PORTN_DATA_R = 0x00;

                 GPIO_PORTD_AHB_DEN_R |= 0x10; //BIT 4 DIGITAL
                 GPIO_PORTD_AHB_DIR_R |= 0x10; //bit 4 SALIDA
                 GPIO_PORTD_AHB_DATA_R = 0x00; // SALIDA A 0
                 GPIO_PORTD_AHB_AFSEL_R = 0x10; //FUNCION ALTERNA EN BIT 4
                 GPIO_PORTD_AHB_PCTL_R = 0x00030000; //DIRIGIDO A T3CCP0


         TIMER3_CTL_R=0X00000000; //DESHABILITA TIMER EN LA CONFIGURACION
         TIMER3_CFG_R= 0X00000000; //CONFIGURAR PARA 16 BITS
         TIMER3_TAMR_R= 0X0002002; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ABAJO 2 TOOGLE ON MATCH
         //TIMER3_TAMR_R= 0X00002012; //CONFIGURAR PARA MODO PERIODICO CUENTA HACIA ARRIBA
         TIMER3_TAILR_R= 0X00FFFF; // VALOR DE RECARGA
         TIMER3_TAPR_R= 0X00; // 16 MHZ /16 =1MHz
         TIMER3_TAMATCHR_R =0X8000; // COMPARACION A LA MITAD DE LA CUENTA
         //TIMER3_ICR_R= 0X00000010 ; //LIMPIA POSIBLE BANDERA PENDIENTE DE CCOMPARE
         TIMER3_CTL_R |= 0X00000001; //HABILITA TIMERA EN LA CONFIGURACION

         while(1);


        // IntMasterEnable();

         while(1);

}
//*******************************************************************************************

*/
