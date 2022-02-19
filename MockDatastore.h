#pragma once
#include <string>
#include <map>

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme


/// <summary>
/// Class MockDatastore:
/// Représente l'objet fesant référence à un LGBD
/// Permet d'enregistrer et acquérir les données pour les Clients du Serveur
/// </summary>
class MockDatastore
{
private:

	/// <summary>
	/// Représente une map de membre enregistrer sur le domaine.
	/// La clé string représente le uuid des membres.
	/// La valeur json sont les données complètes des membres.
	/// </summary>
	std::map<std::string, json> m_mapMembre;

	/// <summary>
	/// Représente une map de conversation enregistrer sur le domaine.
	/// La clé string représente le messageID unique determiner par le serveur.
	/// La valeur json sont les données complètes d'un message.
	/// </summary>
	std::map<std::string, json> m_mapMessages;

public:

	/// <summary>
	/// Retrouve les données d'un membre enregistrer sur le domaine.
	/// </summary>
	/// <param name="membreUuid">le uuid du membre</param>
	/// <returns>Les données du membre</returns>
	json getMembre(std::string membreUuid);

	/// <summary>
	/// Retrouve les données complete d'un message d'une conversation entre deux membres.
	/// </summary>
	/// <param name="membreUuid">le uuid du membre</param>
	/// <returns>Les données du membre</returns>
	json getMessages(std::string messageID);

	/// <summary>
	/// Enregistre les données complete d'un membre.
	/// </summary>
	/// <param name="membreData">Le data du membre</param>
	/// <returns>Les données enregistrées</returns>
	json putMembre(json membreData);

	/// <summary>
	/// Enregistre les données complete d'un message d'une conversation entre deux membres.
	/// </summary>
	/// <param name="messageData">Le data du message</param>
	/// <returns>Les données enregistrées</returns>
	json putMessage(json messageData);
};

