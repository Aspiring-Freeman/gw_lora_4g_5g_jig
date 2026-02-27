#include "main.h"
#include "GPIO.h"
#include "uart5.h"
#include "uart1.h"
#include "uart0.h"
#include "time.h"
#include "ADC_CHK.h"
#include "LED_CTRL.h"
#include "Test_List.h"
#include "WTD.h"
// 版本：VER2.0
uint8_t Debug_Mode = 0;
uint16_t Debug_print_time = 10000;
void test_Init()
{
	Others_GPIO_Init();
	UART5_MF_Config_Init();
	UART1_MF_Config_Init();
	UART0_MF_Config_Init();
	ATIM_Init();
	MF_ADC_PC10_Config_Init();
	// ��λ���
	gongwei_jiance();
	// ���ذ����ó�ʼ��
	test_start_Init();
	// ���Ź�
	WatchDog_Init();
}

int main(void)
{
	/* Initialize FL Driver Library */
	/* SHOULD BE KEPT!!! */
	FL_Init();

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	/* SHOULD BE KEPT!!! */
	MF_Clock_Init();

	/* Initialize all configured peripherals */
	/* SHOULD BE KEPT!!! */
	test_Init();
	// SPI_RW_Demo();

	// 启动标识 - 确认工装测试程序已运行
	DeBug_print("\r\n==========================================\r\n");
	DeBug_print("5G Gateway Tester V1.0 Started!\r\n");
	DeBug_print("Current Station: %d\r\n", Test_jiejuo_jilu.gongwei);
	DeBug_print("Debug_Mode: %d\r\n", Debug_Mode);
	DeBug_print("==========================================\r\n\r\n");

	while (1)
	{
		if (Debug_print_time == 0) //
		{
			Debug_print_time = 10000;
			DeBug_print("[Debug] Still alive, station=%d\r\n", Test_jiejuo_jilu.gongwei);
		}
		Uart5_Rx_rec();
		Uart1_Rx_rec();
		Uart0_Rx_rec();
		LED_FLAG_LOOP();
		test_Loop_Func();
		FL_IWDT_ReloadCounter(IWDT);
	}
}
