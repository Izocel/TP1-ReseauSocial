#pragma once
//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

class MockDatastore
{
private:
	std::map<std::string, json> m_mapMembre;

public:
	json getMembre(std::string membreUuid);
	json putMembre(json membreData);
};

