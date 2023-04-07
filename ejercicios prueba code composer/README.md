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
