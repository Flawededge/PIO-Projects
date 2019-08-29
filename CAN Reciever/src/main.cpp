#include <mbed.h>
#include "CAN3.h"

Serial pc(SERIAL_TX, SERIAL_RX, 115200);
DigitalOut led(LED1);

SPI spi(A6, A5, A4, NC);
CAN3 can(spi,A3); //spi, ncs, itr
// DigitalOut cs(A3); // This can be any pin

int main() {
  wait_ms(100); // Wait for the setup stuff to calm down
  pc.printf("CAN Testing: %s\n", __TIME__);

  char data[1] = {0};
  can.frequency(125000);
  CANMessage msg(2002,data,1);
  
  while(1) {
    msg.data[0] = 0;
    pc.printf("%s: %d into ",__TIME__, msg.data[0]);
    can.read(&msg);
    pc.printf("%d\r\n",msg.data[0]);
    led = !led;
    wait(0.5);
  }
}