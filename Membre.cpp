#include "Membre.h"

Membre::Membre(std::string nom, std::string prenom, 
	std::time_t dateNaissance, std::string uuid)
{
	m_nom = nom; m_prenom = prenom; m_ddn = dateNaissance; m_uuid = uuid;
}
