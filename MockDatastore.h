#pragma once
#include "UtilitaireServeur.h"

class MockDatastore
{
private:
	std::map<std::string, std::string> m_mapMembre;

public:
	json getMembre(std::string membreUuid);
	json putMembre(json membreData);
};

