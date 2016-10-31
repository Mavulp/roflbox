#pragma once
#include <vector>
#include <chrono>
#include <time.h>

class Ad {
public:
    int charsPerBlock = 15;
    int sleepBetweenBlocks = 150;
    int sleepBetweenChars = 2;
    int secondsBetweenAds = 30;

    std::chrono::system_clock::time_point secondsSinceDisplay;
    std::vector<std::string> messages;

    Ad(){};
    Ad(int perBlock, int betweenBlocks, int betweenChars, int betweenAds,
            std::vector<std::string> msgs)
        :charsPerBlock(perBlock),
        sleepBetweenBlocks(betweenBlocks),
        sleepBetweenChars(betweenChars),
        secondsBetweenAds(betweenAds),
        messages(msgs),
        secondsSinceDisplay(std::chrono::system_clock::now()) {};
};
