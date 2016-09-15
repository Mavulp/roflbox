#include "KeySender.hpp"
#include "Configuration.hpp"

std::string getForegroundTitle()
{
    wchar_t title[256];
    GetWindowText(GetForegroundWindow(), title, sizeof(title));
    std::wstring ws(title);
    return std::string(ws.begin(), ws.end());
}

int main()
{
    KeySender MainKeySender;
    Configuration config("config.toml");

    std::vector<Ad>::iterator adIt;
    std::vector<std::string>::iterator stringIt;
    std::string title;
    const char *text;
    bool isRunning = true;

    while(isRunning)
    {
        // Only type ingame
        title = getForegroundTitle();
        if(title.find(config.gameTitle) != std::string::npos)
        {
            for(adIt = config.ads.begin(); adIt != config.ads.end(); adIt++)
            {
                for(stringIt = adIt->messages.begin(); stringIt != adIt->messages.end(); stringIt++)
                {
                    if(*stringIt == "")
                        continue;

                    MainKeySender.writeChar(config.chatKey);

                    // We iterate over the chars to control the speed
                    text = stringIt->c_str();
                    for(int i = 0; text[i] != '\0'; i++)
                    {
                        if(i % adIt->charsPerBlock == 0)
                        {
                            // Give the game time to process the input
                            Sleep(adIt->sleepBetweenBlocks);
                        }
                        MainKeySender.writeChar(text[i]);
                        Sleep(adIt->sleepBetweenChars);
                    }
                    // This should be a simple return
                    MainKeySender.writeChar('\r');
                }
            }
        }

        // TODO Make use of "secondsBetweenAds"
        // Sleep between Ads while checking the exitKey
        for(int i = 0; i < 1000 * 30; i++)
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
