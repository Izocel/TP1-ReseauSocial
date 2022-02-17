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
	std::string m_nom;
	std::string m_type;
	std::string m_clientUuid;
	json m_data;
};

