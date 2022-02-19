#pragma once


//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme


/// <summary>
/// Struct ReponseServeur:
/// Représente la structure d'une réponse serveur fesant suite à une requete.
/// </summary>
struct ReponseServeur
{
	std::string p_serveurUuid;
	std::string p_clientUuid;
	std::string p_route;
	std::string p_type; //[GET,POST,PUT,DELETE]
	/// <summary>
	/// Représente le data contenue dans la réponse.
	/// </summary>
	json p_data;
};

