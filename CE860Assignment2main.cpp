/*KAROPOULOS IOANNIS
1808002
Postgraduate Student
*/


#include "mbed.h"
#include "TextLCD.h"

Serial pc(USBTX, USBRX);
TextLCD lcd(p15, p16, p17, p18, p19, p20);
BusOut rows(p26, p25, p24);
BusIn cols(p14, p13, p12, p11);
DigitalOut myled(LED1);
SPI sw(p5, p6, p7);
DigitalOut cs(p8);
int show_deadline_miss;

#define MAXTASK 8
#define MAXPERIOD 100
#define RMS 1
#define EDF 2

char Keytable[] = { 'F', 'E', 'D', 'C',
'3', '6', '9', 'B',
'2', '5', '8', '0',
'1', '4', '7', 'A'
};

char getKey()
{
	int i, j;
	char ch = ' ';

	for (i = 0; i <= 3; i++)
	{
		rows = i;
		for (j = 0; j <= 3; j++)
		{
			if (((cols ^ 0x00FF)  & (0x0001 << j)) != 0)
			{
				ch = Keytable[(i * 4) + j];
			}
		}
	}
	return ch;
}

//Function of the input character and number from the keypad -------------------------------------------------

int input_number()
{
	char keyCode;
	int number = -1;
	int a = 0;
	char b;

	while (1)
	{
		b = getKey();
		if (b == 'C')
			break;
		if (b != ' ')
		{
			if (b == 'D')
			{
				if (a == 1)
				{
					a = 0;
					lcd.locate(0, 1);
					lcd.putc(' ');
					keyCode = '0';
					wait(0.5);
				}
			}
			else if (a == 0)
			{
				lcd.locate(0, 1);
				lcd.putc(b);
				keyCode = b;
				a++;
				wait(0.5);
			}
		}
	}
	wait(0.5);
	number = keyCode - '0';
	if (number < 1 || number > 9)
	{
		lcd.cls();
		lcd.printf("Number error");
		exit(1);
	}
	return(number);
}

// Demonstration of corresesponding LED --------------------------------------------------------------------

void led_task(int task)
{
	int num = 1 << (task - 1);
	int c = 0, j, k;
	if (task == 0)
		num = 0;
	for (j = 7;j >= 0;j--)
	{
		k = num >> j;
		if (k & 1)
		{
			c = c + (1 << (2 * j)) + (1 << (2 * j + 1));
		}
	}
	sw.write(c);
	cs = 1;
	cs = 0;
	wait(1);
}

// The Demonstration of RMS scheduling -------------------------------------------------------------------------

int RMS_scheduling(int *task_active, int *task_period, int task_number)
{
	int i;
	int smallest_period = MAXPERIOD + 1;
	int smallest_period_task = -1;

	for (i = 1; i <= task_number; i++)
	{
		if (task_active[i] == 1)
		{
			if (task_period[i] < smallest_period)    //the mimimum the period the highest the priority
			{
				smallest_period = task_period[i];
				smallest_period_task = i;
			}
		}
	}
	return(smallest_period_task);
}

// The Demonstration of EDF scheduling -------------------------------------------------------------------

int EDF_scheduling(int *task_active, int *task_deadline, int task_number)
{
	int i;
	int earliest_deadline = 1000;
	int earliest_deadline_task = -1;

	for (i = 1; i <= task_number;i++)
	{
		if (task_active[i] == 1)
		{
			if (task_deadline[i] < earliest_deadline)
			{
				earliest_deadline = task_deadline[i];
				earliest_deadline_task = i;
			}
		}
	}
	return(earliest_deadline_task);
}
int main()
{
	int scheduling_mode = RMS;
	int task_executiontime[MAXTASK + 1] = { 0,2,4 };
	int task_period[MAXTASK + 1] = { 0,5,7 };
	int task_deadline[MAXTASK + 1];
	int task_number = 2;
	int i;
	cs = 0;
	sw.format(16, 0);
	sw.frequency(1000000);

	lcd.cls();
	lcd.printf("RMS or EDF?");
	i = input_number();
	if (i == 1)
		scheduling_mode = RMS;
	else if (i == 2)
		scheduling_mode = EDF;
	else
	{
		lcd.cls();
		lcd.printf("Error");
		exit(1);
	}

	// Determination of the task number -------------------------------------------

	lcd.cls();
	lcd.printf("Task Number");
	task_number = input_number();

	if (task_number > MAXTASK)
	{
		lcd.cls();
		lcd.printf("Task Number Error");
		exit(1);
	}

	// Calculation of the Runtime and the Period ------------------------------------------------

	for (i = 1; i <= task_number; i++)
	{
		lcd.cls();
		lcd.printf("Task %d Runtime", i);
		task_executiontime[i] = input_number();
		lcd.cls();
		lcd.printf("Task %d Period", i);
		task_period[i] = input_number();
	}

	// Computation of superperiod ---------------------------------------------------------

	int super_period = 1;
	int flag;     // variable that increases each time     

				  // Computation of superperiod for all the tasks -------------------------------------------

	while (1)
	{
		flag = 0;
		for (i = 1; i <= task_number; i++)
		{
			if (super_period%task_period[i] == 0)
				flag++;
		}
		if (flag == task_number)
			break;
		super_period++;
	}
	lcd.cls();

	// Demonstration of the tasks, it shows the priority between the tasks ---------------------------

	int t;
	int task_active[MAXTASK + 1], task_time_to_be_scheduled[MAXTASK + 1];
	for (i = 1; i <= task_number; i++)
	{
		task_active[i] = 0;
		task_time_to_be_scheduled[i] = 0;
	}
	for (t = 0; t<super_period; t++)
	{
		lcd.locate(0, 0);
		lcd.printf("t=%d", t);
		for (i = 1; i <= task_number; i++)
		{
			if (t%task_period[i] == 0)
			{
				task_active[i] = 1;

				// Demonstration of task misses ----------------------------------------------------

				if (task_time_to_be_scheduled[i]>0)
				{
					lcd.locate(0, 1);
					lcd.printf("Task %d misses", i);
					wait(0.5);
					show_deadline_miss++;
				}
				task_time_to_be_scheduled[i] = task_executiontime[i];
				task_deadline[i] = t + task_period[i];
			}
		}

		int highest_priority_task;
		if (scheduling_mode == RMS)
		{
			highest_priority_task = RMS_scheduling(task_active, task_period, task_number);
		}
		else
		{
			highest_priority_task = EDF_scheduling(task_active, task_deadline, task_number);
		}
		if (highest_priority_task == -1)
		{
			led_task(0);
			continue;
		}
		task_time_to_be_scheduled[highest_priority_task]--;
		if (task_time_to_be_scheduled[highest_priority_task] <= 0)
		{
			task_active[highest_priority_task] = 0;
			lcd.locate(0, 1);
			lcd.printf("Task %d completes", highest_priority_task);
		}
		led_task(highest_priority_task);
		lcd.cls();
	}
	lcd.cls();
	lcd.printf("%d Miss, Finish", show_deadline_miss);
}