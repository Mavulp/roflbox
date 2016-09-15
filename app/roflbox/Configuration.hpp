#pragma once
#include <string>
#include <Windows.h>
#include <vector>
#include "Ad.hpp"

class Configuration {
public:
    Configuration();
    Configuration(std::string path);
    ~Configuration() {};

    void readFromPath(std::string path);

    short exitKey;
    char  chatKey;
    std::string gameTitle;

    std::vector<Ad> ads;
private:
    void init();
};
