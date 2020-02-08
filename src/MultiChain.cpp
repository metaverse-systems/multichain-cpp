#include <multichain-cpp/MultiChain.hpp>
#include <curl/curl.h>
#include <unistd.h>
#include <iostream>

namespace metaverse
{
    MultiChain::MultiChain(std::string host, uint16_t port, std::string rpcuser, std::string rpcpassword)
    {
        curl_global_init(CURL_GLOBAL_ALL);

        this->host = host;
        this->port = port;
        this->rpcuser = rpcuser;
        this->rpcpassword = rpcpassword;

        Json::Value info = this->InfoGet();
        this->balance = info["balance"].asFloat();
        this->blocks = info["blocks"].asUInt();
        this->burnaddress = info["burnaddress"].asString();
        this->chainname = info["chainname"].asString();
        this->connections = info["connections"].asUInt();
        this->description = info["description"].asString();
        this->difficulty = info["difficulty"].asFloat();
        this->edition = info["edition"].asString();
    }

    Json::Value MultiChain::Execute(Json::Value command)
    {
        CURL *curl = curl_easy_init();
        if(!curl)
        {
            throw std::runtime_error("Couldn't initialize libcurl.");
        }

        Json::StreamWriterBuilder builder;
        const std::string post = Json::writeString(builder, command);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post.size());
        curl_easy_setopt(curl, CURLOPT_URL, this->host.c_str());
        curl_easy_setopt(curl, CURLOPT_PORT, this->port);
        curl_easy_setopt(curl, CURLOPT_USERNAME, this->rpcuser.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, this->rpcpassword.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, MultiChain::write_data);

        std::string rpc_result;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rpc_result);

        struct curl_slist *chunk = curl_slist_append(NULL, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(chunk);

        curl_easy_reset(curl);
        curl_easy_cleanup(curl);

        if(res)
        {
            std::string message(curl_easy_strerror(res));
            throw std::runtime_error(message);
        }

        Json::Value result;
        Json::CharReaderBuilder readerBuilder;
        Json::CharReader *reader = readerBuilder.newCharReader();
        std::string readerErrors;

        bool parsingSuccessful = reader->parse(rpc_result.c_str(), rpc_result.c_str() + rpc_result.size(), &result, &readerErrors);
        delete reader;

        if(!parsingSuccessful)
        {
            std::string err = "Couldn't parse response: " + rpc_result + "\n";
            err += readerErrors;
            throw std::runtime_error(err);
        }

        return result;
    }

    size_t MultiChain::write_data(void *ptr, size_t size, size_t nmemb, std::string *result)
    {
        auto bytes = size * nmemb;
        result->append((char *)ptr, bytes);

        return bytes;
    }

    Stream MultiChain::StreamGet(std::string name)
    {
        return Stream::createStreamObject(this, name);
    }

    Stream MultiChain::StreamCreate(std::string name)
    {
        Json::Value command;
        command["method"] = "create";
        command["params"] = Json::arrayValue;
        command["params"].append("stream");
        command["params"].append(name);
        command["params"].append(true);

        Json::Value result = this->Execute(command);
        if(!result["error"].isNull())
        {
            throw std::runtime_error(result["error"]["message"].asString());
        }

        return this->StreamGet(name);
    }

    Json::Value MultiChain::InfoGet()
    {
        Json::Value command;
        command["method"] = "getinfo";

        Json::Value result = this->Execute(command);
        if(!result["error"].isNull())
        {
            throw std::runtime_error(result["error"]["message"].asString());
        }

        return result["result"];
    }

    void MultiChain::InfoDump()
    {
        std::cout << "Balance: " << this->balance << std::endl;
        std::cout << "Blocks: " << this->blocks << std::endl;
        std::cout << "Burn address: " << this->burnaddress << std::endl;
        std::cout << "Chain name: " << this->chainname << std::endl;
        std::cout << "Number of connections: " << this->connections << std::endl;
        std::cout << "Description: " << this->description << std::endl;
        std::cout << "Difficulty: " << this->difficulty << std::endl;
        std::cout << "Edition: " << this->edition << std::endl;
    }
}
