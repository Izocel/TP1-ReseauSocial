#pragma once


//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme


/// <summary>
/// Struct ReponseServeur:
/// Repr�sente la structure d'une r�ponse serveur fesant suite � une requete.
/// </summary>
struct ReponseServeur
{
	std::string p_serveurUuid;
	std::string p_clientUuid;
	std::string p_route;
	std::string p_type; //[GET,POST,PUT,DELETE]
	/// <summary>
	/// Repr�sente le data contenue dans la r�ponse.
	/// </summary>
	json p_data;
};

