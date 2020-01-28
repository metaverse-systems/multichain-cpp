#pragma once
#include <string>
#include <json/json.h>

#include "multichain-cpp.hpp"

namespace metaverse
{
    class MultiChain;
    class Stream;

    class Item 
    {
      public:
        std::string key;
        static Item createItemObject(Stream *stream, std::string key);
        bool Save();
      private:
        Item(Stream *stream, std::string key);
        Stream *stream = nullptr;
    };
}
