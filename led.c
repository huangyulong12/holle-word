#include "led.h"
#include "timer.h"

static uint8_t LED_Status[LED_NUMBER];

const uint16_t LedPins[LED_NUMBER] = 
{
  RGB_B_PIN,  RGB_R_PIN,  RGB_G_PIN
};

const GPIO_TypeDef *LedGPIO[LED_NUMBER] = 
{
  RGB_B_GPIO,  RGB_R_GPIO,  RGB_G_GPIO
};

static tsTimeType TimeLeds[LED_NUMBER];
static teLedTaskStatus LedTaskStatus[LED_NUMBER];

uint8_t Get_LEDStatus(teLedNums LedNums)
{
  return LED_Status[LedNums];
}

/**
* 函数功能: 开启指定编号led
  * 输入参数: LED编号
  * 返 回 值: 无
  * 说    明: 无
  */
void LedOn(teLedNums LedNums)
{
  if(LedNums < LED_NUMBER)    // 防止数组越界
  {
    HAL_GPIO_WritePin((GPIO_TypeDef *)LedGPIO[LedNums], LedPins[LedNums], GPIO_PIN_RESET);
    LED_Status[LedNums] = 1;
  }
}

/**
* 函数功能: 关闭指定编号led
  * 输入参数: LED编号
  * 返 回 值: 无
  * 说    明: 无
  */
void LedOff(teLedNums LedNums)
{
  if(LedNums < LED_NUMBER)    // 防止数组越界
  {
    HAL_GPIO_WritePin((GPIO_TypeDef *)LedGPIO[LedNums], LedPins[LedNums], GPIO_PIN_SET);
    LED_Status[LedNums] = 0;
  }
}

/**
* 函数功能: 关闭所有Led
  * 输入参数: LED编号，延时时间
  * 返 回 值: 无
  * 说    明: 无
  */
void LedInit(void)
{
  LED_GPIO_Init();
}

/**
* 函数功能: 设置Led为运行态
  * 输入参数: LED编号，延时时间
  * 返 回 值: 无
  * 说    明: 无
  */
void SetRun(teLedNums LedNums)
{
  if(LedNums < LED_NUMBER)    // 防止数组越界
  {
    LedTaskStatus[LedNums] = LED_RUN;
  }
}

/**
  * 函数功能: 放在while里面实时运行
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void LedTask(void)
{
    for(uint8_t i=0; i<LED_NUMBER; i++)
    {
      if(LedTaskStatus[i] == LED_RUN)   // 如果LED是运行状态打开LED设置为延时态
      {
        LedOn(i);
        SetTime(&TimeLeds[i], 300);
        LedTaskStatus[i] = LED_DELAY;
      }
      else if(LedTaskStatus[i] == LED_DELAY)
      {
        if(CompareTime(&TimeLeds[i]))  // 如果超时了停止LED，设置为停止态
        {
          LedOff(i);
          LedTaskStatus[i] = LED_STOP; 
        }
      }
      
    }

}

/*
*函数名称：LED_AllOff
*作用    ：LED全灭
*传递参数：NULL
*返回参数：NULL
*/
void Led_AllOff(void)
{
  for(uint8_t i=0; i<LED_NUMBER; i++)
    LedOff(i);
}

/*
*函数名称：LED_AllOn
*作用    ：LED全开
*传递参数：NULL
*返回参数：NULL
*/
void Led_AllOn(void)
{
  for(uint8_t i=0; i<LED_NUMBER; i++)
    LedOn(i);
}




/*
*函数名称：LED_GPIO_Init
*作用    ：LED和蜂鸣器引脚初始化
*传递参数：NULL
*返回参数：NULL
*/
void LED_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

	LED_GPIO_RCC();
	
	Led_AllOff();
	
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  
  for(uint8_t i=0; i<LED_NUMBER; i++)
  {
    GPIO_InitStruct.Pin = LedPins[i];
    HAL_GPIO_Init((GPIO_TypeDef *)LedGPIO[i], &GPIO_InitStruct);
  }
  

}








