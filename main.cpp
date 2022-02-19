#include "Main.h"


/// ************
/// --Pour démonstration le serveur est injecté directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un écouteur/émmetteur d'API pour les méthodes
/// --fetchRequete, sendResponse, parseRequete, parseResponse
/// ************
int main()
{
    
    Serveur serveur;
    Client client(serveur); 
    
    client.creeMembre();
    client.creeMembre();

    // Aserts les mesages ce retrouve dans un json Array au niveau du mockstore 
    // Au sein d'une map avec comme key_val un ID unique de msg. (considérant les id de membres comme unique) 
    // Une entrée par conversation entre 2 membres contenant un object Json contenant les msg. de la conersation
    std::string uuidTEST = "fdsfsd";
    client.envoyerMessage(uuidTEST);

    getchar();
}
