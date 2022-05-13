#include <string>
#include <ostream>
#include "FetcherConfig.h"

// TODO: better parsing of bad characters that CURL won't like

FetcherConfig::FetcherConfig(){ }

FetcherConfig::FetcherConfig(FetcherConfigMap Map)
{
    ApiKey = Map["KEY"];
    ApiUrl = Map["URL"];
}

std::string& FetcherConfig::Url()
{
    return ApiUrl;
}

std::string& FetcherConfig::Key()
{
    return ApiKey;
}

// std::ostream& operator<<(std::ostream& strm, const FetcherConfig& config)
// {
//     strm << "Url: " << config.Url() << std::endl << "Key: " << config.Key() << std:: endl;
//     return strm;
// }