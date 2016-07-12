#include "KeySender.hpp"
#include "Configuration.hpp"

std::wstring getForegroundTitle()
{
    wchar_t title[256];
    GetWindowText(GetForegroundWindow(), title, sizeof(title));
    return title;
}

int main()
{
    KeySender MainKeySender;
    Configuration config("config.txt"); 
    std::vector<std::string>::iterator it;
    std::wstring title;
    const char *text;
    bool isRunning = true;
    
    while(isRunning)
    {
        // Only type ingame
        title = getForegroundTitle();
        if(title.find(config.gameTitle) != std::string::npos)
        {
            for(it = config.ads.begin(); it != config.ads.end(); it++)
            {
                if(*it == "")
                    continue;

                MainKeySender.writeChar(config.chatKey);

                // We iterate over the chars to control the speed
                text = it->c_str();
                for(int i = 0; text[i] != '\0'; i++)
                {
                    if(i % config.charsPerBlock == 0)
                    {
                        // Give the game time to process the input
                        Sleep(config.sleepBetweenBlocks);
                    }
                    MainKeySender.writeChar(text[i]);
                    Sleep(config.sleepBetweenLetters);
                }
                // This should be a simple return
                MainKeySender.writeChar('\r');
            }
        }

        // Sleep between Ads while checking the exitKey
        for(int i = 0; i < 1000 * config.secondsBetweenAds; i++)
        {
            Sleep(1);
            if(GetAsyncKeyState(config.exitKey))
            {
                isRunning = false;
                break;
            }
        }
    }
    return 0;
}
