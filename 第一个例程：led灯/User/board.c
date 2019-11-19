/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 */
 
 /*开发板硬件相关头文件*/
#include <board.h>
/*RT-Thread头文件*/
#include <rthw.h>
#include <rtthread.h>

#if 0
/*========================================================================*/
#define _SCB_BASE       (0xE000E010UL)
#define _SYSTICK_CTRL   (*(rt_uint32_t *)(_SCB_BASE + 0x0))
#define _SYSTICK_LOAD   (*(rt_uint32_t *)(_SCB_BASE + 0x4))
#define _SYSTICK_VAL    (*(rt_uint32_t *)(_SCB_BASE + 0x8))
#define _SYSTICK_CALIB  (*(rt_uint32_t *)(_SCB_BASE + 0xC))
#define _SYSTICK_PRI    (*(rt_uint8_t  *)(0xE000ED23UL))

// Updates the variable SystemCoreClock and must be called 
// whenever the core clock is changed during program execution.
extern void SystemCoreClockUpdate(void);

// Holds the system core clock, which is the system clock 
// frequency supplied to the SysTick timer and the processor 
// core clock.
extern uint32_t SystemCoreClock;

static uint32_t _SysTick_Config(rt_uint32_t ticks)
{
    if ((ticks - 1) > 0xFFFFFF)
    {
        return 1;
    }
    
    _SYSTICK_LOAD = ticks - 1; 
    _SYSTICK_PRI = 0xFF;
    _SYSTICK_VAL  = 0;
    _SYSTICK_CTRL = 0x07;  
    
    return 0;
}
/*============================================================*/
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
#define RT_HEAP_SIZE 1024
static uint32_t rt_heap[RT_HEAP_SIZE];	// heap default size: 4K(1024 * 4)
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return rt_heap + RT_HEAP_SIZE;
}
#endif

/**
 * This function will initial your board.
 */
void rt_hw_board_init()
{	
	#if 0
	/* System Clock Update */
	SystemCoreClockUpdate();
	
	/* System Tick Configuration */
	_SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
	
  #endif
	
	/*初始化SystemTick,这里使用的是core m4 的时钟配置*/
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
	
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
	
	/*初始化开发板的LED*/
	LED_GPIO_Config();
	
	/*测试硬件是否正常工作*/
	LED1_ON;
	
	/*其他硬件测试*/
	
	/*程序停止*/
//	while (1);
	
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
    
#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    
#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
}

void SysTick_Handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

//#if defined(RT_USING_USER_MAIN) && defined (RT_USING_HEAP)
///*从内部SRAM（DTCM）中分配一部分静态内存来作为RT-Thread的堆空间，这里配置为4KB*/
//#define RT_HEAP_SIZE 1024
//static uint32_t rt_heap[RT_HEAP_SIZE];
//RT_WEAK void *rt_heap_begin_get(void)
//{
//	return rt_heap;
//}
//RT_WEAK void *rt_heap_end_get(void)
//{
//	return rt_heap + RT_HEAP_SIZE;
//}

//#endif

//#if defined(RT_USING_USER_MAIN) && defined (RT_USING_HEAP)
//rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
//#endif
