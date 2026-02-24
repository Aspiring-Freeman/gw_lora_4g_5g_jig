#include "GPIO.h"
#include "tongxin_xieyi_Ctrl.h"
#include "uart1.h"
#include "uart0.h"
#include "Test_List.h"

uint8_t NTST_SET[] = "NTST 000000000000\r\n";
uint8_t ICDC_SET[] = "ICDC\r\n";
uint8_t NTST_Receive[] = "+MAC:";
uint8_t NTST_Receive_NEW[] = "+SLEMAC";
uint8_t Get_IMEI[] = "IMEI: ";
uint8_t Get_ICCID[] = "ICCID: ";
uint8_t Get_CSQ[] = "CSQ: ";
uint8_t get_imei_ICCID_flag = 0;

uint8_t bijiao_zifuchuan(uint8_t bijiao1[], uint8_t bijiao2[], uint16_t lenth)
{
	uint16_t bijiao_lenth = 0;
	for (bijiao_lenth = 0; bijiao_lenth < lenth; bijiao_lenth++)
	{
		if (bijiao1[bijiao_lenth] != bijiao2[bijiao_lenth])
		{
			return 0;
		}
	}
	return 1;
}

void TONGXIN_xieyijiexi(uint8_t zufuchua[], uint16_t lenth)
{
	uint16_t pHead = 0;

	while (1)
	{
		if (pHead > lenth)
		{
			break;
		}
		if (bijiao_zifuchuan(NTST_Receive, &zufuchua[pHead], sizeof(NTST_Receive) - 1))
		{
			memcpy(Test_jiejuo_jilu.zhukongban_xingshan_MAC, &zufuchua[pHead + 5], 12);
			test_xieyi_jilu_Rec = connect_xingshan;
			Test_quanju_canshu_L.time_softdelay_ms = 0;
			// DeBug_print("Current connected xingshan MAC: %s\r\n", Test_jiejuo_jilu.zhukongban_xingshan_MAC);
			DeBug_print("Get received mark: %s\r\n", Test_jiejuo_jilu.zhukongban_xingshan_MAC);
			pHead += 24;
		}
		// 新的+MAC:格式，兼容老的
		if (bijiao_zifuchuan(NTST_Receive_NEW, &zufuchua[pHead], sizeof(NTST_Receive_NEW) - 2))
		{
			memcpy(Test_jiejuo_jilu.zhukongban_xingshan_MAC, &zufuchua[pHead + 8], 12);
			test_xieyi_jilu_Rec = connect_xingshan;
			Test_quanju_canshu_L.time_softdelay_ms = 0;
			// DeBug_print("Current connected xingshan MAC: %s\r\n", Test_jiejuo_jilu.zhukongban_xingshan_MAC);
			DeBug_print("Get received mark SLEMAC: %s\r\n", Test_jiejuo_jilu.zhukongban_xingshan_MAC);
			pHead += 27;
		}
		if (bijiao_zifuchuan(Get_IMEI, &zufuchua[pHead], sizeof(Get_IMEI) - 1))
		{
			memcpy(Test_jiejuo_jilu.IMEI, &zufuchua[pHead + 6], 15);
			DeBug_print("IMEI%s\r\n", Test_jiejuo_jilu.IMEI);
			get_imei_ICCID_flag |= 0x01;
			pHead += 23;
		}
		if (bijiao_zifuchuan(Get_ICCID, &zufuchua[pHead], sizeof(Get_ICCID) - 1))
		{
			memcpy(Test_jiejuo_jilu.ICCID, &zufuchua[pHead + 7], 20);
			DeBug_print("ICCID%s\r\n", Test_jiejuo_jilu.ICCID);
			get_imei_ICCID_flag |= 0x02;
			pHead += 27;
		}
		if (bijiao_zifuchuan(Get_CSQ, &zufuchua[pHead], sizeof(Get_CSQ) - 1))
		{
			Test_jiejuo_jilu.CSQ = zufuchua[pHead + 5] - '0';
			Test_jiejuo_jilu.CSQ = Test_jiejuo_jilu.CSQ * 10;
			Test_jiejuo_jilu.CSQ += zufuchua[pHead + 6] - '0';
			if (Test_jiejuo_jilu.CSQ > 10 && Test_jiejuo_jilu.CSQ < 40 && get_imei_ICCID_flag == 0x03)
			{
				test_xieyi_jilu_Rec = shanggao_zhengchang;
				// ���յ���������������ȴ�
				Test_quanju_canshu_L.time_softdelay_ms = 0;
			}
			DeBug_print("CSQ%d\r\n", Test_jiejuo_jilu.CSQ);
			pHead += 9;
		}
		pHead++;
	}
}
void TONGXIN_xieyifasong_NTST()
{
	memcpy(&NTST_SET[5], Test_jiejuo_jilu.zhuji_MAC, 12);
	Uart0_Tx_Send(NTST_SET, sizeof(NTST_SET) - 1);
	PC_Chuankou_tongxin_Debug_send(NTST_SET, sizeof(NTST_SET) - 1);
}

void TONGXIN_xieyifasong_ICDC()
{
	Uart0_Tx_Send(ICDC_SET, sizeof(ICDC_SET) - 1);
	PC_Chuankou_tongxin_Debug_send(ICDC_SET, sizeof(ICDC_SET) - 1);
}
