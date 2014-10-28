// IR receive for LinkIt ONE
// IR connect to D2 of LinkIt ONE
#include "IR_Recv_LinkIt.h"


void __ISR()
{
    IR.isr();
}

void IR_Recv_LinkIt::begin(int ext_isr_num)
{
    if(ext_isr_num>3 || ext_isr_num<2)
    pinMode(2, INPUT_PULLUP);
    attachInterrupt(0, __ISR, CHANGE);
}

void IR_Recv_LinkIt::isr()
{
    dta[len++] = micros()-timer_1;
    timer_1 = micros();
}

bool IR_Recv_LinkIt::isDta()                   // if get data
{
    return (len>0);
}


// return 0: no data
unsigned char IR_Recv_LinkIt::getDta(int *dtaRecv)
{
    if(!isDta())return 0;
    delay(200);             // wait for data receive ok
    
    int start_loca1 = 5000;
    int start_loca2 = 5000;
    int end_loca    = 5000;
    
    dta[len++] = 10001;
    
    for(int i=0; i<len; i++)
    {
        if(start_loca1 == 5000 && dta[i]>8800 && dta[i]<9500)          // get the start 9ms
        {
            start_loca1 = i;
        }
        else if(start_loca1 < 5000 && dta[i]>4000 && dta[i]<5000)          // get the start 4.5ms
        {
            start_loca2 = i;
        }
        else if(start_loca2 < 5000 && dta[i] > 10000)
        {
            end_loca = i;
            break;
        }
    }

#if DBG
    Serial.print("\r\nstart loca : ");
    Serial.print(start_loca1);
    Serial.print('\t');
    Serial.println(start_loca2);
    
    Serial.print("end loca = ");
    Serial.println(end_loca);
#endif
    int tmp = end_loca - start_loca2-2;
    
    if((start_loca1+start_loca2+end_loca) >= 5000)
    {
        len = 0;
        return 0;
    }

    if(tmp != 64)
    {
        len = 0;
        return 0;
    }
    
    int count_data  = tmp/16;

    int nshort = 0;
    int nlong  = 0;
    
    // find short and long here
    for(int i=0; i<8; i++)
    {
        nshort += dta[2*i+start_loca2+1];
    }
    
    nshort = nshort>>3;
    
    int doubleshort = 2*nshort;             // todo: write a code to find double short
    
    for(int i = 0; i<count_data; i++)
    {
        dtaRecv[i+D_DATA] = 0x00;
        for(int j = 0; j<8; j++)
        {
            if(dta[16*i + j*2+1+start_loca2+1] > doubleshort) // 1
            {
                dtaRecv[i+D_DATA] |= 0x01<< (7-j);
            }
            else
            {
                dtaRecv[i+D_DATA] &= ~(0x01<<(7-j));
            }
        }
    }

#if DBG
    Serial.println();
#endif 
    
    dtaRecv[D_LEN]      = count_data+5;
    dtaRecv[D_STARTH]   = dta[start_loca1];
    dtaRecv[D_STARTL]   = dta[start_loca2];
    dtaRecv[D_SHORT]    = nshort;
    dtaRecv[D_LONG]     = nshort*3;
    dtaRecv[D_DATALEN]  = count_data;
    
    
#if DBG
    Serial.print("\r\n*************************************************************\r\n");
    Serial.print("len\t = ");Serial.println(dtaRecv[D_LEN]);
    Serial.print("start_h\t = ");Serial.println(dtaRecv[D_STARTH]);
    Serial.print("start_l\t = ");Serial.println(dtaRecv[D_STARTL]);
    Serial.print("short\t = ");Serial.println(dtaRecv[D_SHORT]);
    Serial.print("long\t = ");Serial.println(dtaRecv[D_LONG]);
    Serial.print("data_len = ");Serial.println(dtaRecv[D_DATALEN]);
    for(int i = 0; i<dtaRecv[D_DATALEN]; i++)
    {
        Serial.print(dtaRecv[D_DATA+i]);Serial.print("\t");
    }
    Serial.print("\r\n*************************************************************\r\n");
#endif

    len = 0;
    return 1;

}


IR_Recv_LinkIt IR;
    