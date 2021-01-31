#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <ModbusMaster.h>
#include <TextLCD.h>

ModbusMaster node;
TextLCD lcd(D11, D31, D32, D33, D34, D35);
BufferedSerial meter(SERIAL1_TX, SERIAL1_RX, 9600);


// main() runs in its own thread in the OS
int main()
{
    static uint32_t i;
    uint8_t j, result;
    uint16_t data[6];
    node.begin(63, meter);
    while(true){ 
        i++;

        /*// set word 0 of TX buffer to least-significant word of counter (bits 15..0)
        node.setTransmitBuffer(0, lowWord(i));

        // set word 1 of TX buffer to most-significant word of counter (bits 31..16)
        node.setTransmitBuffer(1, highWord(i));

        // slave: write TX buffer to (2) 16-bit registers starting at register 0
        result = node.writeMultipleRegisters(0, 2);

        // slave: read (6) 16-bit registers starting at register 2 to RX buffer
        result = node.readHoldingRegisters(2, 6);*/

        result = node.readHoldingRegisters(1, 1);

        lcd.printf("Result %i", result);

        // do something with data if read is successful
        if (result == node.ku8MBSuccess)
        {
            //lcd.printf("Result %i", result);
            for (j = 0; j < 6; j++)
            {
                data[j] = node.getResponseBuffer(j);
            }
        }
    }
}
