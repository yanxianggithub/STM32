#include "stm32f10x.h"
#include "bsp_led.h" 
#include "bsp_usart.h" 
#include "bsp_beep.h" 
#include "bsp_exti.h" 
#include "bsp_adc.h" 
#include "bsp_SysTick.h" 
#include "bsp_ili9341_lcd.h"
#include "stm32f10x_it.h"

extern float LED_MIN;
extern float LED_MAX;
extern uint8_t ledstate,beepstate;
extern __IO uint16_t ADC_ConvertedValue;

void LcdDisplayName(void);
void LcdDisplayMessage_S(void);
void LcdDisplayMessage_D(void);
void Delay(__IO u32 nCount);
void Control(float ADC_ConvertedValueLocal);
void SetLedMin(float m);
void SetLedMax(float m);
