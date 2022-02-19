#pragma once
#include <iostream>
#include <string>

#include "Membre.h"
#include "Message.h"

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

/// <summary>
/// Struct RequeteClient:
/// Repr�sente la structure d'une requete client.
/// </summary>
struct RequeteClient
{
	std::string p_serveurUuid;
	std::string p_clientUuid;
	std::string p_route;
	std::string p_type;  //[GET,POST,PUT,DELETE]
	/// <summary>
	/// Repr�sente le data contenue dans la requete.
	/// </summary>
	json p_data;
};

