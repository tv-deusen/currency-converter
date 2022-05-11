#include <string>
#include "fetcher_config.h"

FetcherConfig::FetcherConfig(FetcherConfigMap Map)
{
    ApiKey = Map["KEY"];
    Url = Map["URL"];
}

std::string& FetcherConfig::GetUrl()
{
    return Url;
}

std::string& FetcherConfig::GetApiKey()
{
    return ApiKey;
}