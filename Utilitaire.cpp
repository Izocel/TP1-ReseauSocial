#include "Utilitaire.h"

/// <summary>
/// Instances pour la génération de nombre aléatoire
/// </summary>
std::random_device rd;
std::mt19937 RNG(rd());

const int Utilitaire::rndInt(int min, int max)
{
	// dist sert à normaliser le nombre généré entre min et max
	std::uniform_int_distribution<> dist(min, max);
	return dist(RNG);
}
const std::string Utilitaire::uuidServeur()
{
	UUID uuid;
	UuidCreate(&uuid);
	char* str = nullptr;
	UuidToStringA(&uuid, (RPC_CSTR*)&str);
	return str;
}

const std::string Utilitaire::uuidMembre(std::string nom, std::string prenom, std::string dateNaissStr)
{
	std::stringstream ss;
	int rnd = rndInt(10, 99);
	ss << rnd;
	
	std::string str = "";
	str += nom.substr(0, 3);
	str += prenom.substr(0, 3);
	str += dateNaissStr;
	str += ss.str();
	return str;
}

const std::string Utilitaire::uuidCient()
{
	UUID uuid;
	UuidCreate(&uuid);
	char* str = nullptr;
	UuidToStringA(&uuid, (RPC_CSTR*)&str);
	return str;
}
