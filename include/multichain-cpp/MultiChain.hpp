#pragma once
#include <string>
#include <json/json.h>

#include "multichain-cpp.hpp"

namespace metaverse
{
    class Stream;

    class MultiChain
    {
      public:
        MultiChain(std::string, uint16_t, std::string, std::string);
        Json::Value Execute(Json::Value command);
        Stream StreamGet(std::string name);
        Stream StreamCreate(std::string name);
      private:
        std::string host;
        uint16_t port;
        std::string rpcuser;
        std::string rpcpassword;
        static size_t write_data(void *, size_t, size_t, std::string *);
    };
}
