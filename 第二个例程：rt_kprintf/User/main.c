/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2019-11-22
  * @brief   RT-Thread+ STM32����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  *
  ******************************************************************************
  */
#include "board.h"
#include "rtthread.h"
#include <./usart/bsp_debug_usart.h>

/**��������**/

/*�����߳̿��ƿ�*/
static rt_thread_t led1_thread = RT_NULL;

///*�����߳�ʱҪ��RT_ALIGN_SIZE���ֽڶ���*/
//ALIGN(RT_ALIGN_SIZE)
///*�����߳�ջ*/
//static rt_uint8_t rt_led1_thread_stack[1024];


/**��������**/

static void led1_thread_entry(void *parameter);

/**main����**/

int main()
{
	led1_thread= 
	rt_thread_create(	"led1",												/*�߳�����*/
									led1_thread_entry,						/*�߳���ں���*/
									RT_NULL,											/*��ں�������*/
									512,														/*ջ��С*/
									3,														/*���ȼ�*/
									20)													;	/*ʱ��Ƭ*/
 if(led1_thread != RT_NULL) 						/*�����̣߳���ʼ����*/
	 rt_thread_startup(led1_thread);
 else 
	 return -1;
									
	/*
	***************************************************
	*							�̶߳���													
	****************************************************/							
}

static void led1_thread_entry(void *parameter)
{
	while(1)
	{
		LED1_ON;
		rt_thread_delay(500);/*��ʱ500��tick*/
		rt_kprintf("led1_thread running,LED1_ON \r\n");
		
		LED1_OFF;
		rt_thread_delay(500);/*��ʱ500��tick*/
		rt_kprintf("led1_thread running,LED1_OFF \r\n");
	}
}

/*********************************************END OF FILE**********************/

