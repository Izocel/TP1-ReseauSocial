#pragma once
#include "Utilitaire.h"


/// <summary>
/// Class Serveur:
/// Classe représentant l'application coté serveur.
/// Regroupe toutes les actions qu'un serveur pourrait effectuer avec pour le client.
/// Doit implémenter des méthodes pour formuler, envoyer et recevoir des données client/serveur.
/// 
/// "Workflow" des données entre client et serveur:
///   (Action->Formulaire->Requete)//([Requete]->Action->Formulaire->Reponse)
/// 
/// 1- Déterminer l'action à effectuer.
/// 2- Acquérir les données à envoyé/recevoir.
/// 3- Formater au besoin les instances ou le format natif des données en json/objet/natif.
/// 4- Traiter les données avant de les appliquer selon l'action ou la requete.
/// 5- Appliquer l'action: [Modification/Application/Acquisition]->(Requete/Reponse)
/// 
/// ************
/// --Pour démonstration le serveur est injecté directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un écouteur/émmetteur d'API pour les méthodes
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
	/// Représente l'access à une couche LGBD fictive du serveur.
	/// </summary>
	MockDatastore m_mockDS;
public:
	Serveur();

	/// <summary>
	/// Pert met de générer un uuid de serveur au hasard.
	/// </summary>
	/// <return>uuid HEXA</return>
	std::string getUuid();

	/// <summary>
	/// Permet d'analyser une requete client et d'ainsi répondre à la requete.
	/// </summary>
	/// <param name="rqstCLient">L'objet de requete</param>
	/// <returns></returns>
	ReponseServeur parseRequete(RequeteClient& rqstCLient);

	/// <summary>
	/// Détermine la réponse pour la route /membre et la méthode POST
	/// </summary>
	/// <param name="rqstClient">L'objet de requete</param>
	/// <returns>La réponse du serveur avec les données inserées</returns>
	ReponseServeur reponsePostMembre(RequeteClient& rqstClient);

	/// <summary>
	/// Détermine la réponse pour la route /message et la méthode POST
	/// </summary>
	/// <param name="rqstClient">L'objet de requete</param>
	/// <returns>La réponse du serveur avec les données inserées</returns>
	ReponseServeur reponsePostMessage(RequeteClient& rqstClient);

	/// <summary>
	/// Permet d'envoyer des ReponseServeurs à un client.
	/// </summary>
	/// <param name="rspServeur">L'objet de réponse</param>
	//void sendReponse(ReponseServeur& rspServeur);
};

