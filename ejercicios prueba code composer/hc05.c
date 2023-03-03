/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

uint8_t d_uint8Dato;

UART_INI(void)
{
SYSCTL_RCGCUART_R |=0X0009; //HABILITAR UART0  0000 1001
SYSCTL_RCGCGPIO_R |=0X0001; //HABILITAR PUERTO A

UART0_CTL_R &=~0X0001;  //DESHABILITAR UART
UART0_IBRD_R = 27 ; //IBDR=int(50000000/16*115200))= int(27.1267)
UART0_FBRD_R =8 ; //FBRD= round(0.1267*64 =8)
UART0_LCRH_R =0X0070; //8 BITS, HABILITAR FIFO
UART0_CTL_R= 0X0301 ; //HABILITAR RXE, TXE Y UART

UART3_CTL_R &=~0X0001;  //DESHABILITAR UART
UART3_IBRD_R = 325 ; //IBDR=int(50000000/16*9600))= int(325.5208)
UART3_FBRD_R =33 ; //FBRD= round(0.5208*64 =33.3311)
UART3_LCRH_R =0X0070; //8 BITS, HABILITAR FIFO
UART3_CTL_R= 0X0301 ; //HABILITAR RXE, TXE Y UART


GPIO_PORTA_AHB_PCTL_R = (GPIO_PORTA_AHB_PCTL_R&0XFFFFFF00)+0X00110011; //UART
GPIO_PORTA_AHB_AMSEL_R &= ~0X33; //DESHABILITAR FUNCION ANLOGICA EN PA0-1 0011 0011
GPIO_PORTA_AHB_AFSEL_R |= 0X33; //HABILITAR FUNCION ALTERNA EN PA0-1
GPIO_PORTA_AHB_DEN_R |= 0X33; //HABILITAR FINCION I/O DIGITAL
}

//esperar hasta que se reciba un dato
char UART_Lee_dato(void)
{
while((UART0_FR_R&0X0010)!=0); //ESPERAR A QUE RXFE SEA CERO
d_uint8Dato=((char)(UART0_DR_R&0xff));
//return((char)(UART0_DR_R&0xff));
}

//esperar hasta que se reciba un dato en UART3
char UART3_Lee_dato(void)
{
while((UART3_FR_R&0X0010)!=0); //ESPERAR A QUE RXFE SEA CERO
d_uint8Dato=((char)(UART3_DR_R&0xff));
//return((char)(UART0_DR_R&0xff));
}



char UART0_Escribe_dato(char dato)
{
while   ((UART0_FR_R&0X0020)!=0); // espera a que TXFF sea cero
UART0_DR_R=dato;
}
int main(void) {
    uint32_t g_ui32SysClock;
    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                                 SYSCTL_OSC_MAIN |
                                                 SYSCTL_USE_PLL |
                                                 SYSCTL_CFG_VCO_480), 50000000);
 //

    UART_INI();

while (1)
{
    UART3_Lee_dato();
    UART0_Escribe_dato(d_uint8Dato +1);
}
}