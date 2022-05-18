#include <iostream>
#include <sstream>
#include <stdio.h>
#include "Endpoints.h"
#include "Fetcher.h"

using json = nlohmann::json;

Fetcher::Fetcher(FetcherConfigMap ConfigMap)
{
    Config = FetcherConfig(ConfigMap);    
}

std::map<std::string, std::string>& Fetcher::ParseCurrencySymbols(std::string& Buffer)
{
    auto SymbolsJson = json::parse(Buffer).at("symbols");

    for (auto& Element : SymbolsJson.items())
    {
        auto Code = Element.value()["code"].get<std::string>();
        auto Description = Element.value()["description"].get<std::string>();
        SymbolMap[Code] = Description;
    }
    return SymbolMap;
}

std::map<std::string, std::string>& Fetcher::GetCurrencySymbols()
{
    auto SymbolsEndpoint = Config.Url() + Symbols;
    std::string ReadBuffer;
    CURL *Curl = curl_easy_init();
    if (Curl != nullptr)
    {
        // https://api.exchangerate.host
        curl_easy_setopt(Curl, CURLOPT_URL, SymbolsEndpoint.c_str());
        curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, Fetcher::WriteCallback);
        curl_easy_setopt(Curl, CURLOPT_WRITEDATA, &ReadBuffer);
        curl_easy_perform(Curl);
        curl_easy_cleanup(Curl);
    }
    return ParseCurrencySymbols(ReadBuffer);
}

uint Fetcher::GetExchangeRate(const std::string& Base,
                                      const std::string& Target,
                                      const std::string& BaseAmount)
{
    auto RateEndpoint = std::string{Config.Url() + Convert + "?" + "from=" + Base + "&to=" + Target + "&amount=" + BaseAmount};
    std::string ReadBuffer;
    CURL *Curl = curl_easy_init();
    if (Curl != nullptr)
    {
        curl_easy_setopt(Curl, CURLOPT_URL, RateEndpoint.c_str());
        curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, Fetcher::WriteCallback);
        curl_easy_setopt(Curl, CURLOPT_WRITEDATA, &ReadBuffer);
        curl_easy_perform(Curl);
        curl_easy_cleanup(Curl);
    }

    auto Result = json::parse(ReadBuffer);
    return Result["result"].get<uint>();
}

size_t Fetcher::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
