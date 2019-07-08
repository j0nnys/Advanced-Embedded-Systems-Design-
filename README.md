# Advanced-Embedded-Systems-Design- ARM mbed

Task 1:
Blink 8 LEDs in the extension board. There are 8 switches in the extension board. You can assign one of switches to one of the LEDs. When a switch is on, the corresponding LED blinks. When a switch is off, the corresponding LED is off. The blink rate can be changed according to the keyboard input from the host PC via Putty or Hyper terminal. There are four blink rates: 0.2s, 0.5s, 1.0s, and 2.0s. 

Task 2:
This task is to read a four-digit code from the keypad and show them on the LCD in the extension board. A default value of four-digit code “1234” should be initialised at the beginning of the program.
•	Initially the second line of the display should show left aligned “Code: ____”. The first line is empty.
•	When the user enters the first digit of the code, the second line of the display should show left aligned “Code: *___” with the “_” characters being replaced by * with each successive digit entered.
•	If the user presses the “C” key, then the last entered character should be deleted and replaced with “_” unless there are no characters left. 
•	When all four digits of the code have been entered, the first line of the display should display “Press B to set”. 
•	When the “B” key is entered and the new entered code is matched to the stored code, the program should show “CE860 A1” on the first line of the LCD.  The second line of the display should show left aligned “Code: ____” to take the new code.
•	When a wrong code is entered, the first line of the LCD is empty and the second line of the display should show left aligned “Code: ____” to take the new code.
