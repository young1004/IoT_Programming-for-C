#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>

#define LED_RED 7
#define LED_GREEN 21
#define LED_BLUE 22

#define ADC_CS 8
#define ADC_CH3 3
#define SPI_CH 0

#define SPI_SPEED 500000

int main(void)
{
    int i, adcValue = 0;
    unsigned char buf[3];
    char adChannel = ADC_CH3;
    int psdValue = 0.0;
    if (wiringPiSetup() == -1)
        return -1;

    pinMode(ADC_CS, OUTPUT);

    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);

    if (wiringPiSPISetup(SPI_CH, SPI_SPEED) == -1)
    {
        printf("wiringPi SPI Setup failed!\n");
        exit(0);
    }
    while (1)
    {
        digitalWrite(LED_RED, 0);
        digitalWrite(LED_GREEN, 0);
        digitalWrite(LED_BLUE, 0);

        buf[0] = 0x06 | ((adChannel & 0x07) >> 2);
        buf[1] = ((adChannel & 0x07) << 6);
        buf[2] = 0x00;
        digitalWrite(ADC_CS, 0);
        wiringPiSPIDataRW(SPI_CH, buf, 3);
        buf[1] = 0x0F & buf[1];
        adcValue = (buf[1] << 8) | buf[2];
        digitalWrite(ADC_CS, 1);
        psdValue = 10000 / (adcValue * 434 * 5 / 1023 - 46);
        printf("PSD Value -> %d cm\n", psdValue);
        if (psdValue < 10)
            digitalWrite(LED_RED, 1);
        else if (psdValue >= 10 && 20 < psdValue)
            digitalWrite(LED_GREEN, 1);
        else
            digitalWrite(LED_BLUE, 1);
        usleep(100000);
    }
    return 0;
}