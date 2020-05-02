#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx.h"

//start task parameter
#define START_TASK_PRIO 1 //task prio
#define START_STK_SIZE  128 //task stack size
TaskHandle_t StartTask_Handler; 
extern void Start_task(void *pvParameters); //task func

void Stm32_Clock_Init(uint32_t plln,uint32_t pllm,uint32_t pllp,uint32_t pllq);

int main(void)
{    
    HAL_Init();                    	
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); 

    Stm32_Clock_Init(336,8,2,7);  	//setup cpu clock to 168Mhz    
      
	xTaskCreate((TaskFunction_t)Start_task,
                (const char*   )"Start_task",
                (uint16_t      )START_STK_SIZE,
                (void*         )NULL,
                (UBaseType_t   )START_TASK_PRIO,
                &StartTask_Handler);
    vTaskStartScheduler(); //切换至OS系统
    while(1){}
}

//cpu clock config
void Stm32_Clock_Init(uint32_t plln,uint32_t pllm,uint32_t pllp,uint32_t pllq)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure; 
    RCC_ClkInitTypeDef RCC_ClkInitStructure;
    
    __HAL_RCC_PWR_CLK_ENABLE(); 
    
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    
    RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    
    RCC_OscInitStructure.HSEState=RCC_HSE_ON; // if use active crystal choose RCC_HSE_BYPASS                     
    RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;
    RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;
    RCC_OscInitStructure.PLL.PLLM=pllm; 
    RCC_OscInitStructure.PLL.PLLN=plln; 
    RCC_OscInitStructure.PLL.PLLP=pllp; 
    RCC_OscInitStructure.PLL.PLLQ=pllq; 
    ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);
	
    if(ret!=HAL_OK) while(1);
    
    RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;
    RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV4; 
    RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV2; 
    ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_5);
		
    if(ret!=HAL_OK) while(1);

	if (HAL_GetREVID() == 0x1001)
	{
		__HAL_FLASH_PREFETCH_BUFFER_ENABLE();  
	}
    
    HAL_RCC_EnableCSS();
}
