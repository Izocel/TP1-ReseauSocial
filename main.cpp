#include <iostream>

#include "Client.h"

int main()
{

    Client client;

    std::map<std::string, std::string> map_formulaire;

    map_formulaire = client.formulaireMessage("123456");


    getchar();
}
