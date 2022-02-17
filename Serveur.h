#pragma once
#include "UtilitaireServeur.h"

class Serveur
{
private:
	MockDatastore m_mockDS;
public:
	ReponseServeur parseRequete(RequeteClient& rqstCLient);
};

