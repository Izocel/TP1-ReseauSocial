#include "Membre.h"
#include "Utilitaire.h"

Membre::Membre()
{
}

Membre::Membre(std::string& nom, std::string& prenom, const time_t& naissanceEpoch)
{
	m_nom = nom; m_prenom = prenom;
	m_ddn = naissanceEpoch;
}

std::string Membre::getUuid() const
{
	return m_uuid;
}

json Membre::to_json()
{
	try
	{
		return json{
			{"uuid", m_uuid},
			{"nom", m_nom},
			{"prenom", m_prenom},
			{"courriel", m_courriel},
			{"mdp", m_motPasse},
			{"date", m_ddn},
			{"relations", m_relations},
			{"messages", m_messages}
		};
	}
	catch (const std::exception&)
	{

	}
	return json();
}

void Membre::from_json(const json& j)
{
	try
	{
		j.at("uuid").get_to(m_uuid);
		j.at("nom").get_to(m_nom);
		j.at("prenom").get_to(m_prenom);
		j.at("courriel").get_to(m_courriel);
		j.at("mdp").get_to(m_motPasse);
		j.at("date").get_to(m_ddn);
		j.at("relations").get_to(m_relations);
		j.at("messages").get_to(m_messages);
	}
	catch (const std::exception&)
	{

	}
}
