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
#include <./key/bsp_key.h>


/**��������**/

/*�����߳̿��ƿ�*/
static rt_thread_t led1_thread = RT_NULL;
static rt_thread_t key_thread = RT_NULL;



/**��������**/

static void led1_thread_entry(void *parameter);
static void key_thread_entry(void *parameter);

/**main����**/

int main()
{
	rt_kprintf("This is a test of threads management!\n\n");
	rt_kprintf("press KEY1 to suspend the thread, and KEY2 to resume.\n");
	
/*
	***************************************************
	*							�̶߳���													
	****************************************************/
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
 
 	key_thread= 
	rt_thread_create(	"key",												/*�߳�����*/
									key_thread_entry,						/*�߳���ں���*/
									RT_NULL,											/*��ں�������*/
									512,														/*ջ��С*/
									2,														/*���ȼ�*/
									20)													;	/*ʱ��Ƭ*/
 if(key_thread != RT_NULL) 						/*�����̣߳���ʼ����*/
	 rt_thread_startup(key_thread);
 else 
	 return -1;
									
							
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

static void key_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK;
	while(1)
	{
		/*KEY1 are pressed*/
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON){
			rt_kprintf("����LED1�̣߳�\n");
			uwRet = rt_thread_suspend(led1_thread);/*����LED1�߳�*/
			if(RT_EOK == uwRet){
				rt_kprintf("����LED1�̳߳ɹ���\n");
			}else{
				rt_kprintf("����LED1�߳�ʧ�ܣ�ʧ�ܴ���0x%1x\n",uwRet);
			}
		}
		
		/*KEY2 are pressed*/
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON){
			rt_kprintf("�ָ�LED1�̣߳�\n");
			uwRet = rt_thread_resume(led1_thread);/*�ָ�LED1�߳�*/
			if(RT_EOK == uwRet){
				rt_kprintf("�ָ�LED1�̳߳ɹ���\n");
			}else{
				rt_kprintf("�ָ�LED1�߳�ʧ�ܣ�ʧ�ܴ���0x%1x\n",uwRet);
			}
		}
		rt_thread_delay(20);
	}
}



/*********************************************END OF FILE**********************/

