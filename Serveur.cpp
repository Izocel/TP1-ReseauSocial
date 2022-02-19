#include "Serveur.h"

Serveur::Serveur()
{
    m_uuid = Utilitaire::uuidServeur();
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

        if (rqstCLient.p_route == "/membre") {
            return reponsePostMembre(rqstCLient);
        }

        if (rqstCLient.p_route == "/message") {
            return reponsePostMessage(rqstCLient);
        }
    }

    else if (rqstCLient.p_type == "GET") {

    }
    //sendReponse();
    return ReponseServeur();
}

ReponseServeur Serveur::reponsePostMembre(RequeteClient& rqstClient) {
    using namespace Utilitaire;


    // Cast le json de p_data en tant que string pour la m�thode uuidMembre !
    std::string nom; 
    rqstClient.p_data.at("nom").get_to(nom);
    std::string prenom;
    rqstClient.p_data.at("prenom").get_to(prenom);

    // Formule le uuid du membre
    time_t dateT;
    rqstClient.p_data.at("date").get_to(dateT);
    std::string uuid = uuidMembre(nom, prenom, dateT);
    rqstClient.p_data["uuid"] = uuid;

    std::cout << rqstClient.p_data;
    m_mockDS.putMembre(rqstClient.p_data);


    // Il serait possible d'initialiser la r�ponse avec la requete sinon...
    ReponseServeur rsp;
    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;    
    rsp.p_data = rqstClient.p_data;

    return rsp;
}


ReponseServeur Serveur::reponsePostMessage(RequeteClient& rqstClient) {

    std::cout << rqstClient.p_data;
    m_mockDS.putMessage(rqstClient.p_data);

    ReponseServeur rsp;
    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;
    rsp.p_data = rqstClient.p_data;
    return rsp;
}

//void Serveur::sendReponse(ReponseServeur& rspServeur)
//{
//}
