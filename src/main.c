/******************************************************************************
File        : main.c
Author      : Daniel Tar
Version     : 1.0
Copyright   :
Description : mpu6050 library
Info        : 29-06-2018
******************************************************************************/

/******************************************************************************/
/*                               Includes									  */
/******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include "stm32f10x.h"


#include "periph.h"
#include "util.h"
#include "mpu6050.h"

/* Private typedef */
/* Private define  */
// #define DEBUG

/* Private macro */

/* Private variables */

/* Private function prototypes */

/* Private functions */

#ifdef DEBUG
	#include "stm32f10x_dbgmcu.h"

	void InitDBG(void){
		DBGMCU_Config(DBGMCU_TIM2_STOP, ENABLE); /* this will make TIM2 stop when core is halted during debug */
		DBGMCU_Config(DBGMCU_TIM3_STOP, ENABLE);
		DBGMCU_Config(DBGMCU_STOP, ENABLE);
	}
#endif


/**
**===========================================================================
**  Abstract: main program
**===========================================================================
*/

/**
 * Hinweise:
 * Bei den Timern 1, 8, 15, 16 und 17 muessen die PWM Ausgaenge zusaetzlich mit der Funktion TIM_CtrlPWMOutputs(...) aktiviert werden.
 * Nur, falls der Timer aktiviert, aber die PWM-Outputs deaktiviert sind kommen die Einstellungen zum Idle State zum Tragen.
 * Die OCN Ausgaenge gibt es allgemein nur bei den Timern 1, 8, 15, 16 und 17.
 */

int main(void){

	SystemInit();


#ifdef DEBUG
	InitDBG();
#endif

	/* configure SysTick for delay functions */
	InitSysTick();


	/**************************************************/
	/* INIT STUCTURES                                 */
	/**************************************************/
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure; /* external interrupt init */
	NVIC_InitTypeDef NVIC_InitStructure; /* nested vector interrupt controller init */

	/**************************************************/
	/* GPIO INIT */
	/**************************************************/
	/* built-in led init */
	InitGPIO_LED(&GPIO_InitStructure);
	/*switch off the led by default*/
	GPIO_WriteBit(GPIOC,led_pin,Bit_SET);

	/* button init */
	InitGPIO_BTN(&GPIO_InitStructure);

	/**************************************************/
	/* TIMER INIT */
	/**************************************************/

	/**************************************************/
	/* INTERRUPT INIT */
	/* the interrupt handlers found in stm32f1xx_it.c */
	/**************************************************/
	/* button interrupt init */
	InitEXTI_BTN(&EXTI_InitStructure, &NVIC_InitStructure);

	while(1){

	}
}



