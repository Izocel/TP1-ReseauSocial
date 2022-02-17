#ifndef UTILITAIRE_def
#define UTILITAIRE_def
#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#include <iostream>
#include <string>
#include <random>
#include <windows.h>
#include <sstream>
#include "Membre.h"
#include "MockDatastore.h"
#include "ReponseServeur.h"
#include "RequeteClient.h"
#include "Serveur.h"


//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

namespace Utilitaire {


	/// <summary>
	/// Génére un nombre aléatoire normaliser entre min et max
	/// </summary>
	/// <param name="min">minimum</param>
	/// <param name="max">maximum</param>
	/// <returns>Le nombre généré</returns>
	const int rndInt(int min, int max);


	/// <summary>
	/// Permet de générer un uuid de membre
	/// </summary>
	/// <param name="membre"></param>
	/// <returns></returns>
	const std::string uuidServeur();

	/// <summary>
	/// Permet de générer un uuid de membre
	/// </summary>
	/// <param name="membre"></param>
	/// <returns></returns>
	const std::string uuidMembre(std::string nom, std::string prenom, std::string dateNaissStr);


	/// <summary>
	/// Permet de générer un uuid au hasard de client
	/// </summary>
	const std::string uuidCient();
}
#endif
