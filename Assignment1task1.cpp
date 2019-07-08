#include "mbed.h"
#include "math.h" 
Serial pc(USBTX, USBRX); // tx, rx
DigitalOut cs(p8);
SPI sw(p5, p6, p7);
BusIn cols(p14,p13,p12,p11);
BusOut rows(p26,p25,p24);

int main() {
    cs = 0;
    sw.format(16,0);
    sw.frequency(10000000);   
    while(1){     
            rows = 4;
            int switches = cols;
            rows = 5;
            switches = switches*16 + cols;
            int led;
            led = 3 * pow(switches,2.0);
            sw.write(led);
            cs = 1;
            cs = 0;
           
    }
}

