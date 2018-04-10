IR Recv LinkIt ONE
---------------------------------------------------------

[![Grove - Infrared Receiver](https://statics3.seeedstudio.com/images/101020016%201.jpg)](http://www.seeedstudio.com/depot/grove-infrared-receiver-p-994.html?cPath=19_23)

The Infrared Receiver is used to receive infrared signals and also used for remote control detection. There is a IR detector on the Infrared Receiver which is used to get the infrared light emitted by the Infrared Emitter. The IR detector have a demodulator inside that looks for modulated IR at 38 KHz. The Infrared Receiver can receive signals well within 10 meters. If more than 10 meters , the receiver may not get the signals. We often use the two Twigs-the Infrared Receiver and the Infrared Emitter to work together.


**This Library is used for LinkIt ONE only**

# Usage:

This library include 2parts, ir send and ir receive.

### Send Data

You can use this function to send a buf:

    void Send(unsigned char *dta_buf, unsigned char ifreq);


- dta_buf[0] len of the buf(not include dta_buf[0])
- dta_buf[1] start signal high time
- dta_buf[2] start signal low time
- dta_buf[3] bit high time
- dta_buf[4] bit low time
- dta_buf[5] data lenght(how many byte to send)
- dta_buf[6] dta_buf[n] : data to send

- ifreq: frequence, eg:38(means 38k)

![](http://www.seeedstudio.com/wiki/images/4/40/Ir_time.jpg)


### Receive Data

**Initialize:**

    IR.begin(int ext_isr_num);		// pin to receive

**Check Data:**

	IR.isDta();			// if get data, return 1

**Receive Data:**

	IR.getDta(int *dta);	



For more information, please refer to [wiki page](http://www.seeedstudio.com/wiki/).

    
----


This software is written by loovee [luweicong@seeedstudio.com](luweicong@seeedstudio.com "luweicong@seeedstudio.com") for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>





[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/IRSendRev)](https://github.com/igrigorik/ga-beacon)
