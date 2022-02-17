#include "Membre.h"

Membre::Membre()
{
}

Membre::Membre(std::string nom, std::string prenom,
	std::time_t dateNaissance, std::string uuid)
{
	m_nom = nom; m_prenom = prenom; m_ddn = dateNaissance; m_uuid = uuid;
}

std::string Membre::getUuid() const
{
	return m_uuid;
}

json Membre::to_json()
{
	return json {
		{"uuid", m_uuid},
		{"nom", m_nom},
		{"prenom", m_prenom},
		{"courriel", m_courriel},
		{"mdp", m_motPasse},
		{"relations", m_relations},
		{"message", m_messages}
	};
}

void Membre::from_json(const json& j)
{
	j.at("uuid").get_to(m_uuid);
	j.at("nom").get_to(m_nom);
	j.at("prenom").get_to(m_prenom);
	j.at("courriel").get_to(m_courriel);
	j.at("mdp").get_to(m_motPasse);
	j.at("relations").get_to(m_relations);
	j.at("messages").get_to(m_messages);
}
