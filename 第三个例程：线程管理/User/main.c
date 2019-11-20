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
#include <./key/bsp_key.h>


/**变量定义**/

/*定义线程控制块*/
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t key_thread = RT_NULL;



/**函数声明**/

static void led1_thread_entry(void *parameter);
static void key_thread_entry(void *parameter);

/**main函数**/

int main()
{
	rt_kprintf("This is a test of threads management!\n\n");
	rt_kprintf("press KEY1 to suspend the thread, and KEY2 to resume.\n");
	
/*
	***************************************************
	*							线程定义													
	****************************************************/
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
 
 	key_thread= 
	rt_thread_create(	"key",												/*线程名称*/
									key_thread_entry,						/*线程入口函数*/
									RT_NULL,											/*入口函数参数*/
									512,														/*栈大小*/
									2,														/*优先级*/
									20)													;	/*时间片*/
 if(key_thread != RT_NULL) 						/*启动线程，开始调度*/
	 rt_thread_startup(key_thread);
 else 
	 return -1;
									
							
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

static void key_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK;
	while(1)
	{
		/*KEY1 are pressed*/
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON){
			rt_kprintf("挂起LED1线程！\n");
			uwRet = rt_thread_suspend(led1_thread);/*挂起LED1线程*/
			if(RT_EOK == uwRet){
				rt_kprintf("挂起LED1线程成功！\n");
			}else{
				rt_kprintf("挂起LED1线程失败！失败代码0x%1x\n",uwRet);
			}
		}
		
		/*KEY2 are pressed*/
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON){
			rt_kprintf("恢复LED1线程！\n");
			uwRet = rt_thread_resume(led1_thread);/*恢复LED1线程*/
			if(RT_EOK == uwRet){
				rt_kprintf("恢复LED1线程成功！\n");
			}else{
				rt_kprintf("恢复LED1线程失败！失败代码0x%1x\n",uwRet);
			}
		}
		rt_thread_delay(20);
	}
}



/*********************************************END OF FILE**********************/

