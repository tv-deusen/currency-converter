#include <map>

typedef std::map<std::string, std::string> FetcherConfigMap;

class FetcherConfig
{
public:
    FetcherConfig(FetcherConfigMap ConfigMap);
    std::string& GetUrl();
    std::string GetApiKey();

private:
    std::string *Url;
    std::string *ApiKey;
};