#pragma once
#include "Utilitaire.h"

class Client
{
public:
	Client();
	Client(Serveur& srv);
	json formulaireMembre();
	json formulaireMessage(std::string uuidMembre);
	bool creeMembre();
private:
	Serveur m_serveur;
	std::string m_serveurUuid;
	bool m_connecter{false};
	std::string m_version{"1.0"};
	std::string m_uuid{};
	std::string m_menu;
	Membre m_membreConnecter;

	RequeteClient requeteMembre(json& membreData, std::string type);
	ReponseServeur fetchRequete(RequeteClient& requeteC);
};

