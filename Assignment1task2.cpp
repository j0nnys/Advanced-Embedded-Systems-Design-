#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(p15, p16, p17, p18, p19, p20); 
BusOut rows(p26,p25,p24);
BusIn cols(p14,p13,p12,p11);

char Keytable[] = { 'F', 'E', 'D', 'C',   
                    '3', '6', '9', 'B',   
                    '2', '5', '8', '0',   
                    '1', '4', '7', 'A'    
                   };                  
char keyCode[] = {'1','2','3','4'}; // This is the array used to store the keys pressed, it has only for numbers

/*The getKey() function checks 
  which button of the keypad 
  was pressed
 */
char getKey()
{
    int i,j;
    char ch=' ';
    
    for (i = 0; i <= 3; i++) 
    {
        rows = i; 
        for (j = 0; j <= 3; j++) 
        {           
            if (((cols ^ 0x00FF)  & (0x0001<<j)) != 0) 
            {
                ch = Keytable[(i * 4) + j];
            }            
        }        
    }
    return ch;
}

int main() 
{
    lcd.cls();
    int a,i;
    char b = ' ';
    while (1)
    {
        lcd.locate(0,1);
        lcd.printf("Code:____"); 
        for(a = 0; a < 4; a++) 
        {
            b = getKey(); // Get the key pressed from the keypad
            switch(b)
            {
                case ' ':
                    a--; 
                    break;
                case 'C':
                    if (a > 0)
                    {
                        a = a-2;
                        lcd.locate(6+a, 1);    
                        lcd.putc('_');                     
                    }
                    else if (a == 0)
                    {
                        a--;
                    }
                    break; 
                case 'B':
                    lcd.locate(0,0);
                    lcd.printf("CE860 A1"); 
                default:
                    if (keyCode[i]=b)
                    {
                        lcd.locate(5+a, 1);    
                        lcd.putc(b);
                        lcd.locate(0,1);
                        lcd.printf("Code:*___"); 
                        keyCode[a] = b;    // This stores a value in the array if a key was pressed  
                    }
            }   
        }
        wait(1);
    }
}
