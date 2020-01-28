#include <multichain-cpp/Item.hpp>
#include <iostream>

namespace metaverse
{
    Item::Item(Stream *stream, std::string key)
    {
        this->stream = stream;
        this->key = key;

        Json::Value command;
        command["method"] = "liststreamkeyitems";
        command["params"] = Json::arrayValue;
        command["params"].append(this->stream->name);
        command["params"].append(this->key);
        command["params"].append(false);

std::cout << command << std::endl;

        Json::Value result = this->stream->chain->Execute(command);
        if(!result["error"].isNull())
        {
            std::cout << result << std::endl;
            throw std::runtime_error(result["error"]["message"].asString());
        }

        std::cout << result << std::endl;
    }

    Item Item::createItemObject(Stream *stream, std::string key)
    {
        return Item(stream, key);
    }
}
