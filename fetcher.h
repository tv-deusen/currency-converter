#include <string>
#include <curl/curl.h>
#include "fetcher_config.h"

class Fetcher
{
public:
    Fetcher(const FetcherConfigMap Config);


private:
    void GetCurrencySymbols();
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    FetcherConfig Config;
    std::string ReadBuffer;

};