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

	return jsonMembre;
}

bool Client::creeMembre()
{	
	RequeteClient rqstClient;
	ReponseServeur rspServer;
	json membreJson;

	if (m_connecter) return false;

	// Création json du membre
	try
	{
		membreJson = formulaireMembre();
	}
	catch (const std::exception&)
	{
		std::string str = "\nUne erreur est survenu !\nAsurez vous de respecter les formats demandés!!!";
		std::cout << str;
	}
	if (membreJson.empty()) return false;

	// request-response du membre
	try
	{
		//Création et fetch requete vers le serveur
		rqstClient = requete("/membre", membreJson, "POST");
		rspServer = fetchRequete(rqstClient);


		// Si requete serveur OK, uuidMembre présent et si membre connecter
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


json Client::formulaireMessage(std::string& uuidCible)
{
	if (m_connecter) return false;

	std::string texte;
	std::cout << "\nEntrer votre message (250) Laisser vide pour quitter...\n -> ";
	std::cin >> texte;

	if (texte.empty() || texte.size() == 0) throw std::exception();

	json jsonMessage;

	std::string uuidSource{ m_membreConnecter.getUuid() };
	jsonMessage["messageID"] = Utilitaire::findUniqueMsgId(uuidSource, uuidCible);
	jsonMessage["texte"] = texte;
	jsonMessage["date"] = time(0);

	return jsonMessage;
}




bool Client::envoyerMessage(std::string& cibleUuid)
{
	if (m_connecter) return false;

	RequeteClient rqstClient;
	ReponseServeur rspServer;
	json messageJson;

	// Creation json du message
	messageJson = formulaireMessage(cibleUuid);
	if (messageJson.empty()) return false;

	// request-response du message
	try
	{
		//Création et fetch requete vers le serveur
		rqstClient = requete("/message", messageJson, "POST");
		rspServer = fetchRequete(rqstClient);

		if (rspServer.p_type == "ok") return true;
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

RequeteClient Client::requete(std::string nomRoute, json& data, std::string type)
{
	RequeteClient rqst;

	rqst.p_clientUuid = m_uuid;
	rqst.p_serveurUuid = m_serveurUuid;
	rqst.p_route = nomRoute;
	rqst.p_type = type;
	rqst.p_data = data;

	//asserts
	//data.at("champX"); == rqst.p_data.at("champX");
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
