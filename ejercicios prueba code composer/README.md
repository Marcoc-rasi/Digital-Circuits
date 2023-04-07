•	#CD141220-display.c
•	Es un programa en lenguaje C que se utiliza para controlar un display de 7 segmentos con un microcontrolador MSP430. El programa realiza las siguientes funciones:
o	Define las constantes y variables globales que se usan en el programa, como los pines del puerto P1 que se conectan al display, el valor de la frecuencia del reloj del sistema y el número de veces que se repite el ciclo de encendido y apagado del display.
o	Inicializa el microcontrolador configurando los registros de dirección, función y salida del puerto P1, el registro de control del reloj del sistema y el registro de control del temporizador A0.
o	Define una función llamada "delay_ms" que recibe como parámetro un número entero que representa el tiempo en milisegundos que se desea esperar. La función usa el temporizador A0 para generar una interrupción cada 1 ms y cuenta el número de interrupciones hasta llegar al valor del parámetro. La función se usa para generar retardos entre los cambios de estado del display.
o	Define una función llamada "display_7seg" que recibe como parámetro un número entero entre 0 y 9 que representa el dígito que se desea mostrar en el display. La función usa un arreglo de 10 elementos que contiene los valores binarios correspondientes a cada dígito y los envía al puerto P1 mediante una operación de asignación. La función se usa para mostrar los números en el display.
o	Define una función llamada "main" que contiene el bucle principal del programa. La función realiza las siguientes acciones:
o	Declara una variable local llamada "i" que se usa como contador.
o	Inicia un bucle infinito con la instrucción "while(1)".
o	Dentro del bucle, recorre los valores desde 0 hasta 9 con la instrucción "for(i=0; i<10; i++)".
o	Dentro del bucle for, llama a la función "display_7seg" pasando como parámetro el valor de "i".
o	Después de mostrar cada número, llama a la función "delay_ms" pasando como parámetro el valor de 500 para generar un retardo de medio segundo.
o	Al finalizar el bucle for, vuelve a iniciar el ciclo desde el principio.
•	#CODPRAC9.C
•	El programa tiene el propósito de simular el funcionamiento de un circuito digital que utiliza un contador binario de 4 bits y un decodificador BCD a 7 segmentos para mostrar los números del 0 al 9 en un display LED.
•	El programa consta de las siguientes partes:
o	Inclusión de librerías: se incluyen las librerías necesarias para el uso de funciones y constantes predefinidas, como stdio.h, stdint.h y msp430.h.
o	Definición de macros: se definen macros para facilitar la escritura y lectura del código, como BIT0, BIT1, BIT2 y BIT3, que representan los bits menos significativos de un byte.
o	Declaración de variables globales: se declaran variables globales para almacenar el valor del contador binario y el valor del decodificador BCD a 7 segmentos, así como una constante que almacena la tabla de conversión entre ambos sistemas.
o	Configuración del microcontrolador: se configura el microcontrolador MSP430 para usar el reloj interno a 1 MHz, habilitar las interrupciones y configurar los puertos P1 y P2 como salidas digitales.
o	Función main: es la función principal del programa, que se ejecuta al iniciar el mismo. En esta función se llama a la función WDTCTL para deshabilitar el watchdog timer, se llama a la función BCSCTL1 para configurar el divisor del reloj, se llama a la función CCTL0 para configurar el temporizador A0 con modo continuo y fuente SMCLK, se llama a la función TACCR0 para establecer el valor de comparación del temporizador A0 a 50000, se llama a la función CCR0 para habilitar la interrupción por comparación del temporizador A0, y se entra en un bucle infinito que espera a que ocurra una interrupción.
o	Rutina de servicio de interrupción (ISR) del temporizador A0: es la función que se ejecuta cuando el temporizador A0 alcanza el valor de comparación establecido. En esta función se incrementa el valor del contador binario, se aplica una máscara de 4 bits para evitar que supere el valor 9, se busca el valor correspondiente en la tabla de conversión del decodificador BCD a 7 segmentos, y se asigna ese valor al puerto P2 para encender los segmentos adecuados del display LED. Además, se invierte el valor del bit menos significativo del puerto P1 para generar un efecto de parpadeo en un LED conectado a ese pin. Finalmente, se limpia la bandera de interrupción del temporizador A0.

