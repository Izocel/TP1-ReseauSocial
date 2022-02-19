#pragma once
#include "Utilitaire.h"

class Serveur
{
private:
	std::string m_uuid{getUuid()};
	std::string m_nom{ "AN1" };
	std::string m_region{ "Amerique du nord" };
	MockDatastore m_mockDS;
public:
	Serveur();
	std::string getUuid();
	ReponseServeur parseRequete(RequeteClient& rqstCLient);
	ReponseServeur reponsePostMembre(RequeteClient& rqstClient);
	ReponseServeur reponsePostMessage(RequeteClient& rqstClient);
	void sendReponse(ReponseServeur& rspServeur);
};

