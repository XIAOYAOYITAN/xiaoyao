/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-11-22
  * @brief   RT-Thread+ STM32工程
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板 
  *
  ******************************************************************************
  */
#include "board.h"
#include "rtthread.h"
#include <./usart/bsp_debug_usart.h>

/**变量定义**/

/*定义线程控制块*/
static rt_thread_t led1_thread = RT_NULL;

///*定义线程时要求RT_ALIGN_SIZE个字节对齐*/
//ALIGN(RT_ALIGN_SIZE)
///*定义线程栈*/
//static rt_uint8_t rt_led1_thread_stack[1024];


/**函数声明**/

static void led1_thread_entry(void *parameter);

/**main函数**/

int main()
{
	led1_thread= 
	rt_thread_create(	"led1",												/*线程名称*/
									led1_thread_entry,						/*线程入口函数*/
									RT_NULL,											/*入口函数参数*/
									512,														/*栈大小*/
									3,														/*优先级*/
									20)													;	/*时间片*/
 if(led1_thread != RT_NULL) 						/*启动线程，开始调度*/
	 rt_thread_startup(led1_thread);
 else 
	 return -1;
									
	/*
	***************************************************
	*							线程定义													
	****************************************************/							
}

static void led1_thread_entry(void *parameter)
{
	while(1)
	{
		LED1_ON;
		rt_thread_delay(500);/*延时500个tick*/
		rt_kprintf("led1_thread running,LED1_ON \r\n");
		
		LED1_OFF;
		rt_thread_delay(500);/*延时500个tick*/
		rt_kprintf("led1_thread running,LED1_OFF \r\n");
	}
}

/*********************************************END OF FILE**********************/

