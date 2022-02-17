#pragma once
#include "UtilitaireServeur.h"

class MockDatastore
{
private:
<<<<<<< HEAD
	std::map<std::string, json> m_mapMembre;
=======
	std::map<std::string, std::string> m_mapMembre;
>>>>>>> 8e7c447c98c4fd0ca08b6402b868569b235d6278

public:
	json getMembre(std::string membreUuid);
	json putMembre(json membreData);
};

