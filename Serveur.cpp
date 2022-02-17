#include "Serveur.h"


std::string Serveur::getUuid()
{
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
        rqstClient.p_data["uuid"] = Utilitaire::uuidMembre(
        rqstClient.p_data.at("nom"),
        rqstClient.p_data.at("prenom"),
        rqstClient.p_data.at("date")
    );
    m_mockDS.putMembre(rqstClient.p_data);


    // Il serait possible d'initialiser la réponse avec la requete sinon...
    ReponseServeur rsp;
    rsp.p_type = "OK";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_nom = rqstClient.p_nom;
    rsp.p_clientUuid = rqstClient.p_clientUuid;    
    rsp.p_data["uuid"] = rqstClient.p_data["uuid"];

    return rsp;
}

void Serveur::sendReponse(ReponseServeur& rspServeur)
{
}
