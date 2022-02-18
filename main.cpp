#include "Main.h"

int main()
{
    // Incohérant mais serait déterminé à l'installation
    Serveur serveur;
    Client client(serveur);
    

    //client.creeMembre();

    std::string dateS = "1993/09/19";
    time_t timeT = Utilitaire::parseTimeYYYYMMDD(dateS);


    std::cout << Utilitaire::parseTimeT(timeT, "%y/%m/%d");

    getchar();
}
