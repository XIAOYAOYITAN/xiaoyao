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
static rt_thread_t receive_thread = RT_NULL;
static rt_thread_t send_thread = RT_NULL;



/**函数声明**/

static void receive_thread_entry(void *parameter);
static void send_thread_entry(void *parameter);

static rt_mq_t test_mq = RT_NULL;
/**main函数**/

int main()
{
	/*打印提示信息*/
	rt_kprintf("This is a test of message queue!\n\n");
	rt_kprintf("Press KEY1 or KEY2 to send the message.\n");
	rt_kprintf("receive线程接收消息在串口进行回显.\n");
	
/*
	***************************************************
	*							创建一个队列消息													
	****************************************************/
	test_mq= 
	rt_mq_create(	"test_mq",												/*消息队列名称*/
								  40,						  								/*消息的最大长度*/
									20,															/*消息队列的最大容量*/		
									RT_IPC_FLAG_FIFO)							;	/*队列模式*/
 if(test_mq != RT_NULL) 													/*检验是否创建成功*/
	rt_kprintf("消息队列创建成功！\n\n");
 
 /*创建接收线程*/
 	receive_thread= 
	rt_thread_create(	"receive",										/*线程名称*/
									receive_thread_entry,						/*线程入口函数*/
									RT_NULL,										  	/*入口函数参数*/
									512,														/*栈大小*/
									3,														  /*优先级*/
									20)													;	  /*时间片*/
 if(receive_thread != RT_NULL) 						        /*启动线程，开始调度*/
	 rt_thread_startup(receive_thread);
 else 
	 return -1;
 
 /*创建发送线程*/									
 	send_thread= 
	rt_thread_create(	"send",												/*线程名称*/
									send_thread_entry,							/*线程入口函数*/
									RT_NULL,										  	/*入口函数参数*/
									512,														/*栈大小*/
									2,														  /*优先级*/
									20)													;	  /*时间片*/
 if(send_thread != RT_NULL) 	   					        /*启动线程，开始调度*/
	 rt_thread_startup(send_thread);
 else 
	 return -1;
														
}

static void receive_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK; /*There is no error*/
	uint32_t r_queue;
	/*开始无限循环*/
	while(1)
	{
		
		/**/
		uwRet=rt_mq_recv(test_mq,             /*句柄*/
										 &r_queue,							/*接收数据保存位置*/
										 sizeof(r_queue),			/*接收数据长度*/
										 RT_WAITING_FOREVER); /*等待时间*/
		if(RT_EOK == uwRet){
			rt_kprintf("本次接收到的数据是：%d\n",r_queue);
		}
		else{
			rt_kprintf("数据接收出错，错误代码：0x%1x\n",uwRet);
		}
		rt_thread_delay(200); 
	}
}


static void send_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK;
	uint32_t send_data1 = 1;
	uint32_t send_data2 = 2;
	while(1)
	{
		/*KEY1 are pressed*/
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON){
			
			/*将数据写入发送队列中，等待时间为0*/
			uwRet = rt_mq_send(test_mq,             /*发送队列句柄*/
												 &send_data1,          /*发送的数据*/
												 sizeof(send_data1));  /*数据长度*/
			if(RT_EOK != uwRet){
				rt_kprintf("数据不能发送到消息队列！错误代码为：%1x\n",uwRet);
			}
		}
		
		/*KEY2 are pressed*/
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON){
			
			/*将数据写入发送队列中，等待时间为0*/
			uwRet = rt_mq_send(test_mq,             /*发送队列句柄*/
												 &send_data2,          /*发送的数据*/
												 sizeof(send_data2));  /*数据长度*/
			if(RT_EOK != uwRet){
				rt_kprintf("数据不能发送到消息队列！错误代码为：%1x\n",uwRet);
			}
		}
		rt_thread_delay(20);
	}
}



/*********************************************END OF FILE**********************/

