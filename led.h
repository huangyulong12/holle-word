#ifndef __LED__H
#define  __LED__H

/*包含的头文件*/
#include <stdint.h>
#include "stm32l1xx.h"

#define LED_GPIO_RCC()  __HAL_RCC_GPIOC_CLK_ENABLE()

#define RGB_B_GPIO      GPIOC
#define RGB_B_PIN       GPIO_PIN_6

#define RGB_R_GPIO      GPIOC
#define RGB_R_PIN       GPIO_PIN_7

#define RGB_G_GPIO      GPIOC
#define RGB_G_PIN       GPIO_PIN_8

#define LED_NUMBER      3

typedef enum
{
  LED_B = 0,
  LED_R,
  LED_G,
}teLedNums;   // 根据作用枚举LED编号

typedef enum
{
  LED_STOP = 0,
  LED_RUN,
  LED_DELAY
}teLedTaskStatus;   // led状态
  
void    LedInit(void);
void    SetRun(teLedNums LedNums);
void    LedTask(void);
void    LedOn(teLedNums LedNums);
void    LedOff(teLedNums LedNums);
void    Led_AllOff(void);
void    Led_AllOn(void);
uint8_t Get_LEDStatus(teLedNums LedNums);

void    LED_GPIO_Init(void);

#endif

