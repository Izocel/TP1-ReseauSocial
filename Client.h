#pragma once
#include "Utilitaire.h"

class Client
{
public:
	Client();
	Client(Serveur& srv);
	bool creeMembre();
	json formulaireMembre();
	bool envoyerMessage(std::string& cibleUuid);
	json formulaireMessage(std::string& cibleUuid);
	std::string getUuid();
private:
	Serveur m_serveur;
	std::string m_serveurUuid;
	bool m_connecter{false};
	std::string m_version{"1.0"};
	std::string m_uuid{getUuid()};
	std::string m_menu;
	std::string m_conversation;
	Membre m_membreConnecter;

	RequeteClient requete(std::string nomRoute, json& data, std::string type);
	ReponseServeur fetchRequete(RequeteClient& requeteC);
};

