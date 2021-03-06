#pragma once
#include "Utilitaire.h"


/// <summary>
/// Class Serveur:
/// Classe repr?sentant l'application cot? serveur.
/// Regroupe toutes les actions qu'un serveur pourrait effectuer avec pour le client.
/// Doit impl?menter des m?thodes pour formuler, envoyer et recevoir des donn?es client/serveur.
/// 
/// "Workflow" des donn?es entre client et serveur:
///   (Action->Formulaire->Requete)//([Requete]->Action->Formulaire->Reponse)
/// 
/// 1- D?terminer l'action ? effectuer.
/// 2- Acqu?rir les donn?es ? envoy?/recevoir.
/// 3- Formater au besoin les instances ou le format natif des donn?es en json/objet/natif.
/// 4- Traiter les donn?es avant de les appliquer selon l'action ou la requete.
/// 5- Appliquer l'action: [Modification/Application/Acquisition]->(Requete/Reponse)
/// 
/// ************
/// --Pour d?monstration le serveur est inject? directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un ?couteur/?mmetteur d'API pour les m?thodes
/// --fetchRequete, sendResponse, parseRequete, parseResponse
/// 
/// -- Pour l'instant seulement le client pour faire des requete vers le serveur...
/// ************
/// </summary>

class Serveur
{
private:
	std::string m_uuid{getUuid()};
	std::string m_nom{ "AN1" };
	std::string m_region{ "Amerique du nord" };

	/// <summary>
	/// Repr?sente l'access ? une couche LGBD fictive du serveur.
	/// </summary>
	MockDatastore m_mockDS;
public:
	Serveur();

	/// <summary>
	/// Pert met de g?n?rer un uuid de serveur au hasard.
	/// </summary>
	/// <return>uuid HEXA</return>
	std::string getUuid();

	const std::string genererMembreUuid(const RequeteClient& rqstPostMembre);

	const std::string genererMessageID(const RequeteClient& rqstPostMessage);

	std::vector<std::string> getRouteAttributes(std::string& route);

	/// <summary>
	/// D?termine la r?ponse pour la route /membre avec la m?thode POST
	/// </summary>
	/// <param name="rqstClient">L'objet de requete</param>
	/// <returns>La r?ponse du serveur avec les donn?es inser?es</returns>
	ReponseServeur reponsePostMembre(RequeteClient& rqstClient);

	/// <summary>
	/// D?termine la r?ponse pour la route /message avec la m?thode POST
	/// </summary>
	/// <param name="rqstClient">L'objet de requete</param>
	/// <returns>La r?ponse du serveur avec les donn?es inser?es</returns>
	ReponseServeur reponsePostMessage(RequeteClient& rqstClient);

	/// <summary>
	/// D?termine la r?ponse pour la route /relation avec la m?thode POST
	/// </summary>
	/// <param name="rqstClient">L'objet de requete</param>
	/// <returns>La r?ponse du serveur avec les donn?es inser?es</returns>
	ReponseServeur reponsePostRelation(RequeteClient& rqstClient);

	ReponseServeur reponseGetMembre(RequeteClient& rqstClient);

	ReponseServeur reponseGetMessage(RequeteClient& rqstClient);

	ReponseServeur reponseGetConversation(RequeteClient& rqstClient);

	ReponseServeur reponseGetRelation(RequeteClient& rqstClient);

	/// <summary>
	/// Permet d'analyser une requete client et d'ainsi r?pondre ? la requete.
	/// </summary>
	/// <param name="rqstCLient">L'objet de requete</param>
	/// <returns></returns>
	ReponseServeur parseRequete(RequeteClient& rqstCLient);

	/// <summary>
	/// Permet d'envoyer des ReponseServeurs ? un client.
	/// </summary>
	/// <param name="rspServeur">L'objet de r?ponse</param>
	//void sendReponse(ReponseServeur& rspServeur);
};

