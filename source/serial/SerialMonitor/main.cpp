
#include <cstdio>
#include "../CSerial.h"

int main(int argc, char* argv[])
{
        CSerial serial;
        serial.startSerial();
        
        	  
        while (1)      
        {                                      
            const char c = serial.readChar();
            printf("%c\n", c);
        }
        return 0;
}

