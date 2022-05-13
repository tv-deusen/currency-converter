#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "FetcherConfig.h"

class Fetcher
{
public:
    Fetcher(FetcherConfigMap ConfigMap);

private:
    bool ParseCurrencySymbols(std::string& Buffer);
    void GetCurrencySymbols();
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    FetcherConfig Config;
    std::map<std::string, std::string> SymbolMap;
};