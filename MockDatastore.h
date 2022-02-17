#pragma once
#include "UtilitaireServeur.h"

class MockDatastore
{
private:
	std::map<std::string, json> m_mapMembre;

public:
	json getMembre(std::string membreUuid);
	json putMembre(json membreData);
};

