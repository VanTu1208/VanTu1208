#include "stm32f10x.h"                  // Device header

void RCC_config(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
}

void GPIO_config(){
	//Cau hinh PC13
	GPIOC->CRH |= GPIO_CRH_MODE13;
	GPIOC->CRH &= ~GPIO_CRH_CNF13;
	
	//Cau hinh PCA1
	GPIOA->CRL &= ~GPIO_CRL_MODE1;
	GPIOA->CRL |= GPIO_CRL_CNF1_1;
	GPIOA->CRL &= ~GPIO_CRL_CNF1_0;
	GPIOA->ODR |= GPIO_ODR_ODR1; //pull up
}

void toggle_LED(uint16_t pin){
	if(GPIOC->ODR & (1<<pin))
		GPIOC->ODR &= ~(1<<pin);
	else GPIOC->ODR |= 1<<pin;
}

int main() {
	RCC_config();
	GPIO_config();
	while(1){
		if( (GPIOA->IDR & (1<<1)) == 0) { //Khi nhan nut thi idr = 0, nen phep or = 0 , or voi mat na co gia tri bang 1 tai PCA1
			while((GPIOA->IDR & (1<<1)) == 0){}; //cho den khi nao tha nut ra
			toggle_LED(13);
		}
	}
}
