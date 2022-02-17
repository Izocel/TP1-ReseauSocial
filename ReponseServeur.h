#pragma once


//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

class ReponseServeur
{
public:
	std::string p_nom;
	std::string p_type{ "GET" };
	std::string p_serveurUuid;
	json p_data;
};

