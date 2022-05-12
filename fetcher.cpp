
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <nlohmann/json.hpp>
#include "debug.h"
#include "symbols.h"
#include "fetcher.h"

using json = nlohmann::json;

Fetcher::Fetcher(FetcherConfigMap ConfigMap)
{
    Config = FetcherConfig(ConfigMap);
    // std::cout << Config.Url() << std::endl << Config.Key() << std::endl;
    // Should probably move this out of constructor
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

void Fetcher::GetCurrencySymbols()
{
    auto SymbolsEndpoint = Config.Url() + Symbols;

    CURL *Curl = curl_easy_init();
    if (Curl != nullptr)
    {
        // https://api.exchangerate.host
        curl_easy_setopt(Curl, CURLOPT_URL, SymbolsEndpoint.c_str());
        
        curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, Fetcher::WriteCallback);
        curl_easy_setopt(Curl, CURLOPT_WRITEDATA, &ReadBuffer);

        // struct data config;
        // config.trace_ascii = 1; /* enable ascii tracing */       
        // curl_easy_setopt(Curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(Curl, CURLOPT_DEBUGDATA, &config);
        // curl_easy_setopt(Curl, CURLOPT_DEBUGFUNCTION, my_trace);
        
        curl_easy_perform(Curl);
        curl_easy_cleanup(Curl);
    }

    json::parser_callback_t JsonParseCallback = [](int depth, json::parse_event_t event, json & parsed)
    {
        if (event == json::parse_event_t::key && parsed != json("symbols"))
        {
            return false;
        }
        else
        {
            return true;
        }
    };

    // auto FullResponse = json::parse(ReadBuffer);
    // std::cout << std::setw(4) << FullResponse << std::endl;

    auto Response = json::parse(ReadBuffer, JsonParseCallback);
    if (!Response.is_discarded())
    {
        std::cout << Response << std::endl;
    }
    
}

size_t Fetcher::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
