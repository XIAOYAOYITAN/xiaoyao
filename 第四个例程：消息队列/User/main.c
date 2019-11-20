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
static rt_thread_t receive_thread = RT_NULL;
static rt_thread_t send_thread = RT_NULL;



/**��������**/

static void receive_thread_entry(void *parameter);
static void send_thread_entry(void *parameter);

static rt_mq_t test_mq = RT_NULL;
/**main����**/

int main()
{
	/*��ӡ��ʾ��Ϣ*/
	rt_kprintf("This is a test of message queue!\n\n");
	rt_kprintf("Press KEY1 or KEY2 to send the message.\n");
	rt_kprintf("receive�߳̽�����Ϣ�ڴ��ڽ��л���.\n");
	
/*
	***************************************************
	*							����һ��������Ϣ													
	****************************************************/
	test_mq= 
	rt_mq_create(	"test_mq",												/*��Ϣ��������*/
								  40,						  								/*��Ϣ����󳤶�*/
									20,															/*��Ϣ���е��������*/		
									RT_IPC_FLAG_FIFO)							;	/*����ģʽ*/
 if(test_mq != RT_NULL) 													/*�����Ƿ񴴽��ɹ�*/
	rt_kprintf("��Ϣ���д����ɹ���\n\n");
 
 /*���������߳�*/
 	receive_thread= 
	rt_thread_create(	"receive",										/*�߳�����*/
									receive_thread_entry,						/*�߳���ں���*/
									RT_NULL,										  	/*��ں�������*/
									512,														/*ջ��С*/
									3,														  /*���ȼ�*/
									20)													;	  /*ʱ��Ƭ*/
 if(receive_thread != RT_NULL) 						        /*�����̣߳���ʼ����*/
	 rt_thread_startup(receive_thread);
 else 
	 return -1;
 
 /*���������߳�*/									
 	send_thread= 
	rt_thread_create(	"send",												/*�߳�����*/
									send_thread_entry,							/*�߳���ں���*/
									RT_NULL,										  	/*��ں�������*/
									512,														/*ջ��С*/
									2,														  /*���ȼ�*/
									20)													;	  /*ʱ��Ƭ*/
 if(send_thread != RT_NULL) 	   					        /*�����̣߳���ʼ����*/
	 rt_thread_startup(send_thread);
 else 
	 return -1;
														
}

static void receive_thread_entry(void *parameter)
{
	rt_err_t uwRet = RT_EOK; /*There is no error*/
	uint32_t r_queue;
	/*��ʼ����ѭ��*/
	while(1)
	{
		
		/**/
		uwRet=rt_mq_recv(test_mq,             /*���*/
										 &r_queue,							/*�������ݱ���λ��*/
										 sizeof(r_queue),			/*�������ݳ���*/
										 RT_WAITING_FOREVER); /*�ȴ�ʱ��*/
		if(RT_EOK == uwRet){
			rt_kprintf("���ν��յ��������ǣ�%d\n",r_queue);
		}
		else{
			rt_kprintf("���ݽ��ճ���������룺0x%1x\n",uwRet);
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
			
			/*������д�뷢�Ͷ����У��ȴ�ʱ��Ϊ0*/
			uwRet = rt_mq_send(test_mq,             /*���Ͷ��о��*/
												 &send_data1,          /*���͵�����*/
												 sizeof(send_data1));  /*���ݳ���*/
			if(RT_EOK != uwRet){
				rt_kprintf("���ݲ��ܷ��͵���Ϣ���У��������Ϊ��%1x\n",uwRet);
			}
		}
		
		/*KEY2 are pressed*/
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN) == KEY_ON){
			
			/*������д�뷢�Ͷ����У��ȴ�ʱ��Ϊ0*/
			uwRet = rt_mq_send(test_mq,             /*���Ͷ��о��*/
												 &send_data2,          /*���͵�����*/
												 sizeof(send_data2));  /*���ݳ���*/
			if(RT_EOK != uwRet){
				rt_kprintf("���ݲ��ܷ��͵���Ϣ���У��������Ϊ��%1x\n",uwRet);
			}
		}
		rt_thread_delay(20);
	}
}



/*********************************************END OF FILE**********************/

