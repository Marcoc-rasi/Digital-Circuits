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
