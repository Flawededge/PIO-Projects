#include <mbed.h>
#include <MCP2515.h>

#define DEBUG

#ifdef DEBUG
#define debug(x) pc.printf(x)
#define timeTag pc.printf("%s", __TIME__)
#else
#define debug(x)
#define timeTag
#endif

// Pin Defs
#define _MOSI A6
#define _MISO A5
#define _SCK A4
#define _INT A3
#define _NSS A2

#define SCK A4
#define MISO A5
#define MOSI A6
#define SS A2
#define RESET A0

// Base stuff to init
DigitalOut led(LED1);
Serial pc(SERIAL_TX, SERIAL_RX, 115200);

#define _10kbps
SPI spi(_MOSI, _MISO, _SCK);
DigitalOut ss(_NSS);
MCP2515 can(spi, _NSS);

int main() {
    pc.printf("\n-================================-\n");
    timeTag;
    debug(": Init: CAN:\n");
    can.reset();
    can.setMode(MCP2515Mode(LOOPBACK));
    can.baudConfig(10);
    
    byte outStuff[8];
    byte inStuff[8];
    byte len;
    unsigned short id;
    volatile byte command[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    while(1) {
        byte command[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        pc.scanf("%8s", command);
        pc.printf("Sending: %s\n", command);

        pc.printf("Read status: %d\n", can.readStatus());
        // while((can.readStatus() & 0x80) == 0x80) {
            // Send the data
            
            can.load_ff_0(8, 1, command); // Transmit the data
            can.send_0(); // Select send buffer 0
            can.readDATA_ff_0(&len, inStuff, &id); // Recieve the data
            
            // Output what's been found BUFFER 1
            pc.printf("Data: %d bytes long: ", len); 
            for (int i = 0; i < len; i++) {
                pc.printf("%c", inStuff[i]);
            } pc.printf("\n");
        // }

        // Flash the LED and wait a bit
        led = !led;
        wait(0.5);
    }
}