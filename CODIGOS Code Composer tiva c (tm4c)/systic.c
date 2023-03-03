#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c1294ncpdt.h"


 void main (void)

 {  //habilitar portn


     SYSCTL_RCGCGPIO_R |=0X0a00;
     while((SYSCTL_RCGCGPIO_R&0X0a00)==0);

     GPIO_PORTK_DATA_R |=0X00;
     GPIO_PORTK_DIR_R |=0X03;
     GPIO_PORTK_DEN_R |=0X03;


     NVIC_ST_RELOAD_R=2000000; //A 16 Mhz T=62.5 nS, 0.5s/65.5ns = 2000000
     NVIC_ST_CTRL_R=0X05;    //CLK_SRC  INTEN  EN 0101


     while(1)
     {
         // checamos la bandera de count posicion 16
     while (( NVIC_ST_CTRL_R&0x10000)==0); // 0001 0000 0000 0000 0000
      GPIO_PORTK_DATA_R ++;

     }


 }
