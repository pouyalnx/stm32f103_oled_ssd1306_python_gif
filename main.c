#include "cmsis_os2.h"
#include "stm32f10x.h" 
#include "rl_usb.h"


static uint8_t lcd_data[1040];
extern void LCD_UPDATE(unsigned char *bfr);

static void app(void *arg){
	osDelay(10);
	USBD_Initialize(0);
	USBD_Connect(0);
	while(USBD_Configured(0)==false) osDelay(100);
	osDelay(50);
	lcd_data[0]=0x40;
	LCD_UPDATE(lcd_data);
	while(1){
		while(USBD_CDC_ACM_DataAvailable(0)!=1024) osDelay(10);
		USBD_CDC_ACM_ReadData(0,&lcd_data[1],1024);
		if(GPIOB->ODR & GPIO_ODR_ODR12) GPIOB->BRR=GPIO_BRR_BR12;
	   else									  GPIOB->BSRR=GPIO_BSRR_BS12;
		///////////////////////////////////////////////////////////
		lcd_data[0]=0x40;
		LCD_UPDATE(lcd_data);
		///////////////////////////////////////////////////////////
		USBD_CDC_ACM_PutChar(0,'A');
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
extern int keyGetCharRelase(void);
static void led(void *arg){
	RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
	GPIOB->CRH&=~(GPIO_CRH_MODE12|GPIO_CRH_CNF12);
	GPIOB->CRH|=GPIO_CRH_MODE12_1;

	while(1){
		osDelay(10);

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
	osKernelInitialize();
	osThreadNew(led,NULL,NULL);
	osThreadNew(app,NULL,NULL);
	osKernelStart();
}
