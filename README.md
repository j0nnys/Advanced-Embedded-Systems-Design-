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

Project 2:
•	Step 1: Determine whether RMS or EDF will be used.
o	Initially, the first line of the display should show “RMS or EDF”. The second line is empty.
o	When the user enters a digit (‘0’ to ‘9’), the second line of the display should show this digit. However, the user can only enter one digit. When the user enters a new digit while there is already one digit shown in the display, the newly entered digit will not be taken and not shown in the display.
o	At any time, the user can press the ‘D’ key. If there is one digit already entered, it will be deleted, and the program is ready to take a new digit. 
o	When the user presses ‘C’ key, the current digit will be returned to the program. If ‘1’ is returned, the scheduling algorithm will be RMS. If ‘2’ is returned, the scheduling algorithm will be EDF. Otherwise, the display should show “Error”.
•	Step 2: Determine the number of tasks.
o	Initially, the first line of the display should show “Number of Tasks”. The second line is empty.
o	When the user enters a digit (‘0’ to ‘9’), the second line of the display should show this digit. However, the user can only enter one digit. When the user enters a digit while there is already one digit shown in the display, the newly entered digit will not be taken and not shown in the display.
o	At any time, the user can press the ‘D’ key. If there is one digit already entered, it will be deleted, and the program is ready to take a new digit. 
o	When the user presses ‘C’ key, the current digit will be returned to the program as the number of tasks. The number of tasks needs to be between 1 and 8. Otherwise, the display should show “Error”.
•	Step 3: Input the execution time and the period of each task
o	Suppose that the current task is task X.
o	Initially, the first line of the display should show “Task X Runtime”. The second line is empty.
o	When the user enters a digit (‘0’ to ‘9’), the second line of the display should show this digit. However, the user can only enter one digit. When the user enters a digit while there is already one digit shown in the display, the newly entered digit will not be taken and not shown in the display.
o	At any time, the user can press the ‘D’ key. If there is one digit already entered, it will be deleted, and the program is ready to take a new digit. 
o	When the user presses ‘C’ key, the current digit will be returned to the program. The execution time needs to between 1 and 9. Otherwise, the display should show “Error”.
o	After the execution time is taken, the first line of the display should show “Task X Period”. The second line is empty.
o	One similarly inputs the period value (between 1 and 9) of the task X in the second line of the display.
o	Repeat the above until the execution times and the periods of all the tasks are entered.
•	Step 4: Schedule these tasks.
o	Depending on the choice of RMS or EDF in Step 1, the tasks will be scheduled by the corresponding scheduling technique. Note that the super period for all the tasks should have been computed.
o	The first line of the display always shows the current time point. For example, if it is the start of the tenth second, the display should show “t=10”.
o	If task X is scheduled at the current time point, the corresponding LED on the extension board will be on. Since only one task can be scheduled, all other LEDs are off. Note that each task needs to be uniquely assigned to an LED.
o	Since the time unit of all the entered execution time and period is one second, the program would wait for one second to mimic the actual scheduling of each task. For example, there would be one second delay for the switching from “t=2” to “t=3” in the first line of the display.
o	Whenever an instance of a task X is completed, the second line of the display should show “Task X Completes”. After the one second, the second line of the display should be cleared.
o	Whenever an instance of a task X misses its deadline, the second line of the display should show “Task X Misses”. After the one second, the second line of the display should be cleared.
o	When all the tasks are completed, the second line of the display should show “Finish”.

