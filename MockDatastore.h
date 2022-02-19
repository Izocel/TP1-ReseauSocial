#pragma once
//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

class MockDatastore
{
private:
	std::map<std::string, json> m_mapMembre;
	std::map<std::string, json> m_mapMessages;

public:
	json getMembre(std::string membreUuid);
	json getMessages(std::string membreUuid);
	json putMembre(json membreData);
	json putMessage(json messageData);
};

