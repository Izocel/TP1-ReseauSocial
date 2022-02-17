#include "Main.h"

int main()
{
    // Incohérant mais serait déterminé à l'installation
    Serveur serveur;
    Client client(serveur);
    

    client.creeMembre();


    getchar();
}
