#ifndef UTILITAIRE_def
#define UTILITAIRE_def
#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#include <iostream>
#include <string>
#include <random>
#include <windows.h>
#include <sstream>
#include <time.h>
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
	/// G�n�re un nombre al�atoire normaliser entre min et max
	/// </summary>
	/// <param name="min">minimum</param>
	/// <param name="max">maximum</param>
	/// <returns>Le nombre g�n�r�</returns>
	const int rndInt(int min, int max);


	/// <summary>
	/// Permet de g�n�rer un uuid de membre
	/// </summary>
	/// <param name="membre"></param>
	/// <returns></returns>
	const std::string uuidServeur();

	
	/// <summary>
	/// Permet de g�n�rer un uuid de membre
	/// </summary>
	/// <param name="nom">Le nom du membre</param>
	/// <param name="prenom">Le prenom du membre</param>
	/// <param name="naissanceEpoch">La date de naissance au format epoch</param>
	/// <returns></returns>
	const std::string uuidMembre(std::string&, std::string&, time_t&);


	/// <summary>
	/// Permet de g�n�rer un uuid au hasard de client
	/// </summary>
	const std::string uuidCient();


	/// <summary>
	/// Retourne lepoch selon une date au format "%Y/%m/%d".
	/// </summary>
	/// <param name="dateString">La chaine repr�sentant la date.</param>
	/// <returns>Nombre de secondes �coul�es (epoch).</returns>
	const time_t parseTimeYYYYMMDD(std::string& dateString);

	/// <summary>
	/// Retourne un string selon le format demander sur lepoch.
	/// </summary>
	/// <param name="rawtimeEpoch">Secondes �coul�es depuis l'ann�e 1900</param>
	/// <param name="format">strftime format</param>
	/// <returns>Le string au format demand�</returns>
	const std::string parseTimeT(time_t& rawtimeEpoch, const char* format);
}
#endif
