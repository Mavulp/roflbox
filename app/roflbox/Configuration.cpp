#include "Configuration.hpp"
#include <fstream>
#include <sstream>

Configuration::Configuration()
{
    init();
}

Configuration::Configuration(std::string path)
{
    init();
    readFromPath(path);
}

void Configuration::init()
{
    charsPerBlock = 15;
    sleepBetweenBlocks = 150;
    sleepBetweenLetters = 2;
    secondsBetweenAds = 30;
    exitKey = 121;
    chatKey = 't';
    gameTitle = L"Rocket League";
}

void Configuration::readFromPath(std::string path)
{
    std::ifstream fileReader(path);
    std::string line;

    while(std::getline(fileReader, line))
    {
        std::stringstream ss(line);
        std::string name;
        std::string setting;

        if(std::getline(ss, name, ':') && std::getline(ss, setting))
        {
            if(name == "ExitKeycode")
            {
                HKL kbl = GetKeyboardLayout(0);
                exitKey = atoi(setting.c_str());
            }
            else if(name == "ChatKey")
            {
                chatKey = setting.c_str()[0];
            }
            else if(name == "Ad")
            {
                ads.push_back(setting);
            }
            else if(name == "WaitBetweenBlocks")
            {
                sleepBetweenBlocks = atoi(setting.c_str());
            }
            else if(name == "WaitBetweenKeys")
            {
                sleepBetweenLetters = atoi(setting.c_str());
            }
            else if(name == "CharsPerBlock")
            {
                charsPerBlock = atoi(setting.c_str());
            }
            else if(name == "GameTitle")
            {
                std::wstring wSetting(setting.begin(), setting.end());
                gameTitle = wSetting;
            }
            else if(name == "SecondsBetweenAds")
            {
                secondsBetweenAds = atoi(setting.c_str());
            }
        }
    }
}
