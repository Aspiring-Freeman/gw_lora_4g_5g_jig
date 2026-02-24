#include "GPIO.h"
#include "PC_xieyi_Ctrl.h"
#include "Test_List.h"
#include "uart0.h"
#include "uart1.h"
#define send_lenth 200
uint8_t xieyi1_fanhui[5] = {0x68, 0xAB, 0x00, 0x13, 0x16};
uint8_t xieyi2_fanhui[send_lenth];
// 寮�濮嬫祴璇曡缃垚鍔熷悗鍙戦�?
void PC_xieyifasong_1()
{
	DeBug_print("PC_xieyifasong_1:Current station is %d\r\n", Test_jiejuo_jilu.gongwei);
	xieyi1_fanhui[2] = Test_jiejuo_jilu.gongwei;
	xieyi1_fanhui[3] = 0x13 + xieyi1_fanhui[2];
	// Uart0_Tx_Send(xieyi1_fanhui,5);
	PC_Chuankou_tongxin_send(xieyi1_fanhui, 5);
}
// 鏌ヨ缁撴灉
void PC_xieyifasong_2()
{
	uint16_t jishu_lenth = 0;
	uint16_t hejiaoyan = 0;
	memset(xieyi2_fanhui, 0x00, send_lenth);
	xieyi2_fanhui[jishu_lenth++] = 0x68;
	xieyi2_fanhui[jishu_lenth++] = 0xAD;
	xieyi2_fanhui[jishu_lenth++] = Test_jiejuo_jilu.gongwei;
	xieyi2_fanhui[jishu_lenth++] = ((Test_jiejuo_jilu.zhidian_gongdiandianya / 10) >> 8) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = (Test_jiejuo_jilu.zhidian_gongdiandianya / 10) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = ((Test_jiejuo_jilu.zhudian_gonghao / 10) >> 8) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = (Test_jiejuo_jilu.zhudian_gonghao / 10) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = ((Test_jiejuo_jilu.VDD_dianya / 10) >> 8) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = (Test_jiejuo_jilu.VDD_dianya / 10) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = ((Test_jiejuo_jilu.VCC_dianya / 10) >> 8) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = (Test_jiejuo_jilu.VCC_dianya / 10) & 0xFF;
	xieyi2_fanhui[jishu_lenth++] = Test_jiejuo_jilu.USBgongdian;
	xieyi2_fanhui[jishu_lenth++] = Test_jiejuo_jilu.flash_test;
	memcpy(&xieyi2_fanhui[jishu_lenth], Test_jiejuo_jilu.zhukongban_xingshan_MAC, 12);
	jishu_lenth += 12;
	memcpy(&xieyi2_fanhui[jishu_lenth], Test_jiejuo_jilu.IMEI, 15);
	jishu_lenth += 15;
	memcpy(&xieyi2_fanhui[jishu_lenth], Test_jiejuo_jilu.ICCID, 20);
	jishu_lenth += 20;
	xieyi2_fanhui[jishu_lenth++] = Test_jiejuo_jilu.CSQ;
	xieyi2_fanhui[jishu_lenth] = 0;
	for (hejiaoyan = 0; hejiaoyan < jishu_lenth; hejiaoyan++)
	{
		xieyi2_fanhui[jishu_lenth] += xieyi2_fanhui[hejiaoyan];
	}
	jishu_lenth++;
	xieyi2_fanhui[jishu_lenth++] = 0x16;
	PC_Chuankou_tongxin_send(xieyi2_fanhui, jishu_lenth);
}

void PC_xieyijiexi(uint8_t zufuchua[], uint16_t lenth)
{
	uint16_t pHead = 0;
	uint8_t hejiaoyan = 0;
	uint16_t zhenchangdu = 0;
	uint16_t i;

	DeBug_print("*** PC_xieyijiexi() called, len=%d ***\r\n", lenth);
	// 输出接收到的原始数据（前20字节）
	DeBug_print("Data: ");
	for (i = 0; i < (lenth > 20 ? 20 : lenth); i++)
	{
		DeBug_print("%02X ", zufuchua[i]);
	}
	DeBug_print("\r\n");

	while (1)
	{
		if (pHead + 4 > lenth)
		{
			break;
		}
		if (zufuchua[pHead] == 0x68)
		{
			DeBug_print("Found 0x68 at pos %d\r\n", pHead);
			if (zufuchua[pHead + 1] == 0xAA)
			{
				DeBug_print("CMD=0xAA\r\n");
				DeBug_print("RX_Station=%d\r\n", zufuchua[pHead + 2]);
				DeBug_print("Local_Station=%d\r\n", Test_jiejuo_jilu.gongwei);
				if (zufuchua[pHead + 2] != Test_jiejuo_jilu.gongwei)
				{
					DeBug_print("!!! Station MISMATCH !!!\r\n");
				}
			}

			if (zufuchua[pHead + 1] == 0xAA && zufuchua[pHead + 2] == Test_jiejuo_jilu.gongwei && zufuchua[pHead + 16] == 0x16)
			{
				// 杩涜鍜屾牎楠?
				hejiaoyan = 0;
				for (zhenchangdu = 0; zhenchangdu < 15; zhenchangdu++)
				{
					hejiaoyan += zufuchua[pHead + zhenchangdu];
				}
				if (hejiaoyan == zufuchua[pHead + 15])
				{
					memcpy(Test_jiejuo_jilu.zhuji_MAC, &zufuchua[pHead + 3], 12);
					DeBug_print("\r\n[PC] Received START command\r\n");
					DeBug_print("MAC: %.12s\r\n", Test_jiejuo_jilu.zhuji_MAC);
					FL_DelayMs(10);
					test_start();
					FL_DelayMs(10);
					DeBug_print("[PC] Sending ACK...\r\n");
					PC_xieyifasong_1();
					pHead += 15;
				}
			}
			else if (zufuchua[pHead + 1] == 0xAC && zufuchua[pHead + 2] == Test_jiejuo_jilu.gongwei && zufuchua[pHead + 4] == 0x16)
			{
				// 杩涜鍜屾牎楠?
				hejiaoyan = 0;
				for (zhenchangdu = 0; zhenchangdu < 3; zhenchangdu++)
				{
					hejiaoyan += zufuchua[pHead + zhenchangdu];
				}
				if (hejiaoyan == zufuchua[pHead + 3])
				{
					if (Test_quanju_canshu_L.test_over == 1)
					{
						PC_xieyifasong_2();
					}
					pHead += 3;
				}
			}
		}
		pHead++;
	}
}
