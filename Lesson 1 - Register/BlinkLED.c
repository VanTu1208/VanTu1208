#include "stm32f10x.h"                  // Device header

void delay(uint32_t time) {
	for(int i = 0; i < time ; i++);
} // Moi i chay duoc ~1us

void RCC_config(){
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; //Cap xung clock cho portC --- RCC_APB2ENR_IOPCEN: enable portC duoc cung cap boi thu vien stm32f10x.h
	//RCC lien quan den cap xung, APB2ENR: thanh ghi APB2ENR dieu khien bus APB2 lien ket voi GPIO, IOPCEN: bit trong thanh ghi
}

void GPIO_config(){
	//Cau hinh chan
	GPIOC->CRH |= GPIO_CRH_MODE13_1; //Set bit trong so cao mode13 len 1
	GPIOC->CRH |= GPIO_CRH_MODE13_0; //Set bit trong so thap mode13 len 1 che do output  50MHz
	GPIOC->CRH &= ~GPIO_CRH_CNF13; //Set 2 bit CNF13 xuong 0, che do output push-pull
}

int main(){
	RCC_config();
	GPIO_config();
	while(1){
		GPIOC->ODR |= 1<<13; //Ghi bit 1 vao PC13
		delay(5000000);
		GPIOC->ODR &= ~(1<<13); //Ghi bit 0 vao PC13
		delay(5000000);
	}
}
