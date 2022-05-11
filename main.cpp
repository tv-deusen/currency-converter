#include <iostream>
#include <fstream>
#include <sstream>
#include "fetcher.h"


FetcherConfigMap ParseConfig(std::ifstream& Stream)
{
    FetcherConfigMap Config;
    std::string Line;

    while (std::getline(Stream, Line))
    {
        std::istringstream SLine {Line};
        std::string Key;
        std::string Value;
        if (std::getline(SLine, Key, '=') &&
            std::getline(SLine, Value))
        {
            Config[Key] = Value;
        }
    }

    return Config;
}

int main(int argc, char * argv[])
{
    std::string ConfigFName {argv[1]};
    std::ifstream Stream {ConfigFName};
    if (!Stream.is_open())
    {
        std::cout << "Unable to open config " << ConfigFName << std::endl;
        return 1;
    }

    auto Config = ParseConfig(Stream);
    curl_global_init(CURL_GLOBAL_ALL);
    auto CurrencyFetcher = Fetcher(Config);
}