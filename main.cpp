#include "Main.h"

int main()
{
    // Incoh�rant mais serait d�termin� � l'installation
    Serveur serveur;
    Client client(serveur);
    

    client.creeMembre();


    getchar();
}
