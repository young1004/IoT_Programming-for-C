#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>

#define LED_RED 7
#define LED_GREEN 21
#define LED_BLUE 22
#define BUZZER 15


#define PIR_D 2    // 인체 감지 센서를 2번에 연결
char pir_flag = 0; // 센서감지를 나타내는 flag
// 인터럽트 함수
void PIR_interrupt()
{
    pir_flag = 1;
}
int main(void)
{
    if (wiringPiSetup() == -1)
        return -1;
    // 인터러트 사용핀을 입력설정,
    //인터럽트 설정 소스: PIR_D핀, 상승에지, 함수명
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(PIR_D, INPUT);
    pinMode(BUZZER, OUTPUT);

    wiringPiISR(PIR_D, INT_EDGE_RISING, &PIR_interrupt);
    while (1)
    {
        if (pir_flag == 1)
        {
            digitalWrite(LED_RED, 0);
            digitalWrite(LED_GREEN, 1);
            digitalWrite(BUZZER, 1);
            printf("PIR Detected !! \n");
            pir_flag = 0;
        }
        else
        {
            digitalWrite(LED_RED, 1);
            digitalWrite(LED_GREEN, 0);
            digitalWrite(BUZZER, 0);
            printf("PIR Not detect !! \n");
        }
        usleep(100000); // 1초
    }
    return 0;
}