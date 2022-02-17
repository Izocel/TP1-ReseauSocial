#pragma once
#include "Utilitaire.h"

class Serveur
{
private:
	std::string m_uuid;
	std::string m_nom{ "AN1" };
	std::string m_region{ "Amerique du nord" };
	MockDatastore m_mockDS;
public:
	std::string getUuid();
	ReponseServeur parseRequete(RequeteClient& rqstCLient);
	ReponseServeur reponsePostMembre(RequeteClient& rqstClient);
	void sendReponse(ReponseServeur& rspServeur);
};

