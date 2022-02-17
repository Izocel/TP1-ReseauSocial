#include "Client.h"

Client::Client()
{

}

json Client::formulaireMembre()
{	
	std::string str;
	json jsonMembre;

	std::cout << "Votre nom: ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["nom"] = str;

	std::cout << "Votre prenom: ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["prenom"] = str;

	std::cout << "Votre courriel: ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["courriel"] = str;

	std::cout << "Votre mot de passe: ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["mdp"] = str;

	return jsonMembre;
}

json Client::formulaireMessage(std::string uuidMembre)
{
	std::string str;
	std::map<std::string, std::string> map_formulaire;

	map_formulaire["clientUuid"] = m_uuid;
	map_formulaire["source"] = m_membreConnecter.getUuid();
	map_formulaire["cible"] = uuidMembre;

	std::cout << "Votre message: \n";
	getline(std::cin, str);
	std::stringstream(str) >> map_formulaire["texte"];

	// Trop long a implémenter de la bonne façon
	//time_t t = time(NULL); 
	//char* timeinfo = asctime(gmtime(&t));
	std::string timeinfo = "93/09/19";
	map_formulaire["date"] = timeinfo;

	return map_formulaire;
}

void Client::creeMembre()
{	
	RequeteClient rqstClient;
	ReponseServeur rspServer;
	json membreJson;


	if (!m_connecter) {
		try
		{
			membreJson = formulaireMembre();
		}
		catch (const std::exception&)
		{
			std::cout << "Une erreur est survenu !\nAsurez vous d'utilisé les charactères alphanum non-spéciaux !!!";
		}
	}

	if (membreJson) {
		try
		{
			rqstClient = requeteMembre(membreJson, "POST");
			rspServer = fetchRequete(rqstClient);
		}
		catch (const std::exception&)
		{

		}
	}
}

RequeteClient Client::requeteMembre(json& membreData, std::string type)
{
	RequeteClient rqst;

	rqst.m_clientUuid = m_uuid;
	rqst.m_data = membreData;
	rqst.m_nom = type + "/membre";
	return rqst;
}


ReponseServeur Client::fetchRequete(RequeteClient& requeteC)
{
	return m_serveur.parseRequete(requeteC);
}
