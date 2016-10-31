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

    std::string title;
    const char *text;
    bool isRunning = true;

    typedef std::chrono::duration<float> floatSeconds;

    while(!GetAsyncKeyState(config.exitKey))
    {
        // Only type ingame
        title = getForegroundTitle();
        if(title.find(config.gameTitle) != std::string::npos)
        {
            // Make sure that Keyboard/Mouse don't interrupt the input
            BlockInput(true);

            auto now = std::chrono::system_clock::now();

            for(auto adIt = config.ads.begin(); adIt != config.ads.end(); adIt++)
            {
                auto secs = std::chrono::duration_cast<floatSeconds>(now - adIt->secondsSinceDisplay);

                if(secs.count() < adIt->secondsBetweenAds)
                    continue;

                adIt->secondsSinceDisplay = now;

                for(auto stringIt = adIt->messages.begin(); stringIt != adIt->messages.end(); stringIt++)
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
            BlockInput(false);
        }

        Sleep(100);
    }
    return 0;
}
