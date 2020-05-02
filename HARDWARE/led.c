#include "stm32f4xx.h"
   
/**
 *  LED IO Init
 */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOF_CLK_ENABLE();           
    
    GPIO_Initure.Pin=GPIO_PIN_9; //PF9
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull=GPIO_PULLUP;          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
}

/**
 * LED ON OFF
 * @param   led     1=ON 0=OFF       
 */
void LED_Light(uint16_t led)
{
    if(led){
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET);
    }
}
