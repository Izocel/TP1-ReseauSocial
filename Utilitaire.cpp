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

const std::string Utilitaire::uuidMembre(std::string& nom, std::string& prenom, time_t& naissanceEpoch)
{
	using namespace Utilitaire;

	std::stringstream ss;
	int rnd = rndInt(10, 99);
	ss << rnd;
	
	std::string str = "";
	str += nom.substr(0, 3);
	str += prenom.substr(0, 3);
	str += parseTimeT(naissanceEpoch, "%Y%m%d");
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

const time_t Utilitaire::parseTimeYYYYMMDD(std::string& dateString)
{
	struct tm timeinfo{};
	if (dateString.size() < 10) throw;

	//Année
	std::string str{ dateString.substr(0,4) };
	int year = stoi(str) - 1900;
	if (year < 0) throw;
	timeinfo.tm_year = year;


	//Mois
	str = dateString.substr(5, 2);
	int month = stoi(str) - 1;
	if (month < 0 || month > 11) throw;
	timeinfo.tm_mon = month;

	//Jour
	str = dateString.substr(8, 2);
	int day = stoi(str);
	if (day < 1 || day > 31) throw;
	timeinfo.tm_mday = day;


	//Epoch
	return mktime(&timeinfo);
}


const std::string Utilitaire::parseTimeT(time_t& rawtimeEpoch, const char* format)
{
	tm timeS;
	char buffer[80];
	abs(rawtimeEpoch);
	
	// tm struct
	gmtime_s(&timeS, &rawtimeEpoch);

	// Écriture buffer
	strftime(buffer, 80, format, &timeS);
	return buffer;
}
