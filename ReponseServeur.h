#pragma once


//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

class ReponseServeur
{
	std::string m_nom;
	std::string m_type{ "GET" };
	std::string m_clientUuid;
	json m_data;
};

