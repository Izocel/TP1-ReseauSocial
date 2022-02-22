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

        if (rqstCLient.p_route == "/relation") {
            return reponsePostRelation(rqstCLient);
        }
    }

    else if (rqstCLient.p_type == "GET") {

        if (rqstCLient.p_route == "/membre") {
            return reponseGetMembre(rqstCLient);
        }

        if (rqstCLient.p_route.find("/message") == 0) {

            return reponseGetMessage(rqstCLient);
        }

        if (rqstCLient.p_route == "/conversation") {

            return reponseGetConversation(rqstCLient);
        }

        if (rqstCLient.p_route == "/relation") {
            return reponseGetRelation(rqstCLient);
        }
    }
    //sendReponse();
    return ReponseServeur();
}

const std::string Serveur::genererMembreUuid(const RequeteClient& rqstPostMembre) {
    // Cast le json de p_data en tant que string pour la méthode uuidMembre de l'utilitaire!

    std::string uuidMembre;
    std::string nom;
    std::string prenom;
    time_t dateT;

    try
    {
        rqstPostMembre.p_data.at("nom").get_to(nom);
        rqstPostMembre.p_data.at("prenom").get_to(prenom);
        rqstPostMembre.p_data.at("date").get_to(dateT);
        uuidMembre = Utilitaire::uuidMembre(nom, prenom, dateT);
    }
    catch (const std::exception&)
    {

    }
    return uuidMembre;
}

const std::string Serveur::genererMessageID(const RequeteClient& rqstPostMessage) {
    std::string cible;
    std::string source;
    std::string messageID;

    try
    {
        rqstPostMessage.p_data.at("cible").get_to(cible);
        rqstPostMessage.p_data.at("source").get_to(source);
        messageID = Utilitaire::findUniqueMsgId(cible, source);
    }
    catch (const std::exception&)
    {

    }
    return messageID;
}

ReponseServeur Serveur::reponsePostMembre(RequeteClient& rqstClient) {
 
    ReponseServeur rsp;
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;

    std::string uuidMembre = genererMembreUuid(rqstClient);
    rqstClient.p_data["uuid"] = uuidMembre;
    if (uuidMembre.empty()) return rsp;

    std::cout << "\n\n" << rqstClient.p_data;
    rqstClient.p_data = m_mockDS.putMembre(rqstClient.p_data);

    if (rqstClient.p_data.empty()) return rsp;

    rsp.p_type = "ok";  
    rsp.p_data = rqstClient.p_data;

    return rsp;
}


ReponseServeur Serveur::reponsePostMessage(RequeteClient& rqstClient) {

    ReponseServeur rsp;
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;

    std::cout << "\n\n IN RQST: " << rqstClient.p_data;

    /// Safe guard que le message est envoyé vers une relation entre cible et source
    std::string sourceUuid = rqstClient.p_data.at("source");
    std::string cibleUuid = rqstClient.p_data.at("cible");
    json relations = m_mockDS.getRelations(sourceUuid);
    bool relationValide = false;

    if (relations.is_array()) {
        for (size_t i = 0; i < relations.size(); i++)
        {
            relationValide = relations[i] == cibleUuid;
            if (relationValide) i = relations.size();
        }
    }

    if (!relationValide) return rsp;

    std::string messageID = genererMessageID(rqstClient);
    if (messageID.empty()) return rsp;

    std::cout << "\n\n IN MOCK: " << messageID << ": " << rqstClient.p_data;
    rqstClient.p_data = m_mockDS.putMessage(messageID, rqstClient.p_data);

    if (rqstClient.p_data.empty()) return rsp;

    rsp.p_type = "ok";
    rsp.p_data = rqstClient.p_data;

    std::cout << "\n\n OUT: " << rqstClient.p_data;

    return rsp;
}


ReponseServeur Serveur::reponsePostRelation(RequeteClient& rqstClient) {

    std::cout <<  "\n\n" << rqstClient.p_data;
    json uuidRelation = m_mockDS.putRelation(rqstClient.p_data);

    ReponseServeur rsp;

    if (uuidRelation.empty()) return rsp;

    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;
    rsp.p_data = rqstClient.p_data;
    return rsp;
}

ReponseServeur Serveur::reponseGetMembre(RequeteClient& rqstClient) {

    std::cout << "\n\n IN:\n" << rqstClient.p_data;
    json membre = m_mockDS.getMembre(rqstClient.p_data["uuid"]);

    ReponseServeur rsp;

    if (membre.empty()) return rsp;

    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;
    rsp.p_data = membre;

    std::cout << "\n\n OUT:\n" << rsp.p_data;
    return rsp;
}

ReponseServeur Serveur::reponseGetMessage(RequeteClient& rqstClient) {

    std::cout << "\n\n IN:\n" << rqstClient.p_data;
    json relations;
    json messages;
    std::string membreID;
    std::string messageID;
    std::vector < std::string> attributsRte;

    // Trouve les relations du membre si un membre est forunit dans la route
    attributsRte = getRouteAttributs(rqstClient.p_route);
    if (attributsRte.size() == 1) {
        membreID = attributsRte[0];
        relations = m_mockDS.getRelations(membreID);
    }
   
    // Selon les relation retrouve les messages du membre
    if (relations.size() > 0) {
        
        for (size_t i = 0; i < relations.size(); i++)
        {
            messageID = Utilitaire::findUniqueMsgId(relations[i], membreID);
            messages.push_back(m_mockDS.getConversation(messageID));
        }
    }

    ReponseServeur rsp;
    if (messages.empty()) return rsp;

    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;
    rsp.p_data = messages;

    std::cout << "\n\n OUT:\n" << rsp.p_data;
    return rsp;
}

ReponseServeur Serveur::reponseGetConversation(RequeteClient& rqstClient)
{
    std::cout << "\n\n IN:\n" << rqstClient.p_data;
    json conversation;
    std::string membreID;
    std::string relationID;
    std::string messageID;

    // Trouve le messageID
    membreID = rqstClient.p_data["source"];
    relationID = rqstClient.p_data["cible"];
    messageID = Utilitaire::findUniqueMsgId(membreID, relationID);



    // Selon les relation retrouve les messages du membre
    if ( ! messageID.empty()) {
        conversation = m_mockDS.getConversation(messageID);
    }

    ReponseServeur rsp;
    if (conversation.empty()) return rsp;

    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;
    rsp.p_data = conversation;

    std::cout << "\n\n OUT:\n" << rsp.p_data;
    return rsp;
}


ReponseServeur Serveur::reponseGetRelation(RequeteClient& rqstClient) {

    std::cout << "\n\n IN:\n" << rqstClient.p_data;
    json relations = m_mockDS.getRelations(rqstClient.p_data["membreUuid"]);

    ReponseServeur rsp;

    if (relations.empty()) return rsp;

    rsp.p_type = "ok";
    rsp.p_serveurUuid = m_uuid;
    rsp.p_route = rqstClient.p_route;
    rsp.p_clientUuid = rqstClient.p_clientUuid;
    rsp.p_data = relations;

    std::cout << "\n\n OUT:\n" << rsp.p_data;
    return rsp;
}


std::vector<std::string> Serveur::getRouteAttributs(std::string& route) {
    std::string delimiter = "/";
    std::string sousRoute = route.substr(1, route.size());
    return Utilitaire::splitStr(delimiter, sousRoute);
}

//void Serveur::sendReponse(ReponseServeur& rspServeur)
//{
//}
