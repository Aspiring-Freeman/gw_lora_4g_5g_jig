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

// ����д�Ƚ��ַ�����Ҫ��ԭ���Ƚϻ�ʹ\0���ǽ�������
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

	while (pHead < lenth)
	{
		// +MAC: response (5 bytes header + 12 bytes MAC = 17 bytes minimum)
		if (pHead + sizeof(NTST_Receive) - 1 + 12 <= lenth &&
			bijiao_zifuchuan(NTST_Receive, &zufuchua[pHead], sizeof(NTST_Receive) - 1))
		{
			memcpy(Test_jiejuo_jilu.zhukongban_xingshan_MAC, &zufuchua[pHead + 5], 12);
			test_xieyi_jilu_Rec = connect_xingshan;
			// ���յ���������������ȴ�
			Test_quanju_canshu_L.time_softdelay_ms = 0;
			DeBug_print("���ذ�����%s\r\n", Test_jiejuo_jilu.zhukongban_xingshan_MAC);
			pHead += 17;
			continue;
		}
		// +SLEMAC response (7 bytes match, skip ': ' then 12 bytes MAC)
		else if (pHead + sizeof(NTST_Receive_NEW) - 1 + 2 + 12 <= lenth &&
				 bijiao_zifuchuan(NTST_Receive_NEW, &zufuchua[pHead], sizeof(NTST_Receive_NEW) - 1))
		{
			memcpy(Test_jiejuo_jilu.zhukongban_xingshan_MAC, &zufuchua[pHead + 9], 12);
			test_xieyi_jilu_Rec = connect_xingshan;
			Test_quanju_canshu_L.time_softdelay_ms = 0;
			DeBug_print("SLEMAC:%.12s\r\n", Test_jiejuo_jilu.zhukongban_xingshan_MAC);
			pHead += 21;
			continue;
		}
		// IMEI: response (6 bytes header + 15 bytes IMEI = 21 bytes minimum)
		else if (pHead + sizeof(Get_IMEI) - 1 + 15 <= lenth &&
				 bijiao_zifuchuan(Get_IMEI, &zufuchua[pHead], sizeof(Get_IMEI) - 1))
		{
			memcpy(Test_jiejuo_jilu.IMEI, &zufuchua[pHead + 6], 15);
			DeBug_print("IMEI%.15s\r\n", Test_jiejuo_jilu.IMEI);
			get_imei_ICCID_flag |= 0x01;
			pHead += 21;
			continue;
		}
		// ICCID: response (7 bytes header + 20 bytes ICCID = 27 bytes minimum)
		else if (pHead + sizeof(Get_ICCID) - 1 + 20 <= lenth &&
				 bijiao_zifuchuan(Get_ICCID, &zufuchua[pHead], sizeof(Get_ICCID) - 1))
		{
			memcpy(Test_jiejuo_jilu.ICCID, &zufuchua[pHead + 7], 20);
			DeBug_print("ICCID%.20s\r\n", Test_jiejuo_jilu.ICCID);
			get_imei_ICCID_flag |= 0x02;
			pHead += 27;
			continue;
		}
		// CSQ: response (5 bytes header + 2+ bytes data = 7 bytes minimum)
		else if (pHead + sizeof(Get_CSQ) - 1 + 2 <= lenth &&
				 bijiao_zifuchuan(Get_CSQ, &zufuchua[pHead], sizeof(Get_CSQ) - 1))
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
			continue;
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
	// PC_Chuankou_tongxin_Debug_send(ICDC_SET,sizeof(ICDC_SET)-1);
}
