#include "DSL-08.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

char RE_Command[]={0xAA,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbb};

unsigned int Value25,Value10;
uint16_t buff;


void DSLTask (void)  
{ 
	DSLCRC_Send((char *)RE_Command,0x02);
  SendCom((char *)RE_Command);
	delay_ms(100);
	if((USART_RX_STA&0x8000))
	{ 
		if(DSLCRC_Receive((char *)USART_RX_BUF))
		{
		Value25 = USART_RX_BUF[4]*256+USART_RX_BUF[5];
		Value10 = USART_RX_BUF[2]*256+USART_RX_BUF[3];
		}
		USART_RX_STA=0;
	}
}

void SendCom( char * data)
	
{	
	unsigned int i;	
	for(i=0;i<9;i++)
	{
		buff = data[i];
		USART_SendData(USART1, buff);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	}
	
}

/******************************************

@接收发送校验


******************************************/

void DSLCRC_Send (char * data,char fun) 
{	
	char i;
	unsigned int SUM=0u;
	for(i=0;i<9;i++)
	{ 
		if(i!=6&&i!=7)
		SUM=SUM+data[i];
	}
	data[6]=SUM/256;
	data[7]=SUM%256;
	data[1]=fun;
}


unsigned char DSLCRC_Receive(char *data)    
{
  char result;
	unsigned int SUM=0u;
	char i;
	for(i=0;i<9;i++)
	{ 
		if(i!=6&&i!=7)
		SUM=SUM+data[i];
	}
	if(data[6]==SUM/256&&data[7]==SUM%256)
	result=1;
	else 
	result=0;	
	return result;
	
}
