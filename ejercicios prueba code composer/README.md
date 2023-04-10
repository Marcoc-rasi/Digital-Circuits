## CD141220-display.c

Este código es un programa en C para un microcontrolador TM4C1294NCPDT de Texas Instruments que interactúa con un display LCD de 16x2. El código define varias funciones para inicializar el display, enviar comandos y datos, y verificar el estado de la bandera de ocupado del display.
La función INILCD inicializa el display para usar una interfaz de 8 bits, 2 líneas y caracteres de 5x7. También enciende el display con cursor y destello, borra el contenido del display y configura el comportamiento del cursor para que se incremente y se desplace al escribir.
Las funciones ESCCOM y ESCDAT envían comandos y datos al display, respectivamente. Estas funciones utilizan la función _E para generar un pulso en la terminal E del display y enviar el comando o dato.
La función BUSY verifica el estado de la bandera de ocupado del display y espera hasta que sea cero. Esta función utiliza la función LEECON para leer el valor del registro de control del display y verificar si la bandera de ocupado está activa.

# CODPRAC9.C



# SU-HCSR04 distance meter.txt

The code is based on the principle that the sensor sends out a sound wave and measures the time it takes to receive its echo. Knowing the speed of sound, the distance to the object can be calculated.
The code is divided into several parts:
- The first part defines the constants and global variables that will be used in the program. The sensor connection pins (TRIG and ECHO), the speed of sound (343 m/s) and the variable that will store the measured distance are defined.
- The second part. In this function, the sensor pins are configured as output (TRIG) or input (ECHO), and the serial communication is initialized at 9600 baud to display the results on the serial monitor.
- The third part is a loop , which is executed repetitively. In this function, the distance measurement process is carried out following these steps:
- A 10 microsecond pulse is sent to the TRIG pin to activate the sensor.
- Wait for the ECHO pin to change its state to HIGH, which indicates that the sensor has sent the sound wave.
- The time that the ECHO pin remains in the HIGH state is measured, which indicates that the sensor has received the echo of the sound wave.
- The distance to the object is calculated using the formula: distance = (time * speed of sound) / 2. It is divided by two because the time measured is the round trip of the sound wave.
- The distance in centimeters is shown by the serial monitor.
- Wait a second before repeating the process.
The operation and parts of the program can be described as follows:
- Includes the necessary libraries for the use of the microcontroller and the sensor, such as <msp430.h>, < driverlib.h > and <hcsr04.h>.
- Defines some constants and global variables, such as the system clock frequency (SMCLK), the waiting time between measurements (DELAY), and the speed of sound in air (SOUND_SPEED).
- Configure the microcontroller pins that connect to the sensor, such as P1.0 for the red LED, P1.1 for the green LED, P2.0 for the TRIG pin, and P2.1 for the ECHO pin.
- Set timer A0 to generate an interrupt every 1 ms, which is used to measure the time of flight of the ultrasonic pulse.
- Configure the USCI_A0 module to communicate via UART with a speed of 9600 bps, which is used to send the distance data to the serial port.
- Define a function called Init_HCSR04, which initializes the sensor and puts it in standby mode.
- Define a function called Start_Measure , which sends a 10 us pulse to the TRIG pin to start a measurement.
- Define a function called Stop_Measure , which stops the measurement and calculates the distance in centimeters from the time of flight of the ultrasonic pulse.
- Defines a function called ISR_TA0, which is the service routine for timer A0 interrupt. This function increments a variable called counter every 1ms and checks the status of the ECHO pin to determine if the ultrasonic pulse has been sent or received.
- Defines a function called ISR_PORT2, which is the port 2 interrupt service routine. This function is activated when there is a change in the logic level of the ECHO pin and calls the Start_Measure or Stop_Measure functions accordingly .
- Define a function called main , which is the main function of the program. This function performs the following actions:
- Disable the watchdog timer to avoid unexpected reboots.
- Set the system clock to use the DCO oscillator at 16 MHz.
- Calls the configuration functions of the pins, timer, UART and sensor.
- Enable global interrupts and go into an infinite loop.
- Inside the loop, it waits for a time defined by the DELAY constant and then sends a command to the sensor to start a new measurement.
- If the measurement is successful, it turns on the green LED and sends the distance by UART in a text string format. If it is not, it lights the red LED and sends an error message by UART.
The program is well structured and documented, following good C programming practices. In addition, it uses functions and libraries provided by Texas Instruments to facilitate the use of the microcontroller and the sensor.


# adc-pwm.c

The program uses the analog-to-digital converter (ADC) and the pulse width modulator (PWM) to control the speed of a direct current (DC) motor. The program performs the following functions:
- Configures the ADC to sample the signal from a potentiometer connected to an analog input. The ADC is periodically activated by an internal timer and generates an interrupt upon completion of the conversion.
- Configures the PWM to generate an output signal with a fixed frequency and a variable duty cycle. The PWM is synchronized with the ADC so that it changes the duty cycle based on the value read by the ADC.
- Configure the DC motor to be connected to the PWM output and powered by an external source. The motor varies its speed according to the PWM signal.
- Implements a control function that adjusts the PWM duty cycle based on the ADC value, using a simple linear equation. The control function is executed in the ADC interrupt service routine.
It is a program to control the duty cycle of a PWM signal using the analog input of an ADC converter:
- The program includes the necessary libraries to use the functions and constants defined by the microcontroller manufacturer, such as F2802x_Device.h, F2802x_Examples.h and F2802x_EPwm_defines.h.
- The program defines some constants and global variables to configure the ADC and PWM parameters, such as ADC_MODCLK, ADC_RESOLUTION, EPWM1_TIMER_TBPRD and EPWM1_MAX_CMPA.
- The program contains a function called InitEPwm1 Example( ) that initializes the ePWM1 module of the microcontroller, establishing the operating mode, the frequency, the counter and the comparator. This function also enables the generation of a start of conversion (SOC) signal from the ePWM1 to the ADC every time the counter reaches the maximum value (TBPRD).
- The program contains a function called InitAdc ( ) that initializes the ADC module of the microcontroller, establishing the clock, the resolution, the input channel (ADCINA0) and the firing mode (by software or by hardware). This function also enables the generation of an interrupt (ADCINT) each time an ADC conversion is completed.
- The program contains a function called Adc_ Config ( ) that configures the ADC registers to select the input channel, the trigger mode and the trigger source (in this case, the SOC generated by the ePWM1).
- The program contains a function called main ( ) that performs the following actions:
- Initializes the system and enables global interrupts.
- Call the functions InitEPwm1 Example( ), InitAdc () and Adc_Config () to configure the ePWM1 and ADC modules.
- Enters an infinite loop where it waits for the ADC interrupt to occur.
The program contains a function called adc_isr ( ) that is executed every time the ADC interrupt occurs. This function performs the following actions:
- Reads the converted value from the ADC and stores it in a variable called i_AdcResult .
- Calculate the value of the ePWM1 comparator based on the value of the ADC, using a simple rule of three. The value of the comparator determines the duty cycle of the PWM signal.
- Updates the EPwm1Regs.CMPA.half .CMPA register with the new value of the comparer.
- Clears the ADC interrupt flag and acknowledges the interrupt to the system.
In this way, the program manages to synchronize the change in the PWM duty cycle with the analog voltage conversion, using the ADC interrupt as a control mechanism. The period of the PWM signal is kept constant and depends on the value defined for EPWM1_TIMER_TBPRD. The PWM signal is generated on the GPIO pin corresponding to PWM1A.

# adc.c

It is a program that uses the analog-to-digital converter (ADC) of a Texas Instruments microcontroller to read an analog signal and send it over a serial interface. The operation and each part of the program can be described as follows:
- Includes the necessary libraries for the use of the ADC, the serial interface and the standard C functions.
- Define some constants and global variables to configure the ADC and the serial interface, as well as to store the data read.
- Define a function called " init_ADC " that initializes the ADC with the appropriate parameters, such as mode of operation, resolution, input channel, sample rate, and clock source.
- Define a function called " init_UART " that initializes the serial interface with the appropriate parameters, such as baud rate, number of data bits, parity bit, and stop bit.
- Define a function called " send_data " that sends the data read by the ADC through the serial interface, using a simple protocol that consists of sending a start byte, two bytes with the ADC value and an end byte.
- Defines a function called " main " which is the main function of the program and which performs the following actions:
- Call the functions " init_ADC " and " init_UART " to configure the ADC and the serial interface.
- Enable global interrupts and ADC interrupts.
- It enters an infinite loop that does nothing, since the program works by interruptions.
- Defines a function called "ADC_ISR" which is the ADC interrupt service routine and which performs the following actions:
- Reads the value of the ADC and stores it in a global variable.
- Call the " send_data " function to send the ADC value through the serial interface.
- Clears the ADC interrupt flag to allow new interrupts.
This program is an example of how to use the ADC of a Texas Instruments microcontroller to perform analog-to-digital conversion and communicate with another device via a serial interface. An experienced programmer could modify this program to suit their specific needs, such as changing the input channel of the ADC, the baud rate of the serial interface, or the communication protocol used.

# hc05.c

It is a program written in C language to control an HC-05 Bluetooth module connected to a Texas Instruments microcontroller. The program performs the following functions:

- Initializes the microcontroller and configures the input and output pins.
- Initializes the HC-05 Bluetooth module and puts it in configuration mode using the KEY pin.
- Send AT commands to the HC-05 Bluetooth module to change its name, PIN code, communication speed and work mode (master or slave).
- Receives the responses from the HC-05 Bluetooth module and displays them on the microcontroller's serial console.
- Exits the HC-05 Bluetooth module configuration mode and puts it in communication mode.
- Send and receive data through the serial port of the HC-05 Bluetooth module.

The program is divided into several parts:

- The necessary libraries for the operation of the microcontroller and the HC-05 Bluetooth module.
- The definitions of the pins and constants used in the program.
- Global variables to store the data received and sent by the HC-05 Bluetooth module.
- The auxiliary functions to initialize the microcontroller, the HC-05 Bluetooth module and send and receive data through the serial port.
- The main function that calls the auxiliary functions and runs the program.
The program allows a Texas Instruments microcontroller to communicate with an HC-05 Bluetooth module using the UART protocol. The program performs the following functions:
- Initializes the system clock and the UART0 serial port with a rate of 9600 baud.
- Configure pin P1.0 as a digital output to control the red LED of the microcontroller.
- Configure pin P1.3 as a digital input with a pull -up resistor to read the state of the S2 button of the microcontroller.
- Define a function called " UARTSend " that receives a pointer to a character string and sends each character out the UART0 serial port.
- Define a function called " UARTReceive " that reads a character from the UART0 serial port and returns it as a result.
- Defines a function called "HC05Init" that sends the necessary commands to configure the HC-05 Bluetooth module in slave mode, with the name "TI_CC2541" and the pin "1234".
- It defines a function called "HC05Send" that receives a pointer to a character string and sends it to the HC-05 Bluetooth module using the " UARTSend " function.
- Define a function called "HC05Receive" that receives a pointer to a string and reads the data from the HC-05 Bluetooth module using the " UARTReceive " function until it finds the '\n' character or fills the maximum size of the string .
- In the main loop, call the "HC05Init" function to initialize the HC-05 Bluetooth module.
- In each iteration of the loop, it reads the state of the S2 button and if it is pressed, turns on the red LED and sends the "LED ON\n" string to the HC-05 Bluetooth module using the "HC05Send" function. If it is not pressed, it turns off the red LED and sends the string "LED OFF\n" to the HC-05 Bluetooth module using the same function.
- Also in each iteration of the loop, it calls the "HC05Receive" function to receive a character string from the HC-05 Bluetooth module and stores it in an array called "buffer". If the received string is equal to "ON\n", it turns on the red LED. If equal to "OFF\n", turn off the red LED. If it is different, it does nothing.

# main.c

This program is written in C language and is designed for a Texas Instruments MSP430 family microcontroller.
main.c " program consists of the following parts:
- Inclusion of libraries: at the beginning of the file the necessary libraries are included for the operation of the program, such as "msp430.h" that contains the definitions of the registers and the microcontroller peripherals, and "stdio.h" that allows the use of standard input and output functions.
- Definition of constants: some constants that will be used in the program are defined below , such as "LED1" and "LED2" that correspond to the pins where the LEDs are connected , and "FREQ" that indicates the system clock frequency.
- Declaration of global variables: then some global variables that will be used in the program are declared, such as "counter" that stores the number of times the button has been pressed, and "state" that indicates the current state of the LEDs .
- System configuration: in the " main " function, the initial configuration of the system is carried out, such as the adjustment of the clock frequency, the configuration of the pins as inputs or outputs, the enabling of the interrupts and the initiation of the infinite loop.
- Interrupt routine: the "PORT1_ISR" function defines the interrupt routine that is executed when a change is detected in the pin where the button is connected. This routine increments the counter, changes the state of the LEDs according to the value of the counter, and clears the interrupt flag.
- Helper function: in the function " delay_ms " a helper function is defined that generates a delay in milliseconds using a for loop . This function is used to prevent button bounce.
The goal of the program is to make the LEDs blink alternately each time the button is pressed. For example, if the LEDs are off and the button is pressed once, LED1 turns on and LED2 turns off. If the button is pressed again, LED1 turns off and LED2 turns on. If the button is pressed three times in a row, both LEDs light up. If the button is pressed four times in a row, both LEDs turn off.

# timers.c

This file contains a program that uses the Texas Instruments MSP430 microcontroller timers to generate periodic interrupts and change the state of an LED.
The program is made up of the following parts:
intrinsics.h " are included, which contain the definitions of the registers and functions of the microcontroller.
- Main clock configuration: the main clock (MCLK) is configured at a frequency of 1 MHz using the internal oscillator (DCO) and the divider by 1 (DIVM_0).
- Port 1 configuration: pin 1.0 is configured as output and assigned the red LED function (P1OUT and P1DIR).
- Configuration of timer A0: timer A0 is configured to generate an interruption every 500 ms using the auxiliary clock (ACLK) at a frequency of 32.768 kHz and the divider by 8 (ID_3). The counter overflow interrupt (TAIE) is enabled and the interrupt flag (TAIFG) is cleared.
- Enabling global interrupts: the GIE bit of the status register (SR) is enabled using the __ enable_ interrupt ( ) function.
- Infinite loop: an infinite loop is entered where nothing is done other than waiting for the timer interruption to occur .
- Interrupt service routine (ISR) of timer A0: the function __ attribute __(( interrupt ( TIMER0_A1_VECTOR))) Timer_A0_ISR() is defined, which is executed when the interruption of timer A0 occurs. Within this function you do the following:
- It checks if the interruption is due to counter overflow (TAIV == TA0IV_TAIFG).
- The state of the red LED is changed using an XOR operator (^) between the P1OUT register and the value 0x01.
timer interruption flag is cleared (TA0CTL &= ~TAIFG).
This program is a simple example of how to use the MSP430 microcontroller timers to generate periodic events and control external devices such as LEDs .

# uart.c

The " uart.c " file is a program that implements serial communication between a Texas Instruments microcontroller and a peripheral device using the UART (Universal Asynchronous Receiver/ Transmitter ) protocol. The program performs the following functions:
- Initializes the UART peripheral using the UART_init ( ) function, which sets the communication parameters such as baud rate, number of data bits, parity bit, and stop bit.
- Enable UART interrupts using the UART_ enableInterrupt ( ) function, which allows the microcontroller to respond to events such as receiving or sending data.
- Defines an Interrupt Service (ISR) function called UART_ISR ( ), which is executed whenever a UART interrupt is generated. The function checks the type of interrupt and performs the corresponding actions, such as reading or writing data in the UART buffer, or handling possible communication errors.
- Define a main function called main ( ), which performs an infinite loop and sends a welcome message to the peripheral device using the UART_write ( ) function. The function also reads the data received from the peripheral using the UART_ read ( ) function and displays it on the console using the printf () function.
- Includes the necessary libraries for the program to work, such as "ti/ devices /msp432p4xx/ driverlib / driverlib.h ", which contains the definitions and functions of the UART driver , and "ti/ devices /msp432p4xx/ inc / msp.h ", which contains the definitions and macros of the microcontroller.
The program is written in C language and follows a professional and structured style. Each function has a comment that describes its purpose and its parameters. The code is correctly indented and uses meaningful names for variables and constants. The program uses the microcontroller peripheral UART0, which connects to pins P1.2 (RX) and P1.3 (TX). The program can be compiled and run using the Code development environment. Texas Instruments Composer Studio.


