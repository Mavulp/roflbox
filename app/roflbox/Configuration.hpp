#pragma once
#include <string>
#include <Windows.h>
#include <vector>

class Configuration {
public:
    Configuration();
    Configuration(std::string path);
    ~Configuration() {};

    void readFromPath(std::string path);

    int charsPerBlock;
    int sleepBetweenBlocks;
    int sleepBetweenLetters;
    int secondsBetweenAds;
    short exitKey;
    char  chatKey;
    std::wstring gameTitle;
    std::vector<std::string> ads;
private:
    void init();
};