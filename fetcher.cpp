
#include <iostream>
#include <sstream>
#include <stdio.h>
#include "debug.h"
#include "symbols.h"
#include "fetcher.h"

Fetcher::Fetcher(FetcherConfigMap ConfigMap)
{
    Config = FetcherConfig(ConfigMap);
    GetCurrencySymbols();
}

std::string ApiKeyHeader(std::string Key)
{
    std::stringstream Buf;
    Buf << "@{\'apikey\':\'";
    Buf << Key;
    Buf << "\'}";

    return Buf.str();
}

void Fetcher::GetCurrencySymbols()
{
    struct data config;
    config.trace_ascii = 1; /* enable ascii tracing */

    std::string SymbolsEndpoint = Url.append(Symbols);
    CURL *Curl = curl_easy_init();
    if (Curl != nullptr)
    {
        curl_easy_setopt(Curl, CURLOPT_URL, Url.c_str());
        curl_easy_setopt(Curl, CURLOPT_HEADER, ApiKeyHeader(Key)); // this isnt the right option, use CURLOPT_HTTPHEADER
        curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, Fetcher::WriteCallback);
        curl_easy_setopt(Curl, CURLOPT_WRITEDATA, &ReadBuffer);
        curl_easy_setopt(Curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(Curl, CURLOPT_DEBUGDATA, &config);
        curl_easy_setopt(Curl, CURLOPT_DEBUGFUNCTION, my_trace);
        curl_easy_perform(Curl);
        curl_easy_cleanup(Curl);
    }
    std::cout << ReadBuffer << std::endl;
}

size_t Fetcher::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
