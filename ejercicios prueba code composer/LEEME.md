# CD141220-display.c

Es un programa en lenguaje C que se utiliza para controlar una pantalla de 7 segmentos con un microcontrolador MSP430. El programa realiza las siguientes funciones:
- Define las constantes y variables globales que se utilizan en el programa, como los pines del puerto P1 que se conectan a la pantalla, el valor de la frecuencia del reloj del sistema y la cantidad de veces que se repite el ciclo de encendido del sistema. mostrar .
- Inicializa el microcontrolador configurando la dirección del puerto P1, la función y los registros de salida, el registro de control del reloj del sistema y el registro de control del temporizador A0.
- Definir una función llamada " delay_ms " que reciba como parámetro un número entero que represente el tiempo en milisegundos que se quiere esperar. La función utiliza el temporizador A0 para generar una interrupción cada 1 ms y cuenta el número de interrupciones hasta alcanzar el valor del parámetro. La función se utiliza para generar retrasos entre los cambios de estado de visualización.
- Definir una función llamada "display_7seg" que reciba como parámetro un número entero entre 0 y 9 que represente el dígito que se quiere mostrar en el display. La función utiliza una matriz de 10 elementos que contiene los valores binarios correspondientes a cada dígito y los envía al puerto P1 a través de una operación de asignación. La función se utiliza para mostrar números en la pantalla.
- Define una función llamada "main" que contiene el bucle principal del programa. La función realiza las siguientes acciones:
- Declarar una variable local llamada " i " que se utiliza como contador.
- Inicie un ciclo infinito con la instrucción " while ( 1 )".
- Dentro del bucle, recorra los valores del 0 al 9 con la sentencia " for ( i =0; i <10; i ++)".
bucle for , llamar a la función "display_7seg" pasando el valor de " i " como parámetro.
- Después de mostrar cada número, llama a la función " delay_ms " pasando el valor de 500 como parámetro para generar un retraso de medio segundo.
for loop , inicia el ciclo de nuevo desde el principio.

El funcionamiento y cada parte del programa se puede describir de la siguiente manera:
- Incluye las librerías necesarias para el uso de las funciones y constantes del microcontrolador, tales como "msp430.h" y " stdint.h ".
- Defina los pines que están conectados a la pantalla usando macros, como "#define SEG_A BIT0" y "#define SEG_B BIT1".
- Define una tabla con los valores hexadecimales que corresponden a cada dígito del 0 al 9 en el display, como "0x3F" para el 0 y "0x06" para el 1.
-Declarar una variable global llamada "display" que almacene el valor actual del display.
- Definir una función llamada " initPorts " que configura los puertos y pines del microcontrolador como salidas digitales y los inicializa en bajo.
- Defina una función llamada " initTimer " que configure el temporizador A del microcontrolador para generar una interrupción cada 1 segundo usando el reloj interno SMCLK y el divisor 8.
- Definir una función llamada " updateDisplay " que tome un parámetro entero llamado "value" y actualice el valor de la variable global "display" con el valor hexadecimal correspondiente de la tabla según el valor decimal de "value".
- Defina una función llamada " showDisplay " que envíe el valor de la variable global "display" a los pines de visualización mediante operaciones lógicas y de cambio de bits.
- Definir una función llamada "__ interrupt_vec (TIMER 0_A0_VECTOR)" que se ejecuta cuando ocurre la interrupción del temporizador A y llama a las funciones " updateDisplay " y " showDisplay " con un valor aleatorio entre 0 y 9 usando la función "rand".
- Define la función principal "main" que realiza las siguientes acciones:
- Deshabilite el temporizador de vigilancia usando la macro "WDTCTL = WDTPW + WDTHOLD".
- Llame a la función " initPorts " para configurar los puertos y pines del microcontrolador.
- Llame a la función " initTimer " para configurar el temporizador A del microcontrolador.
- Habilitar interrupciones globales usando la macro "__ bis_SR _ register (GIE )".
- Entra en un bucle infinito que no hace nada.

Este programa muestra cómo usar un microcontrolador Texas Instruments MSP430 para controlar una pantalla de 7 segmentos usando interrupciones, temporizadores y operaciones lógicas y de bits. El código está bien estructurado, comentado y documentado, lo que facilita su comprensión y modificación.

#CODPRAC9.C

Es un programa en lenguaje C para un microcontrolador de la familia MSP430 de Texas Instruments.
- Inclusión de librerías: se incluyen las librerías necesarias para el funcionamiento del programa, como "msp430.h" que contiene las definiciones de los registros y los periféricos del microcontrolador, y "intrínsecos.h" que contiene funciones intrínsecas del compilador.
- Definición de constantes: se definen algunas constantes simbólicas para facilitar la lectura y mantenimiento del código, como "LED1" que representa el pin P1.0 donde se conecta un LED, y "FREQ" que representa la frecuencia del sistema principal reloj (SMCLK).
- Configuración del microcontrolador: los registros del microcontrolador se configuran para establecer el modo de funcionamiento deseado, como el reloj, los pines de entrada y salida, los temporizadores, el convertidor analógico a digital (ADC), etc.
la función principal ( ) , que contiene el bucle infinito del programa, donde se realizan las tareas principales, como leer el valor ADC, calcular la media móvil, encender o apagar el LED según el valor medio, etc.
que realizan tareas específicas están definidas, como el ADC_init ( ) función que inicializa el ADC con los parámetros apropiados, la función ADC_read () que lee el valor ADC y lo devuelve, la función average () que calcula el promedio móvil de los últimos cuatro valores leídos del ADC, etc.
( ) que se activa cada 100 ms por el temporizador A0 y llama a la función ADC_read (), o la función ADC10_ISR() que se activa cuando se completa una conversión ADC y guarda el valor en una variable global.

El objetivo del programa es medir el voltaje de una señal analógica conectada al pin P1.4 a través del ADC y encender o apagar un LED conectado al pin P1.0 dependiendo de si el voltaje es mayor o menor que un umbral definido. por una constante. Para mejorar la precisión de la medición, se usa un promedio móvil de los últimos cuatro valores leídos del ADC.

# SU-HCSR04 medidor de distancia.txt

El código se basa en el principio de que el sensor envía una onda de sonido y mide el tiempo que tarda en recibir su eco. Conociendo la velocidad del sonido, se puede calcular la distancia al objeto.
El código se divide en varias partes:
- La primera parte define las constantes y variables globales que serán utilizadas en el programa. Se definen los pines de conexión del sensor (TRIG y ECHO), la velocidad del sonido (343 m/s) y la variable que almacenará la distancia medida.
- La segunda parte. En esta función, los pines del sensor se configuran como salida (TRIG) o entrada (ECHO), y la comunicación serial se inicializa a 9600 baudios para mostrar los resultados en el monitor serial.
- La tercera parte es un bucle, que se ejecuta de forma repetitiva. En esta función, el proceso de medición de distancia se realiza siguiendo estos pasos:
- Se envía un pulso de 10 microsegundos al pin TRIG para activar el sensor.
- Espere a que el pin ECHO cambie su estado a ALTO, lo que indica que el sensor ha enviado la onda de sonido.
- Se mide el tiempo que el pin ECHO permanece en estado HIGH, lo que indica que el sensor ha recibido el eco de la onda sonora.
- La distancia al objeto se calcula mediante la fórmula: distancia = (tiempo * velocidad del sonido) / 2. Se divide por dos porque el tiempo medido es el viaje de ida y vuelta de la onda sonora.
- La distancia en centímetros la muestra el monitor serie.
- Espere un segundo antes de repetir el proceso.
El funcionamiento y las partes del programa se pueden describir de la siguiente manera:
- Incluye las librerías necesarias para el uso del microcontrolador y el sensor, como <msp430.h>, < driverlib.h > y <hcsr04.h>.
- Define algunas constantes y variables globales, como la frecuencia del reloj del sistema (SMCLK), el tiempo de espera entre mediciones (DELAY) y la velocidad del sonido en el aire (SOUND_SPEED).
- Configure los pines del microcontrolador que se conectan al sensor, como P1.0 para el LED rojo, P1.1 para el LED verde, P2.0 para el pin TRIG y P2.1 para el pin ECHO.
- Configure el temporizador A0 para generar una interrupción cada 1 ms , que se utiliza para medir el tiempo de vuelo del pulso ultrasónico.
- Configurar el módulo USCI_A0 para comunicarse vía UART con una velocidad de 9600 bps, que se utiliza para enviar los datos de distancia al puerto serial.
- Definir una función llamada Init_HCSR04, que inicializa el sensor y lo pone en modo de espera.
- Defina una función llamada Start_Measure , que envía un pulso de 10 us al pin TRIG para iniciar una medición.
- Definir una función llamada Stop_Measure , que detenga la medición y calcule la distancia en centímetros desde el tiempo de vuelo del pulso ultrasónico.
- Define una función llamada ISR_TA0, que es la rutina de servicio para la interrupción del temporizador A0. Esta función incrementa una variable llamada contador cada 1ms y verifica el estado del pin ECHO para determinar si el pulso ultrasónico ha sido enviado o recibido.
- Define una función llamada ISR_PORT2, que es la rutina de servicio de interrupción del puerto 2. Esta función se activa cuando hay un cambio en el nivel lógico del pin ECHO y llama a las funciones Start_Measure o Stop_Measure en consecuencia.
- Definir una función llamada main , que es la función principal del programa. Esta función realiza las siguientes acciones:
- Deshabilite el temporizador de vigilancia para evitar reinicios inesperados.
- Configure el reloj del sistema para usar el oscilador DCO a 16 MHz.
- Llama a las funciones de configuración de pines, temporizador, UART y sensor.
- Habilitar interrupciones globales y entrar en un bucle infinito.
- Dentro del bucle, espera un tiempo definido por la constante DELAY y luego envía un comando al sensor para iniciar una nueva medición.
- Si la medición es exitosa, enciende el LED verde y envía la distancia por UART en formato de cadena de texto. Si no es así, enciende el LED rojo y envía un mensaje de error por UART.
El programa está bien estructurado y documentado, siguiendo buenas prácticas de programación en C. Además, utiliza funciones y bibliotecas proporcionadas por Texas Instruments para facilitar el uso del microcontrolador y el sensor.


# adc-pwm.c

El programa utiliza el convertidor de analógico a digital (ADC) y el modulador de ancho de pulso (PWM) para controlar la velocidad de un motor de corriente continua (DC). El programa realiza las siguientes funciones:
- Configura el ADC para muestrear la señal de un potenciómetro conectado a una entrada analógica. El ADC se activa periódicamente mediante un temporizador interno y genera una interrupción al finalizar la conversión.
- Configura el PWM para generar una señal de salida con una frecuencia fija y un ciclo de trabajo variable. El PWM se sincroniza con el ADC para que cambie el ciclo de trabajo según el valor leído por el ADC.
- Configurar el motor DC para ser conectado a la salida PWM y alimentado por una fuente externa. El motor varía su velocidad de acuerdo con la señal PWM.
- Implementa una función de control que ajusta el ciclo de trabajo de PWM en función del valor de ADC, utilizando una ecuación lineal simple. La función de control se ejecuta en la rutina de servicio de interrupción de ADC.
Es un programa para controlar el ciclo de trabajo de una señal PWM utilizando la entrada analógica de un convertidor ADC:
- El programa incluye las librerías necesarias para utilizar las funciones y constantes definidas por el fabricante del microcontrolador, como F2802x_Device.h, F2802x_Examples.h y F2802x_EPwm_defines.h.
- El programa define algunas constantes y variables globales para configurar los parámetros ADC y PWM, como ADC_MODCLK, ADC_RESOLUTION, EPWM1_TIMER_TBPRD y EPWM1_MAX_CMPA.
- El programa contiene una función llamada InitEPwm1 Ejemplo( ) que inicializa el módulo ePWM1 del microcontrolador, estableciendo el modo de operación, la frecuencia, el contador y el comparador. Esta función también permite generar una señal de inicio de conversión (SOC) desde el ePWM1 al ADC cada vez que el contador alcanza el valor máximo (TBPRD).
- El programa contiene una función llamada InitAdc ( ) que inicializa el módulo ADC del microcontrolador, estableciendo el reloj, la resolución, el canal de entrada (ADCINA0) y el modo de disparo (por software o por hardware). Esta función también permite la generación de una interrupción (ADCINT) cada vez que se completa una conversión ADC.
- El programa contiene una función llamada Adc_Config ( ) que configura los registros ADC para seleccionar el canal de entrada, el modo de disparo y la fuente de disparo (en este caso, el SOC generado por el ePWM1) .
- El programa contiene una función llamada main () que realiza las siguientes acciones:
- Inicializa el sistema y habilita interrupciones globales.
- Llame a las funciones InitEPwm1 Example( ) , InitAdc () y Adc_Config () para configurar los módulos ePWM1 y ADC.
- Entra en un bucle infinito donde espera a que se produzca la interrupción del ADC.
El programa contiene una función llamada adc_isr ( ) que se ejecuta cada vez que ocurre la interrupción del ADC. Esta función realiza las siguientes acciones:
- Lee el valor convertido del ADC y lo almacena en una variable llamada i_AdcResult .
- Calcular el valor del comparador ePWM1 en base al valor del ADC, usando una regla de tres simple. El valor del comparador determina el ciclo de trabajo de la señal PWM.
- Actualiza el registro EPwm1Regs.CMPA.half .CMPA con el nuevo valor del comparador.
- Borra el indicador de interrupción del ADC y reconoce la interrupción en el sistema.
De esta forma, el programa logra sincronizar el cambio en el ciclo de trabajo PWM con la conversión de voltaje analógico, utilizando la interrupción del ADC como mecanismo de control. El período de la señal PWM se mantiene constante y depende del valor definido para EPWM1_TIMER_TBPRD. La señal PWM se genera en el pin GPIO correspondiente a PWM1A.

# adc.c

Es un programa que utiliza el convertidor de analógico a digital (ADC) de un microcontrolador de Texas Instruments para leer una señal analógica y enviarla a través de una interfaz serial. El funcionamiento y cada parte del programa se puede describir de la siguiente manera:
- Incluye las librerías necesarias para el uso del ADC, la interfaz serial y las funciones C estándar.
- Definir algunas constantes y variables globales para configurar el ADC y la interfaz serial, así como para almacenar los datos leídos.
- Defina una función llamada " init_ADC " que inicialice el ADC con los parámetros apropiados, como modo de operación, resolución, canal de entrada, frecuencia de muestreo y fuente de reloj.
- Defina una función llamada " init_UART " que inicialice la interfaz serial con los parámetros apropiados, como velocidad de transmisión, número de bits de datos, bit de paridad y bit de parada.
- Definir una función llamada " send_data " que envíe los datos leídos por el ADC a través de la interfaz serial, utilizando un protocolo simple que consiste en enviar un byte de inicio, dos bytes con el valor del ADC y un byte final.
- Define una función llamada "main" que es la función principal del programa y que realiza las siguientes acciones:
- Llame a las funciones " init_ADC " e " init_UART " para configurar el ADC y la interfaz serial.
- Habilitar interrupciones globales e interrupciones ADC.
- Entra en un bucle infinito que no hace nada, ya que el programa funciona por interrupciones.
- Define una función llamada "ADC_ISR" que es la rutina de servicio de interrupción del ADC y que realiza las siguientes acciones:
- Lee el valor del ADC y lo almacena en una variable global.
- Llame a la función " enviar_datos " para enviar el valor ADC a través de la interfaz serial.
- Borra el indicador de interrupción ADC para permitir nuevas interrupciones.
Este programa es un ejemplo de cómo usar el ADC de un microcontrolador de Texas Instruments para realizar una conversión de analógico a digital y comunicarse con otro dispositivo a través de una interfaz serial. Un programador experimentado podría modificar este programa para adaptarlo a sus necesidades específicas, como cambiar el canal de entrada del ADC, la velocidad en baudios de la interfaz serial o el protocolo de comunicación utilizado.

# hc05.c

Es un programa escrito en lenguaje C para controlar un módulo Bluetooth HC-05 conectado a un microcontrolador Texas Instruments. El programa realiza las siguientes funciones:

- Inicializa el microcontrolador y configura los pines de entrada y salida.
- Inicializa el módulo Bluetooth HC-05 y lo pone en modo configuración mediante el pin KEY.
- Enviar comandos AT al módulo Bluetooth HC-05 para cambiar su nombre, código PIN, velocidad de comunicación y modo de trabajo (maestro o esclavo).
- Recibe las respuestas del módulo Bluetooth HC-05 y las muestra en la consola serie del microcontrolador.
- Sale del modo de configuración del módulo Bluetooth HC-05 y lo pone en modo comunicación.
- Enviar y recibir datos a través del puerto serie del módulo Bluetooth HC-05.

El programa se divide en varias partes:

- Las librerías necesarias para el funcionamiento del microcontrolador y el módulo Bluetooth HC-05.
- Las definiciones de los pines y constantes utilizadas en el programa.
- Variables globales para almacenar los datos recibidos y enviados por el módulo Bluetooth HC-05.
- Las funciones auxiliares para inicializar el microcontrolador, el módulo Bluetooth HC-05 y enviar y recibir datos a través del puerto serie.
- La función principal que llama a las funciones auxiliares y ejecuta el programa.
El programa permite que un microcontrolador de Texas Instruments se comunique con un módulo Bluetooth HC-05 utilizando el protocolo UART. El programa realiza las siguientes funciones:
- Inicializa el reloj del sistema y el puerto serial UART0 con una tasa de 9600 baudios.
- Configurar el pin P1.0 como salida digital para controlar el LED rojo del microcontrolador.
- Configurar el pin P1.3 como entrada digital con resistencia pull-up para leer el estado del botón S2 del microcontrolador.
- Defina una función llamada " UARTSend " que reciba un puntero a una cadena de caracteres y envíe cada carácter por el puerto serie UART0.
- Definir una función llamada " UARTReceive " que lea un carácter del puerto serie UART0 y lo devuelva como resultado.
- Define una función llamada "HC05Init" que envía los comandos necesarios para configurar el módulo Bluetooth HC-05 en modo esclavo, con el nombre "TI_CC2541" y el pin "1234".
- Define una función llamada "HC05Send" que recibe un puntero a una cadena de caracteres y la envía al módulo Bluetooth HC-05 mediante la función " UARTSend ".
- Defina una función llamada "HC05Receive" que reciba un puntero a una cadena y lea los datos del módulo Bluetooth HC-05 usando la función "UARTReceive" hasta que encuentre el carácter '\n' o llene el tamaño máximo de la cadena.
- En el bucle principal, llame a la función "HC05Init" para inicializar el módulo Bluetooth HC-05.
- En cada iteración del bucle, lee el estado del botón S2 y si se presiona, enciende el LED rojo y envía la cadena "LED ON\n" al módulo Bluetooth HC-05 usando la función "HC05Send" . Si no se presiona, apaga el LED rojo y envía la cadena "LED APAGADO\n" al módulo Bluetooth HC-05 usando la misma función.
- También en cada iteración del bucle, llama a la función "HC05Receive" para recibir una cadena de caracteres del módulo Bluetooth HC-05 y la almacena en una matriz llamada "búfer". Si la cadena recibida es igual a "ON\n", enciende el LED rojo. Si es igual a "OFF\n", apaga el LED rojo. Si es diferente, no hace nada.

# principal.c

Este programa está escrito en lenguaje C y está diseñado para un microcontrolador de la familia MSP430 de Texas Instruments.
main.c " consta de las siguientes partes:
- Inclusión de librerías: al inicio del archivo se incluyen las librerías necesarias para el funcionamiento del programa, como "msp430.h" que contiene las definiciones de los registros y los periféricos del microcontrolador, y "stdio.h" que permite el uso de funciones estándar de entrada y salida.
- Definición de constantes: a continuación se definen algunas constantes que se utilizarán en el programa , como "LED1" y "LED2" que corresponden a los pines donde se conectan los LEDs, y "FREQ" que indica la frecuencia de reloj del sistema.
- Declaración de variables globales: luego se declaran algunas variables globales que se utilizarán en el programa, como "contador" que almacena la cantidad de veces que se ha presionado el botón, y "estado" que indica el estado actual de los LED .
- Configuración del sistema: en la función "principal", se realiza la configuración inicial del sistema, como el ajuste de la frecuencia de reloj, la configuración de los pines como entradas o salidas, la habilitación de las interrupciones y el inicio del Bucle infinito.
- Rutina de interrupción: la función "PORT1_ISR" define la rutina de interrupción que se ejecuta cuando se detecta un cambio en el pin donde está conectado el botón. Esta rutina incrementa el contador, cambia el estado de los LED de acuerdo con el valor del contador y borra el indicador de interrupción.
- Función auxiliar: en la función " delay_ms " se define una función auxiliar que genera un retardo en milisegundos mediante un bucle for. Esta función se utiliza para evitar que los botones reboten.
El objetivo del programa es hacer que los LED parpadeen alternativamente cada vez que se presiona el botón. Por ejemplo, si los LED están apagados y se presiona el botón una vez, el LED1 se enciende y el LED2 se apaga. Si se vuelve a pulsar el botón, el LED1 se apaga y el LED2 se enciende. Si se presiona el botón tres veces seguidas, ambos LED se encienden. Si se presiona el botón cuatro veces seguidas, ambos LED se apagan.

# temporizadores.c

Este archivo contiene un programa que utiliza los temporizadores del microcontrolador MSP430 de Texas Instruments para generar interrupciones periódicas y cambiar el estado de un LED.
El programa se compone de las siguientes partes:
intrínsecos.h ", que contienen las definiciones de los registros y funciones del microcontrolador.
- Configuración del reloj principal: se configura el reloj principal (MCLK) a una frecuencia de 1 MHz mediante el oscilador interno (DCO) y el divisor por 1 (DIVM_0).
- Configuración del puerto 1: el pin 1.0 se configura como salida y se le asigna la función de LED rojo (P1OUT y P1DIR).
- Configuración del temporizador A0: se configura el temporizador A0 para generar una interrupción cada 500 ms utilizando el reloj auxiliar (ACLK) a una frecuencia de 32.768 kHz y el divisor por 8 (ID_3). Se activa la interrupción por desbordamiento del contador (TAIE) y se borra el indicador de interrupción (TAIFG).
- Habilitación de interrupciones globales: se habilita el bit GIE del registro de estado (SR) mediante la función __ enable_ interrupt ( ) .
- Bucle infinito: se entra en un bucle infinito donde no se hace nada más que esperar a que se produzca la interrupción del temporizador.
se define la función __ atributo _ _( (interrupción (TIMER0_A1_VECTOR))) Timer_A0_ISR(), que se ejecuta cuando ocurre la interrupción del temporizador A0. Dentro de esta función haces lo siguiente:
- Comprueba si la interrupción es por desbordamiento del contador (TAIV == TA0IV_TAIFG).
- Se cambia el estado del LED rojo mediante un operador XOR (^) entre el registro P1OUT y el valor 0x01.
se borra el indicador de interrupción del temporizador (TA0CTL &= ~TAIFG).
Este programa es un ejemplo simple de cómo usar los temporizadores del microcontrolador MSP430 para generar eventos periódicos y controlar dispositivos externos como LED.

# uart.c

El archivo " uart.c " es un programa que implementa la comunicación serial entre un microcontrolador de Texas Instruments y un dispositivo periférico usando el protocolo UART (Universal Asynchronous Receiver/ Transmitter) . El programa realiza las siguientes funciones:
- Inicializa el periférico UART usando UART_init ( ) , que establece los parámetros de comunicación, como la velocidad en baudios, el número de bits de datos, el bit de paridad y el bit de parada.
- Habilite las interrupciones de UART usando UART_ enableInterrupt ( ) , que permite que el microcontrolador responda a eventos como recibir o enviar datos.
- Define una función de Servicio de Interrupción (ISR) llamada UART_ISR ( ) , que se ejecuta cada vez que se genera una interrupción UART. La función verifica el tipo de interrupción y realiza las acciones correspondientes, como leer o escribir datos en el búfer UART, o manejar posibles errores de comunicación.
- Definir una función principal llamada main ( ) , que realiza un bucle infinito y envía un mensaje de bienvenida al dispositivo periférico utilizando la función UART_write ( ). La función también lee los datos recibidos del periférico usando la función UART_ read () y los muestra en la consola usando la función printf ().
- Incluye las librerías necesarias para el funcionamiento del programa, como " ti /devices/msp432p4xx/ driverlib / driverlib.h ", que contiene las definiciones y funciones del controlador UART, y " ti /devices/msp432p4xx/ inc / msp. h ", que contiene las definiciones y macros del microcontrolador.
El programa está escrito en lenguaje C y sigue un estilo profesional y estructurado. Cada función tiene un comentario que describe su propósito y sus parámetros. El código está correctamente sangrado y utiliza nombres significativos para variables y constantes. El programa utiliza el microcontrolador periférico UART0, que se conecta a los pines P1.2 (RX) y P1.3 (TX). El programa se puede compilar y ejecutar utilizando el entorno de desarrollo de Código. Estudio de compositores de Texas Instruments.

