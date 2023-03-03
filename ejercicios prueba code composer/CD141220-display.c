#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/sysctl.h"

unsigned char Valcon,Temp,Temp2;

#define bitset(Var,bitno) ((Var) |= 1 << (bitno))
#define bitclr(Var,bitno) ((Var) &= ~(1 << (bitno)))

#define PORTDIS GPIO_PORTK_DATA_R
#define PORTCON GPIO_PORTM_DATA_R

//bits de control en PORTM
#define E 0x04
#define RS 0x01
#define R_W 0x02


#define BIT7 0X80


#define DISP_ON 0Xff
#define CLR_DISP 0x01

void INILCD(void);
void BUSY (void);
void _E(void);
void ESCDAT (unsigned char c);
void ESCCOM (unsigned char d);
void CLS(void);
void BYTEDIS(unsigned char DByte);
void HOME(void);
void AND491(void);
void   LEECON(void);

    void    main(void)
    {
        INILCD(); //inicializa el display 16 x 2
        while (1);
    }

void INILCD(void)  //INICIALIZA EL DISPLAY A DOS LINEAS, 4 BITS DE INTERFAZ, CURSOR Y DESTELLO.
{
    //PRIMER METODO DE INICIALIZACION
    PORTDIS=0X30; // **D7-D4 = 0011

    SysCtlDelay(80);                 //Delay 100ms
    _E();                               //toggle E
    SysCtlDelay (8);                   //10ms
    _E();                               //toggle E
    SysCtlDelay (8);                   //10ms
    PORTDIS=0X20;
    _E();                               //toggle E
    SysCtlDelay (8);                   //10ms
    ESCCOM(0X38);   //8 BITS , 2 LINEAS, 5X7

    ESCCOM(DISP_ON);  // ENCIENDE DISPLAY CON CURSOR Y DESTELLO


    ESCCOM(CLR_DISP); // BORRAR DISPLAY

    ESCCOM(0X06); // AL ESCRIBIR EL CURSOR SE INCREMENTA Y SE DESPLAZA
    ESCCOM(0X38); // //8 BITS , 2 LINEAS, 5X7 REQUERIDO POR LOS DISPLAYS CLONES

    }

void _E(void)  //GENERA UN PULSO DE 1.25 uS EN LA TERMINAL E DEL DISPLAY
{
    bitset(PORTCON,E);        // E=1
    SysCtlDelay (1);  //retraso de 1.25 uS
    bitclr(PORTCON,E);  // E=0
}

void ESCDAT (unsigned char c)  //ESCRIBE UN DATO ALFANUMERICO AL DISPLAY
{
    //ENVIA dato
    PORTDIS = c;

    bitset(PORTCON,RS);    //ENVIA A REGISTRO DE DATOS
    _E();                //TOGGLE _E()
    BUSY(); //PREGUNTA POR LA BANDERA DE BUSY
    bitclr(PORTCON,RS);    //niveles de control a 0
    }



void ESCCOM (unsigned char d)// ENVIA UN COMANDO AL REGISTRO DE CONTROL DEL LCD
{

    PORTDIS = d;               //envia CMD al LCD
    bitclr(PORTCON,RS);               //direcciona registro de controldel  LCD
    _E();                           //toggle E
    BUSY(); //VERIFICA LA BANDERA DE BUSY
    }



void CLS(void)
{ ESCCOM(0x01);
     AND491( );
        }

void HOME(void)
{ ESCCOM(0x02);
     AND491( ); }


void AND491(void)  // GENERA LOS CORRIMIENTOS PARA ALINEAR COMO EN
    {   ESCCOM (0X1C);  //EL AND491 PARA LOS DISPLAYS GENERICOS
        ESCCOM (0X1C);
        ESCCOM (0X1C);
        ESCCOM (0X1C);
    }



void BUSY (void)  //PREGUNTA POR EL ESTADO DE LA BANDERA BUSY Y ESPERA HASTA QUE SEA CERO
{
    do LEECON( );
    while ((Valcon & BIT7) != 0);
    }


void   LEECON(void)
// LEE EL VALOR DEL REGISTRO DE CONTROL DEL DISPLAY Y REGRESA EL CONTENIDO EN VALCON
    {   PORTDIS=0;
        GPIO_PORTK_DIR_R=0x00; //PORTK como entrada
        bitset(PORTCON,R_W); // LEER PUERTO DE CONTROL
         bitset(PORTCON,E);      //ACTIVA E
         SysCtlDelay(1); //espera 1.25 uS
         Temp=PORTDIS; // LEE PARTE ALTA DEL BUS DE DATOS
         bitclr(PORTCON,E);
         bitclr(PORTCON,E);
         bitclr(PORTCON,R_W);
         GPIO_PORTK_DIR_R=0XFF; //REGRESA A LA CONDICION ORIGINAL DEL PUERTO K A SALIDA
          Valcon=Temp;
                }


void BYTEDIS(unsigned char DByte) //escribe un byte a pantalla

{ Temp2=DByte;
    Temp2=Temp2>>4;
    if (Temp2<=0x09)
        Temp2+=0x30;
        else
        Temp2+=0x37;
            ESCDAT(Temp2);
        Temp2=DByte&0x0f;
        if (Temp2<=0x09)
        Temp2+=0x30;
        else
        Temp2+=0x37;
            ESCDAT(Temp2);

}

