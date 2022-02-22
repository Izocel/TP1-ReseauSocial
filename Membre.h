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
/// Représente une membre
/// </summary>
class Membre
{
public:
	Membre();
	Membre(std::string& nom, std::string& prenom, const time_t& dateNaissance);

	/// <summary>
	/// Permet de contruire un objet Membre selon le modèle json.
	/// </summary>
	/// <param name="j">Le modèle json</param>
	void from_json(const json& j);

	/// <summary>
	/// Contruit un modèle json du membre.
	/// </summary>
	/// <returns>Le modèle json du membre</returns>
	json to_json();


	/// <summary>
	/// Permet d'acquérir le uuid du membre.
	/// </summary>
	/// <returns>Uuid 2a2aDATE2d</returns>
	std::string getUuid() const;


	/// <summary>
	/// Permet d'acquérir le nom du membre.
	/// </summary>
	/// <returns>Le nom du membre</returns>
	const std::string getNom(){ return m_nom;};


	/// <summary>
	/// Permet d'acquérir le prenom du membre.
	/// </summary>
	/// <returns>Le prenom du membre</returns>
	const std::string getPrenom(){ return m_prenom; };


private:
	std::string m_uuid;
	std::string m_nom;
	std::string m_prenom;
	std::string m_courriel;
	std::string m_motPasse;
	/// <summary>
	/// Date de naissance au format epoch
	/// </summary>
	std::time_t m_ddn{0};

	/// <summary>
	/// Représente les relations approuver par le membre.
	/// La clé string représente le uuid du membre approuvé.
	/// La valeur json sont les données approuver pour une relation entre membre.
	/// </summary>
	std::map<std::string, json> m_relations;

	/// <summary>
	/// Représente les conversations entre le membre et ces relations.
	/// La clé string représente le messageID unique determiné par le serveur.
	/// La valeur json sont les données de la conversation.
	/// </summary>
	std::map<std::string, json> m_messages;
};

