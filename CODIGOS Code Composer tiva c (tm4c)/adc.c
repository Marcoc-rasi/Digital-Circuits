// **************************************************
// no modificar nada ni agregar nada hasta no haber
// leido la introducción porque algunas anotaciones se refieren
// especificamente a números de linea. Ver la nota la final del código.
//**********************************************************


#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include   "inc/tm4c1294ncpdt.h"

#define ValPLLFREQ0 0X00800060;
#define ValPLLFREQ1 0X00000004;

    uint32_t  ValorADC;
    float ValorADCf;
int main(void)
{
    //esto se usa en conjunto con la línea 50 si es que se quiere usar el VCO como fuente del ADC
    //SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
      // SYSCTL_CFG_VCO_480), 120000000);


    SYSCTL_PLLFREQ1_R = ValPLLFREQ1;
    SYSCTL_PLLFREQ0_R = ValPLLFREQ0;
    while((SYSCTL_PLLSTAT_R&0x01)==0);


//habilitar reloj para los puertos utilizados
     SYSCTL_RCGCGPIO_R  |= SYSCTL_RCGCGPIO_R4 |SYSCTL_RCGCGPIO_R12;   //RELOJ PARA PUERTO E Y PUERTO N
        SYSCTL_RCGCADC_R  |= SYSCTL_RCGCADC_R0;   //reloj para el adc
 ValorADC=65565; //tiempo para que el reloj llegue a los modulos

 //inicializar PE.3 para que sea AIN0

     GPIO_PORTE_AHB_AMSEL_R |=0X10;  //habilita modulo analogico  0000 1000   0001 0000
     GPIO_PORTE_AHB_DEN_R &= ~0X10;  //desahabilita buffer digital



     GPIO_PORTN_DATA_R = 0X0; //PREPARA PUERTO n LEDS 0 Y 1
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
    ADC0_SSEMUX3_R  = 0;         //obtener entrada del primer grupo de 16 canales (0 al 15) p1146
    ADC0_SSMUX3_R  = 9;         //obtener entrada del canal 0 p1141                                 0000 1001
    ADC0_SSCTL3_R   |= 2;       ////poner bandera para terminar a la 1a muestra p1142  0010
    //ADC0_SSCTL3_R   |= 0x0a;       //tomar lectura del sensor de temperatura
    ADC0_ACTSS_R   |= 8;        //habilitar secuenciador 3 del ADC0  p1077
    SYSCTL_PLLFREQ0_R=0; //DESHABILITA EL PLL
    SYSCTL_PLLFREQ1_R=0;
    while(1)
              {
     ADC0_PSSI_R   |= 8;               //EMPEZAR SECUENCIA DE CONVERSION 3 p1103
     while((ADC0_RIS_R & 8 == 0));  //espera por conversión completa  p1079
     ValorADC  = ADC0_SSFIFO3_R ;       //leer el resultado de la conversion p1118


     if(ValorADC<0x200)
          {GPIO_PORTN_DATA_R=0X00;}
     if(ValorADC>0x400)
     {GPIO_PORTN_DATA_R=0X01;}
     if(ValorADC>0x800)
          {GPIO_PORTN_DATA_R=0X02;}
     if(ValorADC>0xD00)
          {GPIO_PORTN_DATA_R=0X03;}

         ValorADCf=(1475 - ((2475 * ValorADC))/4096)/10; //convertir a grados
    ADC0_ISC_R   = 8;                      //limpiar bandera

               }
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
