
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "symbols.h"
#include "fetcher.h"

using json = nlohmann::json;

Fetcher::Fetcher(FetcherConfigMap ConfigMap)
{
    Config = FetcherConfig(ConfigMap);
    // std::cout << Config.Url() << std::endl << Config.Key() << std::endl;
    // TODO: Should probably move this out of constructor?
    //       Not sure what the best practice is for calling functions
    //       like this in constructors.
    GetCurrencySymbols();
}

std::string ApiKeyHeader(std::string Key)
{
    std::stringstream Buf;
    Buf << "@{\'access_key\'=\'";
    Buf << Key;
    Buf << "\'}";

    return Buf.str();
}

void Fetcher::ParseCurrencySymbols(std::string& Buffer)
{
    auto SymbolsJson = json::parse(Buffer).at("symbols");
    for (auto& Element : SymbolsJson.items())
    {
        auto Code = Element.value()["code"].get<std::string>();
        auto Description = Element.value()["description"].get<std::string>();
        SymbolMap[Code] = Description;
    }
}

void Fetcher::GetCurrencySymbols()
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
    ParseCurrencySymbols(ReadBuffer);
}

size_t Fetcher::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
