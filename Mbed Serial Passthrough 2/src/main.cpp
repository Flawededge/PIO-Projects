#include "mbed.h"

Serial pc(SERIAL_TX, SERIAL_RX, 115200);
Serial inter(D1, D0, 9600);
DigitalOut led(LED1);

// pc.printf("Press '1' to turn LED1 ON, '0' to turn it OFF\n");
// char c = pc.getc(); // Read hyperterminal
// pc.putc(c);
  
int main() {
    pc.printf("Starting!\n");
    while(true) {
        char c = pc.getc();
        char d = inter.getc();

        pc.putc(d);
        inter.putc(c);
    }
}