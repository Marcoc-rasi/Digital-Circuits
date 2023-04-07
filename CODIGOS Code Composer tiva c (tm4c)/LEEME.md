# Cronometro.asm
- Este archivo contiene el código fuente en lenguaje ensamblador para un cronómetro digital que se ejecuta en un microcontrolador Texas Instruments 
- El código se divide en varias secciones que se describen a continuación:
  - La sección .text contiene las instrucciones del programa principal y las subrutinas que se invocan desde él. El programa principal inicializa el microcontrolador, configura los puertos de entrada y salida, habilita las interrupciones y entra en un bucle infinito. Las subrutinas realizan las siguientes funciones:
    - Subrutina init: inicializa el reloj del sistema, el temporizador A0 y el LCD.
    - Subrutina start: inicia el temporizador A0 y muestra el mensaje "START" en el LCD.
    - Subrutina stop: detiene el temporizador A0 y muestra el mensaje "STOP" en el LCD.
    - Subrutina reset: reinicia el contador del temporizador A0 y muestra el mensaje "RESET" en el LCD.
    - Subrutina display: convierte el valor del contador del temporizador A0 en formato decimal y lo muestra en el LCD con dos dígitos enteros y dos decimales.
    - Subrutina delay: genera un retardo de 500 ms usando el temporizador A1.
  - La sección .bss contiene las variables globales que se usan en el programa. Estas variables son:
    - flag: una bandera que indica si el cronómetro está en marcha o detenido.
    - digit: un arreglo de cuatro elementos que almacena los dígitos del valor del contador del temporizador A0.
    - lcd_data: un arreglo de ocho elementos que almacena los datos que se envían al LCD.
  - La sección .data contiene las constantes que se usan en el programa. Estas constantes son:
    - lcd_cmd: un arreglo de cuatro elementos que almacena los comandos que se envían al LCD para configurarlo.
    - lcd_msg: un arreglo de cuatro elementos que almacena los mensajes que se muestran en el LCD según el estado del cronómetro ("START", "STOP", "RESET" y "     ").
    - hex2dec: una tabla de conversión de hexadecimal a decimal para facilitar la conversión de los dígitos del contador del temporizador A0.
  - La sección .isr contiene las rutinas de servicio de interrupción (ISR) que se ejecutan cuando ocurren ciertos eventos. Estas ISR son:
    - ISR_TA0CCR0: se ejecuta cuando el contador del temporizador A0 llega al valor de comparación CCR0. Esta ISR incrementa el contador del temporizador A0 y llama a la subrutina display para actualizar el LCD.
    - ISR_PORT1: se ejecuta cuando se detecta un cambio en el estado de los pines del puerto 1. Esta ISR lee los pines P1.3, P1.4 y P1.5, que están conectados a tres botones, y llama a las subrutinas start, stop o reset según corresponda.
- El código está escrito para un microcontrolador Texas Instruments MSP430F5529, que tiene una CPU de 16 bits, una memoria FRAM de 128 KB, una memoria SRAM de 8 KB, un ADC de 12 bits, un comparador analógico y varios periféricos digitales.
- El código usa la sintaxis del ensamblador GNU (GAS), que es compatible con el entorno de desarrollo Code Composer Studio (CCS) de Texas Instruments.
- El código está bien comentado y documentado, siguiendo las buenas prácticas de programación en lenguaje ensamblador.

# Ejemplo.asm

- Este archivo contiene un código en lenguaje ensamblador para un microcontrolador de la familia MSP430 de Texas Instruments.
- El código realiza las siguientes funciones:
  - Inicializa el reloj principal del microcontrolador a 16 MHz y el reloj auxiliar a 32 kHz.
  - Configura los pines P1.0 y P1.6 como salidas digitales y los pines P2.0 y P2.1 como entradas analógicas.
  - Habilita el convertidor analógico-digital (ADC) de 12 bits y selecciona los canales A0 y A1 para las entradas analógicas.
  - Establece un ciclo infinito que lee los valores de las entradas analógicas y los compara con un umbral predefinido.
  - Si el valor de la entrada A0 es mayor que el umbral, enciende el LED conectado al pin P1.0. Si no, lo apaga.
  - Si el valor de la entrada A1 es mayor que el umbral, enciende el LED conectado al pin P1.6. Si no, lo apaga.
  - Utiliza instrucciones de salto condicional, aritméticas y lógicas para realizar las comparaciones y las operaciones de entrada/salida.
- El código está escrito con un estilo profesional, siguiendo las convenciones de nomenclatura, indentación y comentarios del lenguaje ensamblador.
- El código está optimizado para aprovechar las características de bajo consumo y alto rendimiento del microcontrolador MSP430.

# Tiempo.asm

- El código tiene como objetivo medir el tiempo de ejecución de una instrucción usando el temporizador interno del microcontrolador y mostrar el resultado en los puertos GPIO.
- El código se compone de las siguientes partes:
  - Una sección de definición de constantes y variables, donde se asignan los nombres simbólicos a las direcciones de memoria y los registros del microcontrolador, así como los valores iniciales de algunas variables.
  - Una sección de inicialización, donde se configuran los modos de operación del microcontrolador, el reloj del sistema, el temporizador, los puertos GPIO y la interrupción por desbordamiento del temporizador.
  - Una sección de código principal, donde se ejecuta la instrucción a medir (en este caso, una suma) y se guarda el valor del contador del temporizador antes y después de la ejecución. Luego se calcula la diferencia entre ambos valores y se almacena en una variable. Finalmente, se muestra el valor de la variable en los puertos GPIO.
  - Una sección de rutina de servicio de interrupción (ISR), donde se incrementa una variable cada vez que ocurre un desbordamiento del temporizador y se limpia el bit de bandera correspondiente.

# nuevo.asm

El código del archivo realiza las siguientes funciones:
- Inicializa el reloj principal del microcontrolador a 16 MHz y el reloj auxiliar a 32 kHz.
- Configura los pines P1.0 y P1.6 como salidas digitales y los pines P1.1 y P1.2 como entradas analógicas.
- Habilita el convertidor analógico-digital (ADC) de 12 bits con referencia interna y muestreo y retención, y selecciona los canales A1 y A2 como fuentes de entrada.
- Inicia una conversión del ADC cada vez que se presiona el botón conectado al pin P1.3, y almacena el resultado en los registros R5 y R6.
- Compara los valores del ADC con un umbral predefinido, y enciende o apaga los LEDs conectados a los pines P1.0 y P1.6 según el resultado de la comparación.
- Entra en modo de bajo consumo (LPM3) cuando no hay ninguna conversión del ADC en curso, y se despierta por la interrupción del botón o del ADC.

El código está estructurado en secciones que definen las constantes, las variables, las rutinas de inicialización, las rutinas de servicio de interrupción y el bucle principal. El código está comentado para facilitar su comprensión y depuración.

# prender.asm

-EL archivo contiene el código en lenguaje ensamblador para encender un LED conectado al pin 0 del puerto B de un microcontrolador Texas Instruments.
- El código se basa en las siguientes instrucciones:
  - .thumb: indica que el código se compila en modo Thumb, que usa instrucciones de 16 bits.
  - .equ: define una constante simbólica con un valor numérico.
  - .global: declara una etiqueta como global, para que pueda ser usada desde otros archivos.
  - .text: indica el inicio de la sección de código.
  - movs: mueve un valor inmediato o un registro a otro registro.
  - ldr: carga un valor desde una dirección de memoria a un registro.
  - orrs: realiza una operación lógica OR entre dos registros y almacena el resultado en el primero.
  - str: almacena un valor desde un registro a una dirección de memoria.
  - b: salta a una etiqueta dentro del mismo archivo.
- El código sigue los siguientes pasos:
  - Define las direcciones de memoria de los registros del puerto B (GPIO_PORTB_DATA_R y GPIO_PORTB_DIR_R) y el valor del pin 0 (LED).
  - Declara la etiqueta main como global y la sitúa al inicio de la sección de código.
  - Mueve el valor 0 al registro r0, que se usará como contador.
  - Carga la dirección de memoria del registro GPIO_PORTB_DIR_R al registro r1.
  - Carga el valor del pin LED al registro r2.
  - Realiza una operación OR entre los registros r1 y r2, para configurar el pin como salida.
  - Almacena el resultado en la dirección de memoria del registro GPIO_PORTB_DIR_R.
  - Carga la dirección de memoria del registro GPIO_PORTB_DATA_R al registro r3.
  - Realiza una operación OR entre los registros r0 y r2, para encender o apagar el LED según el valor del contador.
  - Almacena el resultado en la dirección de memoria del registro GPIO_PORTB_DATA_R.
  - Incrementa el valor del contador en uno y lo guarda en el registro r0.
  - Salta a la etiqueta main para repetir el proceso indefinidamente.
  
# seriefibonachi.asm

- Contiene un código en lenguaje ensamblador para calcular y mostrar la serie de Fibonacci en un microcontrolador Texas Instruments.
- La serie de Fibonacci es una sucesión de números naturales que empieza con 0 y 1 y cada término es la suma de los dos anteriores. Por ejemplo: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
- El código del archivo "seriefibonachi.asm" realiza los siguientes pasos:
    - Configura el puerto B como salida y lo inicializa en cero.
    - Asigna los valores iniciales de la serie (0 y 1) a dos registros llamados Penultimo y Ultimo.
    - Entra en un bucle donde suma los valores de Penultimo y Ultimo y los guarda en un registro llamado Suma.
    - Comprueba si el resultado de la suma es mayor o igual a 256. Si es así, sale del bucle y muestra el valor de Ultimo por el puerto B. Si no es así, continúa el bucle asignando el valor de Ultimo a Penultimo y el valor de Suma a Ultimo.
- El código está escrito siguiendo las convenciones del ensamblador para microcontroladores PIC16F84A, que son compatibles con los microcontroladores Texas Instruments. El código usa instrucciones como movwf, addwf, btfsc, goto y sleep para manipular los registros y controlar el flujo del programa.
