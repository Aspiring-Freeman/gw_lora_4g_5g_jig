#include "Test_List.h"
#include "GPIO.h"
#include "ZDINA219.h"
#include "ADC_CHK.h"
#include "uart1.h"
#include "tongxin_xieyi_Ctrl.h"

struct Test_quanju_canshu Test_quanju_canshu_L;
enum Test_liucheng Test_liucheng_L = w_wait;
struct Test_jieguo Test_jiejuo_jilu;
enum test_xieyi_jilu test_xieyi_jilu_Rec = No_Receive;

void test_quanju_canshu_Init()
{
	Test_quanju_canshu_L.time_softdelay_ms = 10;
}
//测试参数初始化
void test_start_Init()
{
		//备电电源打开
		beidian_gongdian_On();
		//主电源供电打开
		zhudian_gongdian_On();
		//主控板串口使能关闭
		Uart_shineng_OFF();
		//按键一抬起
    ANJIAN_1_OFF();
		//按键二抬起
    ANJIAN_2_OFF();
		//按键三抬起
    ANJIAN_3_OFF();
		//按键四抬起
    ANJIAN_4_OFF();
		//119不触发
		dianlu_119_OFF();
}
//工位检测
void gongwei_jiance()
{
	if(FL_GPIO_GetInputPin(GPIOE,FL_GPIO_PIN_0)==0)
	{
		Test_jiejuo_jilu.gongwei = 0x03;
	}
	else if(FL_GPIO_GetInputPin(GPIOE,FL_GPIO_PIN_1)==0)
	{
		Test_jiejuo_jilu.gongwei = 0x02;
	}
	else if(FL_GPIO_GetInputPin(GPIOE,FL_GPIO_PIN_2)==0)
	{
		Test_jiejuo_jilu.gongwei = 0x01;
	}
	else if(FL_GPIO_GetInputPin(GPIOE,FL_GPIO_PIN_3)==0)
	{
		Test_jiejuo_jilu.gongwei = 0x00;
	}
	else
	{
		Test_jiejuo_jilu.gongwei = 0x00;
	}
	DeBug_print("当前工位为%d\r\n",Test_jiejuo_jilu.gongwei);
}
//测试结果初始化
void test_jieguo_qingling()
{
	Test_jiejuo_jilu.VCC_dianya = 0;
	Test_jiejuo_jilu.zhidian_gongdiandianya = 0;
	Test_jiejuo_jilu.VDD_dianya = 0;
	Test_jiejuo_jilu.zhudian_gonghao = 0;
	Test_jiejuo_jilu.USBgongdian = 0;
	Test_jiejuo_jilu.flash_test = 0;
	memset(Test_jiejuo_jilu.zhukongban_xingshan_MAC,0x00,12);
	memset(Test_jiejuo_jilu.IMEI,0x00,15);
	memset(Test_jiejuo_jilu.ICCID,0x00,20);
	Test_jiejuo_jilu.CSQ = 0;
}
//开始测试
void test_start()
{
	//IO口恢复
	test_start_Init();
	//测试结果清零
	test_jieguo_qingling();
	Test_liucheng_L = w_start;
	//最大测试时间90秒
	Test_quanju_canshu_L.time_aroundtest_ms = 90000;
	Test_quanju_canshu_L.test_over = 0;
	Test_quanju_canshu_L.time_softdelay_ms = 0;
	DeBug_print("已开始测试，测试星闪MAC为%s\r\n",Test_jiejuo_jilu.zhuji_MAC);
}
//终止测试
//终止测试的条件是，测试时间过长，或是主控板离开了工装。
void test_testend()
{
	Test_liucheng_L = w_end;
	Test_quanju_canshu_L.test_over = 1;
	Test_quanju_canshu_L.time_softdelay_ms = 0;
}
//测试过程中的额外异常事件
void test_err_end_Func()
{
	//测试超时
	if(Test_quanju_canshu_L.time_aroundtest_ms==0&&Test_quanju_canshu_L.test_over==0)
	{
		//结束测试
		test_testend();
	}
}

void test_Loop_Func()
{
	test_err_end_Func();
	//Test_liucheng_L = w_gonghao_CHK;
	if(Test_quanju_canshu_L.time_softdelay_ms>0)
		return;
	switch(Test_liucheng_L)
	{
		case w_wait:
			//仅等待下一次测试
			break;
		case w_start:
			//开始测试前校验VDD是否有电，从而判断测试是否开始。
		  Test_jiejuo_jilu.VCC_dianya = get_VCC_weizhi_dianya();
		  DeBug_print("VCC电压%d\r\n",Test_jiejuo_jilu.VCC_dianya);
		  //测试合格条件判断
		  if(Test_jiejuo_jilu.VCC_dianya>3000&&Test_jiejuo_jilu.VCC_dianya<3600)
			{
				//测试合格，进入下一步
				Test_quanju_canshu_L.time_softdelay_ms = 0;
				Test_liucheng_L = w_zhudian_CHK;
			}
			else
			{
				//否则1秒复测一次
				Test_quanju_canshu_L.time_softdelay_ms = 1000;
			}
			break;
		case w_zhudian_CHK:
			Test_jiejuo_jilu.zhidian_gongdiandianya = get_zhudian_gongdian_weizhi_dianya();
		  DeBug_print("供电电压%d\r\n",Test_jiejuo_jilu.zhidian_gongdiandianya);
			if(Test_jiejuo_jilu.zhidian_gongdiandianya>5500&&Test_jiejuo_jilu.zhidian_gongdiandianya<6500)
			{
				//测试合格，进入下一步
				Test_quanju_canshu_L.time_softdelay_ms = 0;
				Test_liucheng_L = w_VDD_CHK;
			}
			else
			{
				//否则1秒复测一次
				Test_quanju_canshu_L.time_softdelay_ms = 1000;
			}
			break;
		case w_VDD_CHK:
			Test_jiejuo_jilu.VDD_dianya = get_erjidianyuan_weizhi_dianya();
		  DeBug_print("星闪供电%d\r\n",Test_jiejuo_jilu.VDD_dianya);
		  if(Test_jiejuo_jilu.VDD_dianya>3400&&Test_jiejuo_jilu.zhidian_gongdiandianya>4200)
			{
				//测试合格，进入下一步
				Test_quanju_canshu_L.time_softdelay_ms = 0;
				//此时可以认为USB供电正常
				Test_jiejuo_jilu.USBgongdian = 1;
				Test_liucheng_L = w_SWITCH_gongdian;
			}
			else
			{
				//否则1秒复测一次
				Test_quanju_canshu_L.time_softdelay_ms = 1000;
			}
			break;
		case w_SWITCH_gongdian://更换供电接口
			//主电源供电打开
			zhudian_gongdian_On();
			//备电电源打开
			beidian_gongdian_On();
		  //顺便拉高串口通信控制脚
		  Uart_shineng_ON();
		  Test_quanju_canshu_L.time_softdelay_ms = 0;
		  //下一步测试之前要先重置接收flag
		  test_xieyi_jilu_Rec = No_Receive;
		  Test_liucheng_L = w_set_biaohao;
			break;
		case w_set_biaohao:
			if(test_xieyi_jilu_Rec != connect_xingshan)
			{
				test_xieyi_jilu_Rec = No_Receive;
				TONGXIN_xieyifasong_NTST();
				//等待3秒自动重发
				Test_quanju_canshu_L.time_softdelay_ms = 3000;
			}
			else
			{
				//已设置星闪连接，进入下一步，等待5G网络连接完成
				//若通信成功，说明USB供电以及主电供电,flash都正常(没有flash程序起不来)
				Test_jiejuo_jilu.USBgongdian = 1;
				Test_jiejuo_jilu.flash_test = 1;
				test_xieyi_jilu_Rec = No_Receive;
				//清除接收flag
				get_imei_ICCID_flag = 0;
				Test_liucheng_L = w_fand_shanggao;
			}
			break;
		case w_fand_shanggao:
			if(test_xieyi_jilu_Rec != shanggao_zhengchang)
			{
				test_xieyi_jilu_Rec = No_Receive;
				TONGXIN_xieyifasong_ICDC();
				//等待3秒自动重发
				Test_quanju_canshu_L.time_softdelay_ms = 3000;
			}
			else
			{
				//5G信号获取完成
				test_xieyi_jilu_Rec = No_Receive;
				Test_liucheng_L = w_gonghao_CHK;
			}
			break;
		case w_gonghao_CHK:
			//主电源供电打开
			zhudian_gongdian_On();
			//备电电源打开
			beidian_gongdian_On();
			Test_jiejuo_jilu.zhudian_gonghao = Current_CHK_Func();
		  DeBug_print("测试电流%d\r\n",Test_jiejuo_jilu.zhudian_gonghao);
			Test_liucheng_L = w_end;
			break;
		case w_end:
			//主电源供电打开
			zhudian_gongdian_On();
			//备电电源打开
			beidian_gongdian_On();
			//一切测试都已结束，打开测试返回
		  Test_quanju_canshu_L.test_over = 1;
		  //回到第一步
		  Test_liucheng_L = w_wait;
			break;
		default:
			Test_liucheng_L = w_end;
			break;
	}
}
