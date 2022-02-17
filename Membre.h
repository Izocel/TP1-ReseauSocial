#pragma once

#include <iostream>
#include <string>
#include <map>

//// Third-Party
#include "json.hpp"
using json = nlohmann::json;
// Ref: https://github.com/nlohmann/json#readme

class Membre
{
public:
	Membre();
	void from_json(const json& j);
	Membre(std::string nom, std::string prenom, std::time_t dateNaissance, std::string uuid);
	std::string getUuid() const;

	json to_json();
private:
	std::string m_uuid;
	std::string m_nom;
	std::string m_prenom;
	std::string m_courriel;
	std::string m_motPasse;
	std::time_t m_ddn{};
	std::map<std::string, std::string> m_relations;
	std::map<std::string, std::string> m_messages;
};

