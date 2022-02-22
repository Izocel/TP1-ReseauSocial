#include "Main.h"
#include "Test.h"


/// ************
/// --Pour d�monstration le serveur est inject� directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un �couteur/�mmetteur d'API pour les m�thodes
/// --fetchRequete, sendResponse, parseRequete, parseResponse
/// ************
int main()
{
    Serveur serveur;
    Client client(serveur);

    //Test::inputOutputJson();
}