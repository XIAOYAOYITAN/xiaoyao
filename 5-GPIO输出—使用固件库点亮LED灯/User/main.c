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

/**��������**/

/*�����߳̿��ƿ�*/
static struct rt_thread led1_thread;

/*�����߳�ʱҪ��RT_ALIGN_SIZE���ֽڶ���*/
ALIGN(RT_ALIGN_SIZE)
/*�����߳�ջ*/
static rt_uint8_t rt_led1_thread_stack[1024];


/**��������**/

static void led1_thread_entry(void *parameter);

/**main����**/

int main()
{
	rt_thread_init(&led1_thread, 									/*�߳̿��ƿ�*/
									"led1",												/*�߳�����*/
									led1_thread_entry,						/*�߳���ں���*/
									RT_NULL,											/*��ں�������*/
									&rt_led1_thread_stack[0],			/*��ʼ��ַ*/
									sizeof(rt_led1_thread_stack),	/*ջ��С*/
									3,														/*���ȼ�*/
									20)													;	/*ʱ��Ƭ*/
  rt_thread_startup(&led1_thread);  /*�����̣߳���ʼ����*/
									
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
		
		LED1_OFF;
		rt_thread_delay(500);/*��ʱ500��tick*/
	}
}


/*********************************************END OF FILE**********************/

