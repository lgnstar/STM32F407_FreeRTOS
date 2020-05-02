#include "led.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * LED demo
 * @param pvParameters [para]
 */
void Led_task(void *pvParameters)
{
    LED_Init();
    while(1)
    {
        LED_Light(1);
        vTaskDelay(500);
        LED_Light(0);
        vTaskDelay(500);
       
    }
}
