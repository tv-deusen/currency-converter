#include <string>
#include <curl/curl.h>

class Fetcher
{
public:
    Fetcher(std::string ApiKey, std::string ApiUrl);


private:
    void GetSymbols();
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    std::string Key;
    std::string Url;
    std::string ReadBuffer;

};