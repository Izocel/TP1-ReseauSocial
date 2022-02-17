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
	int rnd = rndInt(10, 99);
	std::string str = "";
	str += nom[0] + nom[1] + nom[2];
	str += prenom[0] + prenom[1] + prenom[2];
	str += dateNaissStr;
	str += rnd;

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
