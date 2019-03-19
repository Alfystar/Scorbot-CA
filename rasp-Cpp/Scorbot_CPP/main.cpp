#include <iostream>
#include "spisend.h"

using namespace std;

SpiSend *send;
int main()
{
    send = new SpiSend();

    setPWMSend s;
    strcpy(s.text,"Ciao Arduino");
    feedRet *r=send->sendPWM(&s);
    printf("%s\n",r->text);
    return 0;
}
