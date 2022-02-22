#include "Client.h"
#include  <stdio.h>
#include  <signal.h>
#include  <stdlib.h>

Client::Client()
{
	m_uuid = getUuid();
	run();
}

Client::Client(Serveur& srv)
{
	m_serveur = srv;
	m_serveurUuid = srv.getUuid();
	m_uuid = getUuid();
	run();
}



int Client::run()
{
	std::string uInput{};
	bool choixEchec = false;
	bool ajoutRelationEchec = false;
	bool envoiMsgEchec = false;

	int iTentative = 0;

	static bool boucle = true;
	while (boucle) {

		if (! m_membreConnecter) {
			vueConnection(iTentative);
			std::cin >> uInput;

			if (uInput == "0") {
				std::string email;
				std::string mdp;

				std::cout << "\nEntrez vos informations de connection";
				std::cout << "\nCourriel: ";
				std::cin >> email;
				std::cout << "Mot de passe: ";
				std::cin >> mdp;

				//Get serveur membre


				// If rsp 'OK' m_connecter = true;
				if (! m_connecter) {
					iTentative++;
				}
			}

			else if (uInput == "1") {
				creeMembre();
			}
		}

		else {
			iTentative = 0;
			vueAcceuil();
			std::cin >> uInput;
			
			bool boucleSecondaires = true;

			if (uInput == "0") { // Ajout Relation
				while (boucleSecondaires) {

					std::cin >> uInput;
					if (uInput == "exit") boucleSecondaires = false;
				}
				
			}

			else if (uInput == "1") { // Retirer Relation
				while (boucleSecondaires) {
				
					std::cin >> uInput;
					if (uInput == "exit") boucleSecondaires = false;
				}
			}

			else if (uInput == "2") { // Envoyer Message

				bool messagesTrouver = false;
				std::string uuidRelation;

				while (boucleSecondaires) {

					const ReponseServeur rspSrvRelation;
					std::array<std::string, 0> relationUuidArr;

					vueConversation(rspSrvRelation);
					std::cin >> uInput;


					/**
					  stringstream geek(s);
 
						// The object has the value 12345 and stream
						// it to the integer x
						int x = 0;
						geek >> x;
					*/

					// Utilise relationUuidArr[uInput] == uuidRelation
					// messageTrouver = Get the conversation message from srv 


					if (uInput == "exit" || messagesTrouver) {
						boucleSecondaires = false;
					}
				}


				while (messagesTrouver) {
					vueMessage(uuidRelation);
					std::cin >> uInput;

					// messageTrouver = POST the message to the srv

					if (uInput == "exit" ) messagesTrouver = false;
				}
			}
			
			// Fin boucles secondaires
		}
		// Fin boucle primaire
		if (uInput == "exit") boucle = false;
	}
	std::cout << "\n\n" + MESSAGEAUREVOIR;
	return 0;
}

void Client::vueMembreConnecter() {
	std::string ligneIdentifiant = SKIPLINE;

	std::string nomAfficherMembre = "Connecter en tant que: " +
		m_membreConnecter.getPrenom() + " " + m_membreConnecter.getNom()[0] + ".";

	int charNomLen = nomAfficherMembre.size();
	ligneIdentifiant.replace(1, charNomLen, nomAfficherMembre);

	std::cout << SKIPLINE + ligneIdentifiant;
}

void Client::vueMessage(std::string& uuidRelation) {
	std::cout << CONVERSATIONHEADER;
	vueMembreConnecter();
	std::cout << FOOTER;
	std::cout << "\nEnvoyer->";
}

void Client::vueConversation(const ReponseServeur& rspSrvConversation) {
	std::cout << CONVERSATIONHEADER;
	vueMembreConnecter();
		
	// Parse rspSrvConversation -> wathc if empty !@!cout

	std::cout << FOOTER;
	std::cout << QUESTIONMENU;
}

void Client::vueAcceuil() {
	std::cout << MENUACCEUILHEADER;
	vueMembreConnecter();
	std::cout << FOOTER;
	std::cout << QUESTIONMENU;
}

void Client::vueConnection(int& iTentative) {
	std::cout << MENUCONNECTION;
	if (iTentative > 0)
		std::cout << "\nImpossible de vous connecter!!!";
	std::cout << QUESTIONMENU;
}

json Client::formulaireMembre()
{	
	std::string str;
	json jsonMembre;
	bool estValide = true;

	std::cout << "\nVotre nom: ";
	std::cin >> str;
	std::stringstream(str) >> str;
	jsonMembre["nom"] = str;
	str.size() < 3 ? estValide = false : NULL;

	std::cout << "Votre prenom: ";
	std::cin >> str;
	std::stringstream(str) >> str;
	jsonMembre["prenom"] = str;
	str.size() < 3 ? estValide = false : NULL;

	std::cout << "Votre date de naissance (AAAA/MM/JJ): ";
	std::cin >> str;
	std::stringstream(str) >> str;
	jsonMembre["date"] = Utilitaire::parseTimeYYYYMMDD(str);
	str.size() < 8 ? estValide = false : NULL;

	std::cout << "Votre courriel: ";
	std::cin >> str;
	std::stringstream(str) >> str;
	jsonMembre["courriel"] = str;
	str.size() < 1 ? estValide = false : NULL;

	std::cout << "Votre mot de passe: ";
	std::cin >> str;
	std::stringstream(str) >> str;
	jsonMembre["mdp"] = str;
	str.size() < 1 ? estValide = false : NULL;

	if (estValide)
		return jsonMembre;

	throw std::exception();
}

bool Client::creeMembre()
{	
	RequeteClient rqstClient;
	ReponseServeur rspServer;
	json membreJson;

	if (m_connecter) return false;

	// Cr�ation json du membre
	try
	{
		membreJson = formulaireMembre();
	}
	catch (const std::exception&)
	{
		std::string str = "\nUne erreur est survenu !\nAsurez vous de respecter les formats demander!!!";
		std::cout << str;
	}
	if (membreJson.empty()) return false;


	// request-response du membre
	try
	{
		//Cr�ation et fetch requete vers le serveur
		rqstClient = requete("/membre", membreJson, "POST");
		rspServer = fetchRequete(rqstClient);


		// Si requete serveur OK, uuidMembre pr�sent et si membre connecter
		if (rspServer.p_type == "ok") {
			std::string givenUuid{};
			rspServer.p_data["uuid"].get_to(givenUuid);
			if (givenUuid.empty()) return false;

			m_membreConnecter.from_json(rspServer.p_data);
			m_connecter = true;
			return true;
		}
	}
	catch (const std::exception&)
	{
		std::cout << "\nUne erreur est survenu !!!\nImpossible de creer votre profil...";
	}
	return false;
}


json Client::formulaireMessage(std::string& uuidCible, std::string& texte)
{
	if (m_connecter) return false;

	if (texte.empty() || texte.size() > 250) throw std::exception();

	json jsonMessage;

	jsonMessage["source"] = m_membreConnecter.getUuid();
	jsonMessage["cible"] = uuidCible;
	jsonMessage["texte"] = texte;
	jsonMessage["date"] = time(0);

	return jsonMessage;
}


bool Client::envoyerMessage(std::string& cibleUuid, std::string& texte)
{
	if (m_connecter) return false;

	RequeteClient rqstClient;
	ReponseServeur rspServer;
	json messageJson;

	// Creation json du message
	messageJson = formulaireMessage(cibleUuid, texte);
	if (messageJson.empty()) return false;

	// request-response du message
	try
	{
		//Cr�ation et fetch requete vers le serveur
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
