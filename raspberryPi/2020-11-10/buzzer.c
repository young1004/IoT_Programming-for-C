#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>

#define BUZZER 15

int main(void)
{
    if (wiringPiSetup() == -1)
        return 1;
    pinMode(BUZZER, OUTPUT);
    printf("Buzzer Control Start !! \n");
    while (1)
    {
        printf("BUZZER ON !!!\n");
        digitalWrite(BUZZER, 1);
        sleep(1); // 1초시간 지연
        printf("BUZZER OFF !!!\n");
        digitalWrite(BUZZER, 0);
        sleep(1); // 1초 시간 지연
    }
    return 0;
}
