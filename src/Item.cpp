#include <multichain-cpp/Item.hpp>

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

        Json::Value result = this->stream->chain->Execute(command);
        if(!result["error"].isNull())
        {
            throw std::runtime_error(result["error"]["message"].asString());
        }
    }

    Item Item::createItemObject(Stream *stream, std::string key)
    {
        return Item(stream, key);
    }
}
