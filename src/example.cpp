#include <multichain-cpp/multichain-cpp.hpp>
#include <iostream>

using namespace metaverse;

std::string bin2hex(const std::string& input)
{
    std::string res;
    const char hex[] = "0123456789ABCDEF";
    for(auto sc : input)
    {
        unsigned char c = static_cast<unsigned char>(sc);
        res += hex[c >> 4];
        res += hex[c & 0xf];
    }

    return res;
}

int main(int argc, char *argv[])
{
    MultiChain test("localhost", 9740, "multichainrpc", "CjuusA3dwCPjWQmTiWCFdRvnubCnrpiJEcUZzRTpwL1r");

    Json::Value command;
    command["method"] = "liststreams";
    command["params"] = Json::arrayValue;

//    Json::Value result = test.Execute(command);
//    std::cout << result << std::endl;

    Stream stream = test.StreamGet("Name stream");
    std::cout << stream.name << std::endl;

    Item i = stream.ItemGet("1");
    return 0;
}
