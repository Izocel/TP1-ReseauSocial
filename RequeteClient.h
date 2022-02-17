#pragma once

#include <iostream>
#include <string>

#include "Membre.h"
#include "Message.h"

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme


class RequeteClient
{
public:
	std::string p_nom;
	std::string p_type;
	std::string p_clientUuid;
	json p_data;
};

