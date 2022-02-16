#include "Client.h"

Client::Client()
{

}

std::map<std::string, std::string> Client::formulaireMembre()
{	
	std::string str;
	std::map<std::string, std::string> map_formulaire;

	std::cout << "Votre nom: ";
	getline(std::cin, str);
	std::stringstream(str) >> map_formulaire["nom"];

	std::cout << "Votre prenom: ";
	getline(std::cin, str);
	std::stringstream(str) >> map_formulaire["prenom"];

	std::cout << "Votre courriel: ";
	getline(std::cin, str);
	std::stringstream(str) >> map_formulaire["courriel"];

	std::cout << "Votre mot de passe: ";
	getline(std::cin, str);
	std::stringstream(str) >> map_formulaire["mdp"];

	return map_formulaire;
}

std::map<std::string, std::string> Client::formulaireMessage(std::string uuidMembre)
{
	std::string str;
	std::map<std::string, std::string> map_formulaire;

	map_formulaire["clientUuid"] = m_uuid;
	map_formulaire["source"] = m_membreConnecter.getUuid();
	map_formulaire["cible"] = uuidMembre;

	std::cout << "Votre message: \n";
	getline(std::cin, str);
	std::stringstream(str) >> map_formulaire["texte"];

	// Trop long a implémenter de la bonne façon
	//time_t t = time(NULL); 
	//char* timeinfo = asctime(gmtime(&t));
	std::string timeinfo = "93/09/19";
	map_formulaire["date"] = timeinfo;

	return map_formulaire;
}
