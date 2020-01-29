#pragma once
#include <string>
#include <json/json.h>

#include "multichain-cpp.hpp"

namespace metaverse
{
    class MultiChain;
    class Item;

    class Stream 
    {
      public:
        std::string name;
        static Stream createStreamObject(MultiChain *chain, std::string name);
        bool Save();
        Item ItemPublish(std::string key, std::string data);
        Item ItemGet(std::string key);
        std::vector<std::string> KeysGet(std::vector<std::string> keys);
        std::vector<std::string> KeysGet();
      private:
        friend class Item;
        Stream(MultiChain *chain, std::string name);
        MultiChain *chain = nullptr;
        std::vector<std::string> keys_get(Json::Value keys);
    };
}
