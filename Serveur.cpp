#include "Serveur.h"


Serveur::Serveur()
{
    m_uuid = getUuid();
}

std::string Serveur::getUuid()
{
    if (m_uuid.empty())
        m_uuid = Utilitaire::uuidServeur();
    return m_uuid;
}

ReponseServeur Serveur::parseRequete(RequeteClient& rqstCLient)
{
    if (rqstCLient.p_serveurUuid != m_uuid) return ReponseServeur();

    if (rqstCLient.p_type == "POST") {

        if (rqstCLient.p_nom == "/membre") {
            return reponsePostMembre(rqstCLient);
        }
    }

    else if (rqstCLient.p_type == "GET") {

    }
    //sendReponse();
    return ReponseServeur();
}

ReponseServeur Serveur::reponsePostMembre(RequeteClient& rqstClient) {
    using namespace Utilitaire;


    // Cast le json de p_data en tant que string pour la méthode uuidMembre !
    std::string nom; 
    rqstClient.p_data.at("nom").get_to(nom);
    std::string prenom;
    rqstClient.p_data.at("prenom").get_to(prenom);
    std::string date;
    rqstClient.p_data.at("date").get_to(date);
    
    
    std::string uuid = uuidMembre(nom, prenom, date);
    rqstClient.p_data["uuid"] = uuid;

    std::cout << rqstClient.p_data;

    m_mockDS.putMembre(rqstClient.p_data);


    // Il serait possible d'initialiser la réponse avec la requete sinon...
    ReponseServeur rsp;
    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_nom = rqstClient.p_nom;
    rsp.p_clientUuid = rqstClient.p_clientUuid;    
    rsp.p_data = rqstClient.p_data;

    return rsp;
}

void Serveur::sendReponse(ReponseServeur& rspServeur)
{
}
