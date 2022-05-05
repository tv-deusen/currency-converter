#include "fetcher.h"

int main(int argc, char * argv[])
{

    std::string Url = "https://api.apilayer.com/exchangerates_data";
    // TODO: add API key as cmdline arg
    std::string Key = "";

    curl_global_init(CURL_GLOBAL_ALL);

    auto CurrencyFetcher = Fetcher(Key, Url);
}