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
        Json::Value InfoGet();
        void InfoDump(void);

        float balance;
        size_t blocks;
        std::string burnaddress;
        std::string chainname;
        size_t connections;
        std::string description;
        float difficulty;
        std::string edition;
        
#if 0
	"errors" : "",
	"incomingpaused" : false,
	"keypoololdest" : 1580175695,
	"keypoolsize" : 2,
	"miningpaused" : false,
	"nodeaddress" : "clarion@192.168.200.104:9741",
	"nodeversion" : 20005901,
	"offchainpaused" : false,
	"paytxfee" : 0,
	"port" : 9741,
	"protocol" : "multichain",
	"protocolversion" : 20011,
	"proxy" : "",
	"reindex" : false,
	"relayfee" : 0,
	"setupblocks" : 60,
	"testnet" : false,
	"timeoffset" : 0,
	"version" : "2.0.5",
	"walletdbversion" : 3,
	"walletversion" : 60000
#endif

      private:
        std::string host;
        uint16_t port;
        std::string rpcuser;
        std::string rpcpassword;
        static size_t write_data(void *, size_t, size_t, std::string *);
    };
}
