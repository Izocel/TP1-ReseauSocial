#include "Main.h"

int main()
{
    // Incoh�rant mais serait d�termin� � l'installation
    Serveur serveur;
    Client client(serveur);
    
    client.creeMembre();
    client.creeMembre();

    // Aserts les mesages ce retrouve dans un json Array au niveau du mockstore 
    // Au sein d'une map avec comme key_val un ID unique de msg. (consid�rant les id de membres comme unique) 
    // Une entr�e par conversation entre 2 membres contenant un object Json contenant les msg. de la conersation
    std::string uuidTEST = "fdsfsd";
    client.envoyerMessage(uuidTEST);

    getchar();
}
