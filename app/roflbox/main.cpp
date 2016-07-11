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

    Sleep(1000*10);
    ks.setDelay(2);
    while(true)
    {
        title = getForegroundTitle();
        if(title.find(L"Rocket League") != std::string::npos)
        {
            ks.writeKey('t');
            Sleep(160);
            ks.writeString("WWW.ROFLBOX.WEBSITE");
            Sleep(160);
            ks.writeString(" - BEST FREE RL HACK!\n");

            Sleep(160);

            ks.writeKey('t');
            Sleep(160);
            ks.writeString("GET GOOD, GET ROFLBOX!");
            ks.writeKey('\n');

            Sleep(1000 * 10);
        }
    }
    return 0;
}
