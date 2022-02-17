#include "Serveur.h"


ReponseServeur Serveur::parseRequete(RequeteClient& rqstCLient)
{
    if (rqstCLient.p_type == "POST") {

        if (rqstCLient.p_nom == "/membre") {

            rqstCLient.p_data["uuid"] = "fdsa";
            m_mockDS.putMembre(rqstCLient.p_data);
        }
    }

    else if (rqstCLient.p_type == "GET") {

    }
    return ReponseServeur();
}
