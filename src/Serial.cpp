#include "Serial.h"

void Serial_Setup(Serial_t &Stemp)
{
    Stemp.autocl = 0;
    Stemp.cmd = 0;
    Serial.begin(SERIAL_RATE);
    while (!Serial)
    {
    }
    Serial.print("UART STARTED!");
}

void Serial_Ctrl(Serial_t &Stemp)
{
    if (Serial.available() > 0)
    {
        static String data = "";
        data += char(Serial.read());
        data.trim();
        if (data.length() == 4)
        {
            if (data.startsWith("car"))
            {
                switch (char(data.end()))
                {
                case 'n':
                    Stemp.autocl = 1;
                    break;
                case 'f':
                    Stemp.autocl = 0;
                    Stemp.cmd = 's';
                    break;
                case 'u':
                    Stemp.cmd = 'u';
                    break;
                case 'd':
                    Stemp.cmd = 'd';
                    break;
                case 'r':
                    Stemp.cmd = 'r';
                    break;
                case 'l':
                    Stemp.cmd = 'l';
                    break;
                case 's':
                    Stemp.cmd = 's';
                    break;

                default:
                    break;
                }
            }
            data = "";
        }
    }
}
