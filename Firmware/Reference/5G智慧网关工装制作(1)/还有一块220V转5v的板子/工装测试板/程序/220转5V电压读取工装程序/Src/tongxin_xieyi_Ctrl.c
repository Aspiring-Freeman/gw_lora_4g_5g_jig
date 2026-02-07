#include "GPIO.h"
#include "tongxin_xieyi_Ctrl.h"
#include "uart1.h"
#include "uart0.h"
#include "Test_List.h"
uint8_t send_xieyi_data[200];


void TONGXIN_xieyijiexi(uint8_t zufuchua[],uint16_t lenth)
{
	uint16_t pHead = 0;
	uint16_t shujuyu_changdu = 0;
	while(1)
	{
		if(pHead+21>lenth)
		{
			break;
		}
		if(zufuchua[pHead]==0x68)
		{
			if(zufuchua[pHead+7]==0x68)
			{
				//获取数据域长度
				shujuyu_changdu = zufuchua[pHead+10];
				shujuyu_changdu = shujuyu_changdu<<8;
				shujuyu_changdu += zufuchua[pHead+9];
				if(zufuchua[pHead+12+shujuyu_changdu]==0x16)
				{
				//校验完成，接下来是协议解析部分
				//控制码
				if(zufuchua[pHead+8]==0x84)
				{
					//1008
					if(zufuchua[pHead+18] == 0x09&&zufuchua[pHead+19] == 0x10)
					{
						//主电电压读取

						 //119数据处理
						
							//接收到指令立刻进入下一步
					
						 Test_quanju_canshu_L.time_softdelay_ms = 0;
					}
				}
				//协议解析部分结束
				pHead = pHead+10+shujuyu_changdu;
				}
			}
		}
		pHead++;
	}
}
void TONGXIN_xieyifasong()
{
	uint16_t send_data_lenth = 0;
	uint16_t hejiaoyan = 0;
	send_xieyi_data[send_data_lenth++] = 0x68;
	//表号00 00 00 01 00 00
	send_xieyi_data[send_data_lenth++] = 0x00;
	send_xieyi_data[send_data_lenth++] = 0x00;
	send_xieyi_data[send_data_lenth++] = 0x00;
	send_xieyi_data[send_data_lenth++] = 0x01;
	send_xieyi_data[send_data_lenth++] = 0x00;
	send_xieyi_data[send_data_lenth++] = 0x00;
	send_xieyi_data[send_data_lenth++] = 0x68;
	//控制码
	send_xieyi_data[send_data_lenth++] = 0x04;
	//数据域长度
	send_xieyi_data[send_data_lenth++] = 0x0A;
	send_xieyi_data[send_data_lenth++] = 0x00;
	//系统时钟24 09 20 13 22 01 16
	send_xieyi_data[send_data_lenth++] = 0x24;
	send_xieyi_data[send_data_lenth++] = 0x09;
	send_xieyi_data[send_data_lenth++] = 0x20;
	send_xieyi_data[send_data_lenth++] = 0x13;
	send_xieyi_data[send_data_lenth++] = 0x22;
	send_xieyi_data[send_data_lenth++] = 0x01;
	send_xieyi_data[send_data_lenth++] = 0x16;
	//数据标识
	send_xieyi_data[send_data_lenth++] = 0x09;
	send_xieyi_data[send_data_lenth++] = 0x10;
	//协议包数
	send_xieyi_data[send_data_lenth++] = 0x00;
	send_xieyi_data[send_data_lenth] = 0;
	for(hejiaoyan=0;hejiaoyan<send_data_lenth;hejiaoyan++)
	{
		send_xieyi_data[send_data_lenth]+=send_xieyi_data[hejiaoyan];
	}
	send_data_lenth++;
	send_xieyi_data[send_data_lenth++] = 0x16;
	Uart0_Tx_Send(send_xieyi_data,send_data_lenth);
	PC_Chuankou_tongxin_Debug_send(send_xieyi_data,send_data_lenth);
}



