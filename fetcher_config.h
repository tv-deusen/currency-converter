#include <map>

typedef std::map<std::string, std::string> FetcherConfigMap;

class FetcherConfig
{
public:
    FetcherConfig();
    FetcherConfig(FetcherConfigMap ConfigMap);
    std::string& Url();
    std::string& Key();

private:
    std::string ApiUrl;
    std::string ApiKey;
};