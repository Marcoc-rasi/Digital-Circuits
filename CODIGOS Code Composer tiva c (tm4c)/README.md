# Stopwatch.asm

- This file contains the assembly language source code for a digital timer running on a Texas Instruments microcontroller
- The code is divided into several sections that are described below:
   - The .text section contains the instructions of the main program and the subroutines that are called from it. The main program initializes the microcontroller, configures the input and output ports, enables interrupts, and enters an infinite loop. The subroutines perform the following functions:
     - init subroutine: initializes the system clock, the A0 timer and the LCD.
     - Start subroutine: starts timer A0 and displays the message "START" on the LCD.
     - Subroutine stop: stops timer A0 and displays the message "STOP" on the LCD.
     - Reset subroutine: resets the A0 timer counter and shows the message "RESET" on the LCD.
     - Display subroutine: converts the value of the A0 timer counter in decimal format and shows it on the LCD with two integer digits and two decimals.
     - Delay subroutine: generates a 500 ms delay using timer A1.
   - The .bss section contains the global variables that are used in the program. These variables are:
     - flag: a flag indicating whether the timer is running or stopped.
     - digit: a four-element array that stores the digits of the value of the A0 timer counter.
     - lcd_data: an eight element array that stores the data that is sent to the LCD.
   - The .data section contains the constants that are used in the program. These constants are:
     - lcd_cmd: a four element array that stores the commands that are sent to the LCD to configure it.
     - lcd_msg: a four element array that stores the messages that are displayed on the LCD based on the timer status ("START", "STOP", "RESET" and " ").
     - hex2dec: a hexadecimal to decimal conversion table to make it easy to convert the digits of the A0 timer counter.
   - The .isr section contains the interrupt service routines (ISR) that are executed when certain events occur. These ISRs are:
     - ISR_TA0CCR0: executed when the A0 timer counter reaches the CCR0 comparison value. This ISR increments the A0 timer counter and calls the display subroutine to update the LCD.
     - ISR_PORT1: Executed when a change in the state of port 1 pins is detected. This ISR reads pins P1.3, P1.4, and P1.5, which are connected to three buttons, and calls the start subroutines , stop or reset as appropriate.
- The code is written for a Texas Instruments MSP430F5529 microcontroller, which has a 16-bit CPU, 128KB FRAM, 8KB SRAM, 12bit ADC, analog comparator, and various digital peripherals.
- The code uses GNU Assembler Syntax (GAS), which is compatible with Texas Instruments' Code Composer Studio (CCS) development environment.
- The code is well commented and documented, following good assembly language programming practices.

# Example.asm

- This file contains assembly language code for a Texas Instruments MSP430 family microcontroller.
- The code performs the following functions:
   - Initializes the main clock of the microcontroller to 16 MHz and the auxiliary clock to 32 kHz.
   - Configure pins P1.0 and P1.6 as digital outputs and pins P2.0 and P2.1 as analog inputs.
   - Enables the 12-bit analog-to-digital converter (ADC) and selects channels A0 and A1 for the analog inputs.
   - Establishes an infinite cycle that reads the values of the analog inputs and compares them with a predefined threshold.
   - If the value of input A0 is greater than the threshold, it turns on the LED connected to pin P1.0. If not, turn it off.
   - If the value of input A1 is greater than the threshold, it turns on the LED connected to pin P1.6. If not, turn it off.
   - Uses conditional, arithmetic, and logical jump instructions to perform comparisons and input/output operations.
- The code is written in a professional style, following assembly language conventions for naming, indenting, and commenting.
- The code is optimized to take advantage of the low power and high performance characteristics of the MSP430 microcontroller.

# Time.asm

- The code aims to measure the execution time of an instruction using the microcontroller's internal timer and display the result on the GPIO ports.
- The code is made up of the following parts:
   - A section for the definition of constants and variables, where the symbolic names are assigned to the memory addresses and registers of the microcontroller, as well as the initial values of some variables.
   - An initialization section, where the microcontroller operating modes, system clock, timer, GPIO ports and timer overflow interrupt are configured.
   - A main code section, where the instruction to be measured is executed (in this case, an addition) and the value of the timer counter is saved before and after the execution. The difference between the two values is then calculated and stored in a variable. Finally, the value of the variable on the GPIO ports is displayed.
   - An interrupt service routine (ISR) section, where a variable is incremented each time a timer overflow occurs and the corresponding flag bit is cleared.

# new.asm

The code in the file performs the following functions:
- Initializes the main clock of the microcontroller to 16 MHz and the auxiliary clock to 32 kHz.
- Configure pins P1.0 and P1.6 as digital outputs and pins P1.1 and P1.2 as analog inputs.
- Enables the 12-bit analog-to-digital converter (ADC) with internal reference and sample and hold, and selects channels A1 and A2 as input sources.
- Starts an ADC conversion each time the button connected to pin P1.3 is pressed, and stores the result in registers R5 and R6.
- Compares the ADC values with a predefined threshold, and turns the LEDs connected to pins P1.0 and P1.6 on or off according to the comparison result.
- Enters low power mode (LPM3) when there is no ADC conversion in progress, and wakes up by button or ADC interrupt.

The code is structured in sections that define the constants, variables, initialization routines, interrupt service routines, and the main loop. The code is commented to make it easier to understand and debug.

# turn on.asm

-The file contains the assembly language code to turn on an LED connected to pin 0 of port B of a Texas Instruments microcontroller.
- The code is based on the following instructions:
   - .thumb: Indicates that the code is compiled in Thumb mode, which uses 16-bit instructions.
   - .equ: defines a symbolic constant with a numeric value.
   - .global: declares a label as global, so it can be used from other files.
   - .text: indicates the beginning of the code section.
   - movs: moves an immediate value or a record to another record.
   - ldr: load a value from a memory address to a register.
   - orrs: performs a logical OR operation between two registers and stores the result in the first one.
   - str: stores a value from a register to a memory address.
   -b: Jump to a label within the same file.
- The code follows the following steps:
   - Defines the memory addresses of the port B registers (GPIO_PORTB_DATA_R and GPIO_PORTB_DIR_R) and the value of pin 0 (LED).
   - Declare the main tag as global and place it at the beginning of the code section.
   - Moves the value 0 to register r0, which will be used as a counter.
   - Loads the memory address of the GPIO_PORTB_DIR_R register to the r1 register.
   - Load the value of the LED pin to register r2.
   - Performs an OR operation between registers r1 and r2, to configure the pin as an output.
   - Stores the result in the memory address of the GPIO_PORTB_DIR_R register.
   - Loads the memory address of the GPIO_PORTB_DATA_R register to the r3 register.
   - Performs an OR operation between registers r0 and r2, to turn the LED on or off according to the value of the counter.
   - Stores the result in the memory address of the GPIO_PORTB_DATA_R register.
   - Increases the value of the counter by one and stores it in register r0.
   - Jump to the main tag to repeat the process indefinitely.

# fibonachistring.asm

- Contains assembly language code to calculate and display the Fibonacci series on a Texas Instruments microcontroller.
- The Fibonacci series is a sequence of natural numbers that begins with 0 and 1 and each term is the sum of the previous two. For example: 0, 1, 1, 2, 3, 5, 8, 13, 21, ...
- The code of the file "seriefibonachi.asm" performs the following steps:
     - Configures port B as an output and initializes it to zero.
     - Assigns the initial values of the series (0 and 1) to two registers called Penultimate and Last.
     - Enters a loop where it adds the Penultimate and Last values and saves them in a register called Sum.
     - Check if the result of the sum is greater or equal to 256. If so, it exits the loop and displays the value of Last on port B. If not, it continues the loop by assigning the value of Last to Penultimate and the value of Sum to Last.
- The code is written following the assembler conventions for PIC16F84A microcontrollers, which are compatible with Texas Instruments microcontrollers. The code uses instructions such as movwf, addwf, btfsc, goto, and sleep to manipulate registers and control the flow of the program.
