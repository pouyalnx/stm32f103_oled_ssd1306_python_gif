#include "stm32f10x.h"
#include "cmsis_os2.h"

extern int keyRead(void);
extern int keyGetChar(void);
extern int keyGetCharRelase(void);
extern void keyInit(void);


//int stdin_getchar(void){return keyGetChar();}
int stdin_getchar(void){return keyGetCharRelase();}

#define U_read (GPIOA->IDR & GPIO_IDR_IDR5)==0
#define C_read (GPIOA->IDR & GPIO_IDR_IDR4)==0
#define L_read (GPIOA->IDR & GPIO_IDR_IDR3)==0
#define D_read (GPIOA->IDR & GPIO_IDR_IDR2)==0
#define R_read (GPIOA->IDR & GPIO_IDR_IDR1)==0
static int isInit=0;


int keyRead(void){
	if(isInit==0) keyInit();
	if(U_read) return 'U';
	if(C_read) return 'C';
	if(L_read) return 'L';
	if(D_read) return 'D';
	if(R_read) return 'R';
	return 0;
}

int keyGetChar(void){
	if(isInit==0) keyInit();
	while(1){
		if(U_read) return 'U';
		if(C_read) return 'C';
		if(L_read) return 'L';
		if(D_read) return 'D';
		if(R_read) return 'R';
		osDelay(2);
	}
}



int keyGetCharRelase(void){
	if(isInit==0) keyInit();
	while(1){
		if(U_read){
			osDelay(10);
			if(U_read){
				while(U_read) osDelay(2);
				return 'W';
			}
		}
		if(C_read){
			osDelay(10);
			if(C_read){
				while(C_read) osDelay(2);
				return 'C';
			}
		}
		if(L_read){
			osDelay(10);
			if(L_read){
				while(L_read) osDelay(2);
				return 'A';
			}
		}
		if(D_read){
			osDelay(10);
			if(D_read){
				while(D_read) osDelay(2);
				return 'S';
			}
		}
		if(R_read){
			osDelay(10);
			if(R_read){
				while(R_read) osDelay(2);
				return 'D';
			}
		}
		osDelay(2);
	}
}





void keyInit(void){
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;

	GPIOA->CRL&=~(GPIO_CRL_MODE0|GPIO_CRL_CNF0);
	GPIOA->CRL|=GPIO_CRL_MODE0_1;
	GPIOA->BRR=GPIO_BRR_BR0;

	GPIOA->CRL&=~(GPIO_CRL_MODE6|GPIO_CRL_CNF6);
	GPIOA->CRL|=GPIO_CRL_MODE6_1;
	GPIOA->BSRR=GPIO_BSRR_BS6;
	
	GPIOA->CRL&=~GPIO_CRL_MODE1;
	GPIOA->CRL&=~GPIO_CRL_CNF1;
	GPIOA->CRL|=GPIO_CRL_CNF1_1;
	
	GPIOA->CRL&=~GPIO_CRL_MODE2;
	GPIOA->CRL&=~GPIO_CRL_CNF2;
	GPIOA->CRL|=GPIO_CRL_CNF2_1;
	
	GPIOA->CRL&=~GPIO_CRL_MODE3;
	GPIOA->CRL&=~GPIO_CRL_CNF3;
	GPIOA->CRL|=GPIO_CRL_CNF3_1;
	
	GPIOA->CRL&=~GPIO_CRL_MODE4;
	GPIOA->CRL&=~GPIO_CRL_CNF4;
	GPIOA->CRL|=GPIO_CRL_CNF4_1;		

	GPIOA->CRL&=~GPIO_CRL_MODE5;
	GPIOA->CRL&=~GPIO_CRL_CNF5;
	GPIOA->CRL|=GPIO_CRL_CNF5_1;
	isInit=1;
}






