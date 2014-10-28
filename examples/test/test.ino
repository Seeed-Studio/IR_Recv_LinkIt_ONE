// test code for IR Recv LinkIt ONE
#include <IR_Recv_LinkIt.h>

int ir_dta[15];

void setup()
{
    Serial.begin(115200);
    
    IR.begin();             // initialize
} 


void loop()
{
    if(IR.isDta())
    {
        if(IR.getDta(ir_dta))
        {
            Serial.print("\r\n*********GET DATA FROM IR REMOTE***************************\r\n");
            Serial.print("len\t = ");Serial.println(ir_dta[D_LEN]);
            Serial.print("start_h\t = ");Serial.println(ir_dta[D_STARTH]);
            Serial.print("start_l\t = ");Serial.println(ir_dta[D_STARTL]);
            Serial.print("short\t = ");Serial.println(ir_dta[D_SHORT]);
            Serial.print("long\t = ");Serial.println(ir_dta[D_LONG]);
            Serial.print("data_len = ");Serial.println(ir_dta[D_DATALEN]);
            for(int i = 0; i<ir_dta[D_DATALEN]; i++)
            {
                Serial.print(ir_dta[D_DATA+i]);Serial.print("\t");
            }
            Serial.print("\r\n*************************************************************\r\n\r\n");
        }
    }

}