#include "Main.h"


/// ************
/// --Pour démonstration le serveur est injecté directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un écouteur/émmetteur d'API pour les méthodes
/// --fetchRequete, sendResponse, parseRequete, parseResponse
/// ************
int main()
{
    Serveur serveur;

    const std::time_t p3 = Utilitaire::getUtcNow();
    std::string p1 = "vign";
    std::string p2 = "raph";
    Membre m1 = Membre(p1, p2, p3);

    p1 = "eponge";
    p2 = "bob";
    Membre m2 = Membre(p1, p2, p3);

    p1 = "doe";
    p2 = "john";
    Membre m3 = Membre(p1, p2, p3);

    p1 = "doll";
    p2 = "jane";
    Membre m4 = Membre(p1, p2, p3);


    Client client(serveur);

    //Requete ajout membre
    json membreJson;
    RequeteClient rqstMembre;
    rqstMembre.p_clientUuid = client.getUuid();
    rqstMembre.p_route = "/membre";
    rqstMembre.p_serveurUuid = serveur.getUuid();
    rqstMembre.p_type = "POST";


    //Requete ajout relation
    json relationJson;
    RequeteClient rqstRelation;
    rqstRelation.p_clientUuid = client.getUuid();
    rqstRelation.p_route = "/relation";
    rqstRelation.p_serveurUuid = serveur.getUuid();
    rqstRelation.p_type = "POST";


    //Requete lecture relation pour m1
    json getMRelationJson;
    RequeteClient rqstRelationM;
    rqstRelationM.p_clientUuid = client.getUuid();
    rqstRelationM.p_route = "/relation";
    rqstRelationM.p_serveurUuid = serveur.getUuid();
    rqstRelationM.p_type = "GET";


    //Requete post message de m1 à mN
    json messageJson;
    RequeteClient rqstPostMsg;
    rqstPostMsg.p_clientUuid = client.getUuid();
    rqstPostMsg.p_route = "/message";
    rqstPostMsg.p_serveurUuid = serveur.getUuid();
    rqstPostMsg.p_type = "POST";


   
    /// <summary>
    /// Ajout des membre m1,m2,m3 et m4
    /// </summary>
    /// <returns>cout</returns>
    std::cout << "\n\n Ajout des membre m1,m2,m3 et m4 //////////////////////////////////////////////////";
    rqstMembre.p_data = m1.to_json();
    m1.from_json(serveur.parseRequete(rqstMembre).p_data);

    rqstMembre.p_data = m2.to_json();
    m2.from_json(serveur.parseRequete(rqstMembre).p_data);

    rqstMembre.p_data = m3.to_json();
    m3.from_json(serveur.parseRequete(rqstMembre).p_data);

    rqstMembre.p_data = m4.to_json();
    m4.from_json(serveur.parseRequete(rqstMembre).p_data);


    /// <summary>
    /// Ajout des relations avec m2,m3,m4 pour m1
    /// </summary>
    /// <returns>cout</returns>
    std::cout << "\n\n Ajout des relations avec m2,m3,m4 pour m1 ///////////////////////////////////////////";
    relationJson["uuid"] = m1.getUuid();
    relationJson["relationUuid"] = m2.getUuid();
    rqstRelation.p_data = relationJson;
    serveur.parseRequete(rqstRelation);

    relationJson["relationUuid"] = m3.getUuid();
    rqstRelation.p_data = relationJson;
    serveur.parseRequete(rqstRelation);

    // Preuve de "scaling"
    std::cout << "\n\n DEBUT Scale test relations //////////////////////////////";
    getMRelationJson["membreUuid"] = m1.getUuid();
    rqstRelationM.p_data = getMRelationJson;
    serveur.parseRequete(rqstRelationM);

    std::cout << "\n\n FIN Scale test relations ///////////////////////////////";
    relationJson["relationUuid"] = m4.getUuid();
    rqstRelation.p_data = relationJson;
    serveur.parseRequete(rqstRelation);


    // Preuve d'intégrité et d'interrelation après scaling
    std::cout << "\n\n Integrity test relations /////////////////////////////////////////////////////////////";
    rqstRelationM.p_data = getMRelationJson;
    serveur.parseRequete(rqstRelationM);

    std::cout << "\n\n Inter-relation: relation de m2,m3,m4 //////////////////////";
    getMRelationJson["membreUuid"] = m2.getUuid();
    rqstRelationM.p_data = getMRelationJson;
    serveur.parseRequete(rqstRelationM);
    getMRelationJson["membreUuid"] = m3.getUuid();
    rqstRelationM.p_data = getMRelationJson;
    serveur.parseRequete(rqstRelationM);
    getMRelationJson["membreUuid"] = m4.getUuid();
    rqstRelationM.p_data = getMRelationJson;
    serveur.parseRequete(rqstRelationM);


    /// <summary>
    /// Envoi de message par m1 a mN
    /// </summary>
    /// <returns>cout</returns>
    std::cout << "\n\n Envoit des messages par m1 -> mN /////////////////////////////////////////////////";
    messageJson["source"] = m1.getUuid();
    messageJson["date"] = Utilitaire::getUtcNow();
    messageJson["cible"] = m2.getUuid();
    messageJson["texte"] = "Hello M2 !!!";

    messageJson["date"] = messageJson["date"]+1;
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);
    messageJson["date"] = messageJson["date"] + 1;
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);
    messageJson["date"] = messageJson["date"] + 1;
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);
    messageJson["date"] = messageJson["date"] + 1;
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);


    messageJson["date"] = messageJson["date"] + 1;
    messageJson["cible"] = m3.getUuid();
    messageJson["texte"] = "Hello M3 !!!";
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);


    messageJson["date"] = messageJson["date"] + 1;
    messageJson["cible"] = m4.getUuid();
    messageJson["texte"] = "Hello M4 !!!";
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);


    /// <summary>
    /// Envoi de message par m1 a mN
    /// </summary>
    /// <returns>cout</returns>
    messageJson.clear();
    rqstPostMsg.p_route = "/conversation";
    rqstPostMsg.p_type = "GET";
    std::cout << "\n\n Lecture des messages pour m1m2,m1m3,m1m4 ///////////////////////////";

    // Asserts
    messageJson["source"] = m1.getUuid();
    messageJson["cible"] = m2.getUuid();
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);
    messageJson["cible"] = m1.getUuid();
    messageJson["source"] = m2.getUuid();
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);


    messageJson["source"] = m1.getUuid();
    messageJson["cible"] = m3.getUuid();
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);
    messageJson["cible"] = m1.getUuid();
    messageJson["source"] = m3.getUuid();
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);


    messageJson["source"] = m1.getUuid();
    messageJson["cible"] = m4.getUuid();
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);
    messageJson["cible"] = m1.getUuid();
    messageJson["source"] = m4.getUuid();
    rqstPostMsg.p_data = messageJson;
    serveur.parseRequete(rqstPostMsg);



    //Requete get tout les messages de m1
    std::cout << "\n\nRequete get tout les messages de m1";
    RequeteClient rqstGetMsg;
    rqstGetMsg.p_clientUuid = client.getUuid();
    rqstGetMsg.p_route = "/message/" + m1.getUuid();
    rqstGetMsg.p_serveurUuid = serveur.getUuid();
    rqstGetMsg.p_type = "GET";
    rqstGetMsg.p_data = NULL;

    serveur.parseRequete(rqstGetMsg);




    return 0;
}

// Asserts
/*
*
* 

 Ajout des membre m1,m2,m3 et m4 //////////////////////////////////////////////////

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"vign","prenom":"raph","relations":{},"uuid":"vigrap1645498531164549853141"}

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"eponge","prenom":"bob","relations":{},"uuid":"epobob1645498531164549853134"}

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"doe","prenom":"john","relations":{},"uuid":"doejoh1645498531164549853124"}

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"doll","prenom":"jane","relations":{},"uuid":"doljan1645498531164549853166"}

 Ajout des relations avec m2,m3,m4 pour m1 ///////////////////////////////////////////

{"relationUuid":"epobob1645498531164549853134","uuid":"vigrap1645498531164549853141"}

{"relationUuid":"doejoh1645498531164549853124","uuid":"vigrap1645498531164549853141"}

 DEBUT Scale test relations //////////////////////////////

 IN:
{"membreUuid":"vigrap1645498531164549853141"}

 OUT:
["epobob1645498531164549853134","doejoh1645498531164549853124"]

 FIN Scale test relations ///////////////////////////////

{"relationUuid":"doljan1645498531164549853166","uuid":"vigrap1645498531164549853141"}

 Integrity test relations /////////////////////////////////////////////////////////////

 IN:
{"membreUuid":"vigrap1645498531164549853141"}

 OUT:
["epobob1645498531164549853134","doejoh1645498531164549853124","doljan1645498531164549853166"]

 Inter-relation: relation de m2,m3,m4 //////////////////////

 IN:
{"membreUuid":"epobob1645498531164549853134"}

 OUT:
["vigrap1645498531164549853141"]

 IN:
{"membreUuid":"doejoh1645498531164549853124"}

 OUT:
["vigrap1645498531164549853141"]

 IN:
{"membreUuid":"doljan1645498531164549853166"}

 OUT:
["vigrap1645498531164549853141"]

 Envoit des messages par m1 -> mN /////////////////////////////////////////////////

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}

 IN MOCK: vigrap1645498531164549853141doejoh1645498531164549853124: {"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}

 OUT: [{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}]

 IN RQST: {"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}

 IN MOCK: vigrap1645498531164549853141doljan1645498531164549853166: {"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}

 OUT: [{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]

 Lecture des messages pour m1m2,m1m3,m1m4 ///////////////////////////

 IN:
{"cible":"epobob1645498531164549853134","source":"vigrap1645498531164549853141"}

 OUT:
[{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN:
{"cible":"vigrap1645498531164549853141","source":"epobob1645498531164549853134"}

 OUT:
[{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN:
{"cible":"doejoh1645498531164549853124","source":"vigrap1645498531164549853141"}

 OUT:
[{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}]

 IN:
{"cible":"vigrap1645498531164549853141","source":"doejoh1645498531164549853124"}

 OUT:
[{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}]

 IN:
{"cible":"doljan1645498531164549853166","source":"vigrap1645498531164549853141"}

 OUT:
[{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]

 IN:
{"cible":"vigrap1645498531164549853141","source":"doljan1645498531164549853166"}

 OUT:
[{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]

Requete get tout les messages de m1

 IN:
0

 OUT:
[[{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}],[{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}],[{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]]
* 
* **/