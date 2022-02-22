#ifndef UTILITAIRE_def
#define UTILITAIRE_def
#pragma comment(lib, "rpcrt4.lib")  // UuidCreate - Minimum supported OS Win 2000
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <random>
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


/// <summary>
/// Namespace Utilitaire:
/// Pose des fonctions utiles pour un client ou un serveur.
// Celle-ci pourraient être implémentées de façcon sélective selon le coté (serveur ou client).
/// </summary>
namespace Utilitaire {


	/// <summary>
	/// Génére un nombre aléatoire normaliser entre min et max
	/// </summary>
	/// <param name="min">minimum</param>
	/// <param name="max">maximum</param>
	/// <returns>Le nombre généré</returns>
	const int rndInt(int min, int max);


	/// <summary>
	/// Permet de générer un uuid HEXA de serveur au hasard
	/// </summary>
	/// <returns>Uuid</returns>
	const std::string uuidServeur();

	/// <summary>
	/// Permet de générer un uuid HEXA de client au hasard
	/// </summary>
	/// <returns>Uuid</returns>
	const std::string uuidCient();
	
	/// <summary>
	/// Permet de générer un uuid 3a3aDATE2d de membre 
	/// </summary>
	/// <param name="nom">Le nom du membre</param>
	/// <param name="prenom">Le prenom du membre</param>
	/// <param name="naissanceEpoch">La date de naissance au format epoch</param>
	/// <returns>Uuid</returns>
	/// FIXME: NON-UNIQUE
	const std::string uuidMembre(std::string& nom, std::string& prenom, time_t& naissanceEpoch);

	/// <summary>
	/// Retourne lepoch selon une date au format "%Y/%m/%d".
	/// </summary>
	/// <param name="dateString">La chaine représentant la date.</param>
	/// <returns>Nombre de secondes écoulées (epoch).</returns>
	const time_t parseTimeYYYYMMDD(std::string& dateString);

	/// <summary>
	/// Retourne un string selon le format demander sur lepoch.
	/// </summary>
	/// <param name="rawtimeEpoch">Secondes écoulées depuis l'année 1900</param>
	/// <param name="format">strftime format</param>
	/// <returns>Le string au format demandé</returns>
	const std::string parseTimeT(time_t& rawtimeEpoch, const char* format);

	const time_t getUtcNow();

	
	/// <summary>
	/// Comparaison des uuid pour résoudre la construction 
	/// d'un messageId composé des deux uuid (optimization niveau recherche et stockage)
	/// </summary>
	/// <param name="s1">Cible/Source UUID</param>
	/// <param name="s2">Cible/Source UUID</param>
	/// <returns>messageUuid</returns>
	const std::string findUniqueMsgId(const std::string& s1, const std::string& s2);
	std::vector<std::string> splitStr(std::string& needle, std::string haystack);
	std::vector<std::string> splitStrV2(const char* needle, const std::string& haystack);
}
#endif
