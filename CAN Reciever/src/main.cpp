#include <mbed.h>
#include <CAN3.h>

// Pin Defs
#define _MOSI A6
#define _MISO A5
#define _SCK A4
#define _INT A3
#define _NSS A2

Serial pc(SERIAL_TX, SERIAL_RX, 115200);
DigitalOut led(LED1);

SPI spi(_MOSI, _MISO, _SCK, NC);
CAN3 can(spi,_NSS); //spi, ncs, itr
DigitalOut cs(_NSS); // This can be any pin

int main() {
  wait_ms(100); // Wait for the setup stuff to calm down
  pc.printf("CAN Testing: %s\n", __TIME__);

  char data[1] = {52};
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