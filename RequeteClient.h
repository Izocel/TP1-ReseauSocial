#pragma once

#include <iostream>
#include <string>

#include "Membre.h"
#include "Message.h"

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme


struct RequeteClient
{
	std::string p_serveurUuid;
	std::string p_clientUuid;
	std::string p_nom;
	std::string p_type;
	json p_data;
};

