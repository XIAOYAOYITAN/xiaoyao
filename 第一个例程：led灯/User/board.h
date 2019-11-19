#ifndef __BOARD_H__
#define __BOARD_H__


/*STM32固件库头文件*/
#include "stm32f4xx.h"
/*开发版硬件bsp头文件*/

#include "./led/bsp_led.h"

/*函数声明*/
void rt_hw_board_init(void);
void SysTick_Handler(void);
	
	
#endif /*__BOARD_H__*/
