#ifndef __DSL_H
#define __DSL_H		



void DSLTask (void);
void DSLCRC_Send (char * data,char fun);
void SendCom( char * data);
unsigned char DSLCRC_Receive(char *data);


extern unsigned int Value25 ,Value10;




#endif
