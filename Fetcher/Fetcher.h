#ifndef F_FETCHER_H
#define F_FETCHER_H

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "FetcherConfig.h"

class Fetcher
{
public:
    Fetcher(FetcherConfigMap ConfigMap);
    std::map<std::string, std::string>& GetCurrencySymbols();
    uint GetExchangeRate(const std::string& Base,
                                            const std::string& Target,
                                            const std::string& BaseAmount);

private:
    std::map<std::string, std::string>& ParseCurrencySymbols(std::string& Buffer);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    FetcherConfig Config;
    std::map<std::string, std::string> SymbolMap;
};

#endif