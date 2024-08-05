#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

void delay(uint32_t time) {
    for(int i = 0; i < time ; i++);
} // Moi i chay duoc ~1us


void RCC_config(void){
	//Ham cap xung clock cho GPIOC va GPIOA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
}

void GPIO_config(void){
	//Cau hinh chan PC13
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; // Neu muon them nhieu chan thi su dung phep OR
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStruct );
	
}
void nhayduoiLED( uint16_t loop ){
	uint16_t valLed;
	for(int i = 0; i < loop; i++) {
		valLed = 0x0010;
		for(int j = 0; j < 5; j++) {
			valLed = valLed << 1;
			GPIO_Write(GPIOC, valLed);
			delay(7000000);
		}
	}
}


int main(){
	RCC_config();
	GPIO_config();
	while(1) {
		nhayduoiLED(5);
		break;
	}	
}
