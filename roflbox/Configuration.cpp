#include "Configuration.hpp"
#include <fstream>
#include <cpptoml.h>

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
    // Set default Values
    exitKey = 121;
    chatKey = 't';
    gameTitle = "Rocket League";
}

void Configuration::readFromPath(std::string path)
{
    // If the config file does not exist, create it
    std::ofstream file(path, std::ios::app);
    if(!file)
        file << "\n";
    file.close();

    bool validConfig = true;

    // Parse TOML
    auto config = cpptoml::parse_file("config.toml");
    auto global = config->get_table("Global");

    // Global Settings
    if(global)
    {
        auto exitKey = global->get_as<int64_t>("ExitKeyCode");
        auto chatKey = global->get_as<std::string>("ChatKey");
        auto title   = global->get_as<std::string>("GameTitle");

        if(exitKey)
            this->exitKey = *exitKey;
        if(chatKey)
            this->chatKey = chatKey->c_str()[0];
        if(title)
            this->gameTitle = *title;

        if(!(exitKey && chatKey && title))
            validConfig = false;

    }
    auto ads = config->get_table_array("Ad");

    // Settings specific to each Ad
    if(ads)
    {
        for(const auto& ad : *ads)
        {
            std::vector<std::string> messages;

            auto charsPerBlock      = ad->get_as<int64_t>("CharsPerBlock");
            auto sleepBetweenBlocks = ad->get_as<int64_t>("SleepBetweenBlocks");
            auto sleepBetweenChars  = ad->get_as<int64_t>("SleepBetweenChars");
            auto secondsBetweenAds  = ad->get_as<int64_t>("SecondsBetweenAds");

            auto msgs = ad->get_array_of<std::string>("Messages");

            for(const auto& msg : *msgs)
                messages.push_back(msg);

            if(charsPerBlock && sleepBetweenBlocks && sleepBetweenChars && secondsBetweenAds
                    && !messages.empty())
            {
                Ad a = Ad(*charsPerBlock, *sleepBetweenBlocks, *sleepBetweenChars,
                        *secondsBetweenAds, messages);

                this->ads.push_back(a);
            }
            else
                validConfig = false;
        }
    }
    // If the config file is incorrect 
    // overwrite it with defaults or values that could be read
    if(!(global && validConfig))
    {

        std::shared_ptr<cpptoml::table> config = cpptoml::make_table();

        auto global = cpptoml::make_table();
        global->insert("ExitKeyCode", (int64_t)exitKey);
        global->insert("ChatKey", std::string(1, chatKey));
        global->insert("GameTitle", std::string(gameTitle.begin(), gameTitle.end()));

        config->insert("Global", global);

        auto adsTable = cpptoml::make_table_array();

        for(auto &ad : this->ads)
        {
            auto adTable = cpptoml::make_table();
            adTable->insert("CharsPerBlock", (int64_t)ad.charsPerBlock);
            adTable->insert("SleepBetweenBlocks", (int64_t)ad.sleepBetweenBlocks);
            adTable->insert("SleepBetweenChars", (int64_t)ad.sleepBetweenChars);
            adTable->insert("SecondsBetweenAds", (int64_t)ad.secondsBetweenAds);

            auto msgArray = cpptoml::make_array();
            for(auto &msg : ad.messages){
                msgArray->push_back(msg);
            }
            adTable->insert("Messages", msgArray);

            adsTable->push_back(adTable);
        }
        config->insert("Ad", adsTable);

        file.open(path);
        file << (*config);
        file.close();
    }
}
