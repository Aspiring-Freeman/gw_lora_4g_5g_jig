#ifndef __TEST_LIST_H__
#define __TEST_LIST_H__
#include "main.h"

struct Test_quanju_canshu
{
	uint16_t time_softdelay_ms;
	uint32_t time_aroundtest_ms;
	uint8_t test_over;
};
extern struct Test_quanju_canshu Test_quanju_canshu_L;

struct Test_jieguo
{
	uint8_t gongwei;
	uint8_t zhuji_MAC[12];
	uint32_t VCC_dianya;
	uint32_t zhidian_gongdiandianya;
	uint32_t VDD_dianya;
	uint16_t zhudian_gonghao;
	uint8_t  USBgongdian;
	uint8_t  flash_test;
	uint8_t  zhukongban_xingshan_MAC[12];
	uint8_t  IMEI[15];
	uint8_t  ICCID[20];
	uint8_t  CSQ;
};
extern struct Test_jieguo Test_jiejuo_jilu;

enum Test_liucheng
{
	w_wait = 0,
	//3.3V VCC检测
	w_start,
	//电压供电检测
	w_zhudian_CHK,
	//VDD电压检测
	w_VDD_CHK,
	//转换供电，转由5V接口供电
	w_SWITCH_gongdian,
	//设置表号，并开启连接
	w_set_biaohao,
	//查询上告信息
	w_fand_shanggao,
	//功耗测试
	w_gonghao_CHK,
	w_end
};
extern enum Test_liucheng Test_liucheng_L;

enum test_xieyi_jilu
{
	connect_xingshan = 0,
	shanggao_zhengchang,
	No_Receive
};
extern enum test_xieyi_jilu test_xieyi_jilu_Rec;

void test_Loop_Func(void);

//工位检测
void gongwei_jiance(void);
//开始测试前恢复标志位
void test_start_Init(void);
//开始测试
void test_start(void);
#endif
