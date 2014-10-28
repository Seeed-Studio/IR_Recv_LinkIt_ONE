// IR receive for LinkIt ONE
#ifndef __IR_RECV_LINKIT_H__
#define __IR_RECV_LINKIT_H__

#include <Arduino.h>

#define DBG     0

#define D_LEN       0
#define D_STARTH    1
#define D_STARTL    2
#define D_SHORT     3
#define D_LONG      4
#define D_DATALEN   5
#define D_DATA      6


class IR_Recv_LinkIt{

private:

    int len;
    int dta[500];
    int timer_1;

public:

    void begin(int ext_isr_num);                   // initialize
    bool isDta();                   // if get data
    void isr();                     // ext interrupt

    unsigned char getDta(int *dtaRecv);         // get data

};

extern IR_Recv_LinkIt IR;


#endif