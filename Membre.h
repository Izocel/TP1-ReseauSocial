#pragma once

#include <iostream>
#include <string>
#include <map>

class Membre
{
public:
	Membre();
	Membre(std::string nom, std::string prenom, std::time_t dateNaissance, std::string uuid);
	std::string getUuid() const;
private:
	std::string m_uuid;
	std::string m_nom;
	std::string m_prenom;
	std::string courriel;
	std::time_t m_ddn{};
	std::map<std::string, std::string> m_relations;
	std::map<std::string, std::string> m_messages;
};

