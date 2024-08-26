/**
* @file		Jump2System.c
* @author	remov-b4-flight
* @note		code is lent from STMicro. application note
*/
#include "main.h"
//! Start address of DFU BOOTLOADER
#define SYSTEM_MEMORY	0x1FFFC800

/**
 * @brief jump into system memory (DFU BOOTLOADER)
 */
void Jump2SystemMemory() {
	void (*SysMemBootJump)(void);

	/*
	* Set system memory address.
	* For STM32F072, system memory is on 0x1FFFC800
	*/
	volatile uint32_t addr = SYSTEM_MEMORY;
	/**
	 * Stop all Interrupt source
	 */
	//TIM1
	TIM1->DIER = 0;
	TIM1->SR = 0;
	//TIM6
	TIM6->DIER = 0;
	TIM6->SR = 0;
	//TIM7
	TIM7->DIER = 0;
	TIM7->SR = 0;
	//EXTI
	EXTI->IMR = 0;
	EXTI->PR = 0;
	//DMA
	DMA1->IFCR = 0;
	//I2C2
	I2C2->ICR = 0;
	//USB
	USB->ISTR = 0;
	// Disable systick timer and reset it to default values
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;

	// Re-map system memory to address 0x0000 0000 in address space
	SYSCFG->CFGR1 = 0x01;

	// Set jump memory location for system memory
	// Use address with 4 bytes offset which specifies jump location where program starts
	SysMemBootJump = (void (*)(void)) (*((uint32_t *)(addr + 4)));

	// Set main stack pointer.
	uint32_t msp = *(uint32_t *)addr;
	__set_MSP(msp);

	/**
	 * Call our function to jump to set location
	 * This will start system memory execution
	 */
	SysMemBootJump();
}
