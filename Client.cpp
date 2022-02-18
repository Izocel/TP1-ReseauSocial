#include "Client.h"

Client::Client()
{
	m_uuid = getUuid();
}

Client::Client(Serveur& srv)
{
	m_serveur = srv;
	m_serveurUuid = srv.getUuid();
	m_uuid = getUuid();
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

	std::cout << "Votre date de naissance (AAAA/MM/JJ): ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["date"] = Utilitaire::parseTimeYYYYMMDD(str);

	std::cout << "Votre courriel: ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["courriel"] = str;

	std::cout << "Votre mot de passe: ";
	getline(std::cin, str);
	std::stringstream(str) >> str;
	jsonMembre["mdp"] = str;

	str = "93/09/19";
	jsonMembre["date"] = str;

	return jsonMembre;
}

json Client::formulaireMessage(std::string uuidMembre)
{
	std::string str;
	json jsonMessage;

	return jsonMessage;
}

bool Client::creeMembre()
{	
	RequeteClient rqstClient;
	ReponseServeur rspServer;
	json membreJson;

	if (m_connecter) return false;

	try
	{
		membreJson = formulaireMembre();
	}
	catch (const std::exception&)
	{
		std::cout << "\nUne erreur est survenu !\nAsurez vous d'utilisé les charactères alphanum non-spéciaux !!!";
	}
	if (membreJson.empty()) return false;

	try
	{
		//Création et fetch requete vers le serveur
		rqstClient = requeteMembre(membreJson, "POST");
		rspServer = fetchRequete(rqstClient);


		// Si requete srv OK et uuidMembre présent set membre connecter
		if (rspServer.p_type == "ok") {
			std::string givenUuid{};
			rspServer.p_data["uuid"].get_to(givenUuid);
			if (givenUuid.empty()) return false;

			m_membreConnecter.from_json(rspServer.p_data);
			return true;
		}
	}
	catch (const std::exception&)
	{
		std::cout << "\nUne erreur est survenu !!!\nImpossible de creer votre profil...";
	}
	return false;
}

std::string Client::getUuid()
{
	if (m_uuid.empty())
		m_uuid = Utilitaire::uuidCient();
	return m_uuid;
}

RequeteClient Client::requeteMembre(json& membreData, std::string type)
{
	RequeteClient rqst;

	rqst.p_clientUuid = m_uuid;
	rqst.p_serveurUuid = m_serveurUuid;
	rqst.p_nom = "/membre";
	rqst.p_type = type;
	rqst.p_data = membreData;

	//asserts
	/*std::cout << membreData.at("nom"); == std::cout << rqst.p_data.at("nom");*/
	return rqst;
}


ReponseServeur Client::fetchRequete(RequeteClient& requeteC)
{
	ReponseServeur rsp = m_serveur.parseRequete(requeteC);

	if (rsp.p_serveurUuid == m_serveurUuid) {
		return rsp;
	}
	return ReponseServeur();
}
