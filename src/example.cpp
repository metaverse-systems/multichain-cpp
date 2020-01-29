#include <multichain-cpp/multichain-cpp.hpp>
#include <iostream>
#include <fstream>

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

const std::vector<std::string> explode(const std::string &s, const char &c)
{
    std::string buff{""};
    std::vector<std::string> v;

    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

Json::Value parseConf(std::string filename)
{
    std::string data;
    std::ifstream file;
    std::streampos fsize, fstart = 0;

    file.open(filename);
    fstart = file.tellg();
    file.seekg(0, std::ios::end);
    fsize = file.tellg() - fstart;
    file.seekg(0, std::ios::beg);
    data.resize(fsize);
    file.read(&data[0], fsize);
    file.close();

    Json::Value results;

    for(auto line : explode(data, '\n'))
    {
        auto option = explode(line, '=');
        results[option[0]] = option[1];
    }

    return results;
}

int main(int argc, char *argv[])
{
    std::string home = std::string(getenv("HOME"));
    Json::Value credentials = parseConf(home + "/.multichain/clarion/multichain.conf");

    MultiChain clarion("localhost", 9740, credentials["rpcuser"].asString(), credentials["rpcpassword"].asString());

    std::cout << "Number of blocks: " << clarion.blocks << std::endl;

    return 0;
}
