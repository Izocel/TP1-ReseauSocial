#pragma once
#include "UtilitaireClient.h"

class Client
{
public:
	Client();
	json formulaireMembre();
	json formulaireMessage(std::string uuidMembre);
	void creeMembre();
private:
	Serveur m_serveur;
	bool m_connecter{false};
	std::string m_version;
	std::string m_uuid;
	std::string m_menu;
	Membre m_membreConnecter;
	std::chrono::time_point<std::chrono::system_clock> 
		m_clock{ std::chrono::system_clock::now() };

	RequeteClient requeteMembre(json& membreData, std::string type);
	ReponseServeur fetchRequete(RequeteClient& requeteC);
};

