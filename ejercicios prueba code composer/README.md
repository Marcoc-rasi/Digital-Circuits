#CD141220-display.c

It is a C language program that is used to control a 7-segment display with an MSP430 microcontroller. The program performs the following functions:
- Defines the constants and global variables that are used in the program, such as the P1 port pins that are connected to the display, the value of the system clock frequency, and the number of times that the power cycle of the system is repeated. display.
- Initializes the microcontroller by setting the P1 port address, function, and output registers, the system clock control register, and the A0 timer control register.
- Define a function called "delay_ms" that receives as a parameter an integer that represents the time in milliseconds that you want to wait. The function uses timer A0 to generate an interrupt every 1 ms and counts the number of interrupts until the parameter value is reached. The function is used to generate delays between display state changes.
- Define a function called "display_7seg" that receives as a parameter an integer between 0 and 9 that represents the digit to be shown on the display. The function uses a 10-element array that contains the binary values corresponding to each digit and sends them to port P1 through an assignment operation. The function is used to show the numbers on the display.
- Defines a function called "main" that contains the main loop of the program. The function performs the following actions:
   - Declare a local variable called "i" that is used as a counter.
   - Start an infinite loop with the "while(1)" statement.
   - Inside the loop, iterate through the values from 0 to 9 with the statement "for(i=0; i<10; i++)".
   - Within the for loop, call the function "display_7seg" passing the value of "i" as a parameter.
   - After displaying each number, it calls the "delay_ms" function passing the value of 500 as a parameter to generate a delay of half a second.
   - At the end of the for loop, start the loop again from the beginning.
   
#CODPRAC9.C

The purpose of the program is to simulate the operation of a digital circuit that uses a 4-bit binary counter and a 7-segment BCD decoder to show the numbers from 0 to 9 on an LED display.
The program consists of the following parts:
- Inclusion of libraries: the necessary libraries for the use of predefined functions and constants are included, such as stdio.h, stdint.h and msp430.h.
- Definition of macros: macros are defined to facilitate the writing and reading of the code, such as BIT0, BIT1, BIT2 and BIT3, which represent the least significant bits of a byte.
- Declaration of global variables: global variables are declared to store the value of the binary counter and the value of the 7-segment BCD decoder, as well as a constant that stores the conversion table between both systems.
- Microcontroller configuration: the MSP430 microcontroller is configured to use the internal clock at 1 MHz, enable interrupts and configure ports P1 and P2 as digital outputs.
- Main function: it is the main function of the program, which is executed when it starts. In this function, the WDTCTL function is called to disable the watchdog timer, the BCSCTL1 function is called to set the clock divider, the CCTL0 function is called to set the A0 timer with continuous mode and SMCLK source, the function TACCR0 to set the comparison value of timer A0 to 50000, the CCR0 function is called to enable the comparison interrupt of timer A0, and an infinite loop is entered waiting for an interrupt to occur.
- Interrupt service routine (ISR) of timer A0: it is the function that is executed when timer A0 reaches the established comparison value. This function increments the value of the binary counter, applies a 4-bit mask to prevent it from exceeding 9, looks up the corresponding value in the 7-segment BCD decoder conversion table, and assigns that value to the port. P2 to turn on the appropriate segments of the LED display. Additionally, the value of the least significant bit of port P1 is inverted to produce a blinking effect on an LED connected to that pin. Finally, the interrupt flag of timer A0 is cleared.
