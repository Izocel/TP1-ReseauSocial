#pragma once
#include "ReponseServeur.h"
#include "RequeteClient.h"
class Serveur
{

public:
	ReponseServeur parseRequete(RequeteClient& rqstCLient);
};

