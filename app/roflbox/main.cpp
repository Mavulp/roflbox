#include "KeySender.hpp"
#include <string>

std::wstring getForegroundTitle()
{
    wchar_t title[256];
    GetWindowText(GetForegroundWindow(), title, sizeof(title));
    return title;
}

int main()
{
    KeySender ks;
    std::wstring title;
    bool isRunning = true;

    ks.setDelay(2);
    
    while(isRunning)
    {
        title = getForegroundTitle();
        if(title.find(L"TeamSpeak") != std::string::npos)
        {
            ks.writeKey('t');
            Sleep(160);
            ks.writeString("WWW.ROFLBOX.WEBSITE");
            Sleep(160);
            ks.writeString(" - BEST FREE RL HACK!\n");

            Sleep(160);

            ks.writeKey('t');
            Sleep(160);
            ks.writeString("GET GOOD, GET ROFLBOX!\n");
        }

        for(int i = 0; i < 1000 * 10; i++)
        {
            Sleep(1);
            if(GetAsyncKeyState(VK_F10))
            {
                isRunning = false;
                break;
            }
        }
    }
    return 0;
}
