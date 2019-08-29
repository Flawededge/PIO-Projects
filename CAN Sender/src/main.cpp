#include <mbed.h>
#include <FastPWM.h>
#include "MCP2515/CAN3.h"

DigitalOut led(LED1);
Serial pc(SERIAL_TX, SERIAL_RX, 115200);
FastPWM cryst(D5);

int main() {
  // Set the clock pin to 8 Mhz for the CAN chip
  cryst.prescaler(1); // Smallest prescaler possible to get the fastest clock possible
  cryst.period_ticks(10); // 80 Mhz / 10 = 8Mhz
  cryst.pulsewidth_ticks(5); // MCP needs 45% - 55% duty cycle, so half of period



  while(1) {
      pc.printf("LED Off\n");
      led = 0;
      wait(0.5);
      led = 1;
      wait_ms(0.2);
  }
}

// #include <mbed.h>
// #include "CAN3.h"
// #include <FastPWM.h>

// Serial pc(SERIAL_TX, SERIAL_RX, 115200);
// DigitalOut led(LED1);
// FastPWM cryst(D8);

// SPI spi(A6, A5, A4, NC);
// CAN3 can(spi,A3); //spi, ncs, itr
// // DigitalOut cs(A3); // This can be any pin


// int main() {
//   cryst.period_us((double)0.05);
//   wait_ms(100); // Wait for the setup stuff to calm down
//   pc.printf("CAN Testing: %s\n", __TIME__);

//   char data[1] = {0};
//   can.frequency(125000);
//   CANMessage msg(2002,data,1);
//   msg.data[0] = 253;
  
//   while(1) {
//     can.write(&msg);
//     pc.printf("%s: Send:%d\r\n",__TIME__, msg.data[0]);
//     led = !led;
//     wait(2);
//   }
// }
