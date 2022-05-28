#include "main.h"
float ADC_ConvertedValueLocal;  
int main()
{
	LED_GPIO_Config();
	BEEP_GPIO_Config();
	EXTI_Key_Config();
	USART_Config();
	ADCx_Init();
	SysTick_Init();
	ILI9341_Init();
	LcdDisplayName();
	while(1)
	{
		LcdDisplayMessage_D();
		Control(ADC_ConvertedValueLocal);
	}

}

void SetLedMin(float m)
{
	LED_MIN = m;
}

void SetLedMax(float m)
{
	LED_MAX = m;
}


void Control(float ADC_ConvertedValueLocal)
{
	if(ADC_ConvertedValueLocal < LED_MIN)
	{
		LED_WHITE;
		ledstate = LED_ON;
		LcdDisplayMessage_S();
	}
	else if(ADC_ConvertedValueLocal > LED_MAX)
	{
		BEEP(BEEP_ON);
		beepstate = BEEP_ON;
		LcdDisplayMessage_S();
	}
	else
	{
		ledstate = LED_OFF;
		beepstate = BEEP_OFF;
		LED_RGBOFF;
		BEEP(BEEP_OFF);
		LcdDisplayMessage_S();
	}
}

void LcdDisplayMessage_D(void)
{
	char dispBuff[100];
	Delay_ms(2000);
	ILI9341_GramScan(6);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
	sprintf(dispBuff,"tmp:%.2f ^C",ADC_ConvertedValueLocal);
  LCD_ClearLine(LINE(9));
	ILI9341_DispStringLine_EN(LINE(9),dispBuff);
	sprintf(dispBuff,"sun:%.2f lux",ADC_ConvertedValueLocal);
	LCD_ClearLine(LINE(10));
	ILI9341_DispStringLine_EN(LINE(10),dispBuff);
	
}

void LcdDisplayMessage_S(void)
{
	ILI9341_GramScan(6);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	LCD_ClearLine(LINE(7));
	LCD_ClearLine(LINE(8));
	if( ledstate == LED_OFF )ILI9341_DispStringLine_EN(LINE(7),"LED_OFF");
	else ILI9341_DispStringLine_EN(LINE(7),"LED_ON");
	if( beepstate == BEEP_OFF )ILI9341_DispStringLine_EN(LINE(8),"BEEP_OFF");
	else ILI9341_DispStringLine_EN(LINE(8),"BEEP_ON");
}

void LcdDisplayName(void)
{
	int i = 11;
	ILI9341_GramScan(6);
	LCD_SetFont(&Font16x24);
	LCD_SetColors(BLACK,WHITE);
	do{
		ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
		ILI9341_DispStringLine_EN(LINE(i),"ICCS");
		ILI9341_DispStringLine_EN(LINE(i+1),"3018");
		Delay_ms(100);
		}while(i--);
	ILI9341_Clear(0,49,LCD_X_LENGTH,LCD_Y_LENGTH);
	ILI9341_DispStringLine_EN(LINE(2),"yanxiang");
	ILI9341_DispStringLine_EN(LINE(3),"chengwenya");
	LcdDisplayMessage_S();
}
/*
void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
} */
