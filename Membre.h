#pragma once
#include <iostream>
#include <string>
#include <map>

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme



/// <summary>
/// Class Membre:
/// Repr�sente une membre
/// </summary>
class Membre
{
public:
	Membre();
	Membre(std::string& nom, std::string& prenom, time_t& dateNaissance);

	/// <summary>
	/// Permet de contruire un objet Membre selon le mod�le json.
	/// </summary>
	/// <param name="j">Le mod�le json</param>
	void from_json(const json& j);

	/// <summary>
	/// Contruit un mod�le json du membre.
	/// </summary>
	/// <returns>Le mod�le json du membre</returns>
	json to_json();


	/// <summary>
	/// Permet d'acqu�rir le uuid du membre.
	/// </summary>
	/// <returns>Uuid 2a2aDATE2d</returns>
	std::string getUuid() const;


private:
	std::string m_uuid;
	std::string m_nom;
	std::string m_prenom;
	std::string m_courriel;
	std::string m_motPasse;
	/// <summary>
	/// Date de naissance au format epoch
	/// </summary>
	std::time_t m_ddn;

	/// <summary>
	/// Repr�sente les relations approuver par le membre.
	/// La cl� string repr�sente le uuid du membre approuv�.
	/// La valeur json sont les donn�es approuver pour une relation entre membre.
	/// </summary>
	std::map<std::string, json> m_relations;

	/// <summary>
	/// Repr�sente les conversations entre le membre et ces relations.
	/// La cl� string repr�sente le messageID unique determin� par le serveur.
	/// La valeur json sont les donn�es de la conversation.
	/// </summary>
	std::map<std::string, json> m_messages;
};

