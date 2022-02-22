#pragma once
#include <string>
#include <map>

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme


/// <summary>
/// Class MockDatastore:
/// Repr�sente l'objet fesant r�f�rence � un LGBD
/// Permet d'enregistrer et acqu�rir les donn�es pour les Clients du Serveur
/// </summary>
class MockDatastore
{
private:

	/// <summary>
	/// Repr�sente une map de membre enregistrer sur le domaine.
	/// La cl� string repr�sente le uuid des membres.
	/// La valeur json sont les donn�es compl�tes des membres.
	/// </summary>
	std::map<std::string, json> m_mapMembre;

	/// <summary>
	/// Repr�sente une map de conversation enregistrer sur le domaine.
	/// La cl� string repr�sente le messageID unique determiner par le serveur.
	/// La valeur json sont les donn�es compl�tes d'un message.
	/// </summary>
	std::map<std::string, json> m_mapMessages;


	/// <summary>
	/// Repr�sente une map des relation pour un membre donn� enregistrer sur le domaine.
	/// La cl� string repr�sente le uuid du membre.
	/// La valeur json est une liste de uuid au format json.
	/// </summary>
	std::map<std::string, json> m_mapRelations;

public:

	/// <summary>
	/// Retrouve les donn�es d'un membre enregistrer sur le domaine.
	/// </summary>
	/// <param name="membreUuid">le uuid du membre</param>
	/// <returns>Les donn�es du membre</returns>
	json getMembre(std::string membreUuid);

	/// <summary>
	/// Retrouve les donn�es complete d'une conversation entre deux membres.
	/// </summary>
	/// <param name="messageID">le uuid du message</param>
	/// <returns>Les donn�es de la conversation</returns>
	json getConversation(std::string messageID);



	json getRelations(std::string membreUuid);

	/// <summary>
	/// Enregistre les donn�es complete d'un membre.
	/// </summary>
	/// <param name="membreData">Le data du membre</param>
	/// <returns>Les donn�es enregistr�es</returns>
	json putMembre(json membreData);

	/// <summary>
	/// Enregistre les donn�es complete d'un message d'une conversation entre deux membres.
	/// </summary>
	/// <param name="messageData">Le data du message</param>
	/// <returns>Les donn�es enregistr�es</returns>
	json putMessage(std::string messageID, json messageData);


	json putRelation(json relationData);
};

