#include "Utilitaire.h"

/// <summary>
/// Class Client:
/// Classe représentant l'application coté utilisateur.
/// Regroupe toutes les actions qu'un utilisateur pourrait effectuer avec l'application.
/// Doit implémenter des méthodes pour formuler, envoyer et recevoir des données client/serveur.
/// 
/// "Workflow" des données entre client et serveur:
///   (Action->Formulaire->Requete)//([Requete]->Action->Formulaire->Reponse)
/// 
/// 1- Déterminer l'action à effectuer.
/// 2- Acquérir les données à envoyé/recevoir.
/// 3- Formater au besoin les instances ou le format natif des données en json/objet/natif.
/// 4- Traiter les données avant de les appliquer selon l'action ou la requete.
/// 5- Appliquer l'action: [Modification/Application/Acquisition]->(Requete/Reponse)
/// 
/// ************
/// --Pour démonstration le serveur est injecté directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un écouteur/émmetteur d'API pour les méthodes
/// --fetchRequete, sendResponse, parseRequete, parseResponse
/// 
/// -- Pour l'instant seulement le client pour faire des requete vers le serveur...
/// ************
/// </summary>
/// 




static const int LARGEURMENUCONNECTION = 60;
static const std::string MENUCONNECTION{
R"(

                       MENU-CONNECTION
============================================================
------------------------------------------------------------
0- Se connecter                                            |
1- S'enregistrer                                           |
------------------------------------------------------------
============================================================
)"
};


static const int NOMBRECHOIXDEFAULT = 2;
static const int LARGEURMENUACCEUIL = 84;
static const std::string MENUACCEUILHEADER{
R"(

                                    MENU-ACCEUIL
====================================================================================
------------------------------------------------------------------------------------
0- Ajouter une relation                                                            |
1- Retirer une relation                                                            |
2- Envoyer un message                                                              |)"
};


static const int LARGEURCONVERSATION = 84;
static const std::string CONVERSATIONHEADER{
R"(

                                    CONVERSATION
====================================================================================
------------------------------------------------------------------------------------
                                                                                   |)"
};


static const std::string RELATIONHEADER{
R"(

                                      RELATIONS
====================================================================================
------------------------------------------------------------------------------------
                                                                                   |)"
};

static const std::string SKIPLINE{R"(
                                                                                   |)" };

static const std::string FOOTER{R"(
------------------------------------------------------------------------------------
====================================================================================
)"};


static const std::string QUESTIONMENU{ R"(
----------------------------------------------------------
Entrer votre choix (exit) pour quitter                   |
----------------------------------------------------------
->)" };



static const std::string MESSAGEAUREVOIR{ R"(
----------------------------------------------------------
				  MERCI ET AU REVOIR !                   |
----------------------------------------------------------
)" };



class Client
{
public:
	Client();
	Client(Serveur& srv);

	/// <summary>
	/// Boucle d'application
	/// </summary>
	/// <returns>False</returns>
	int run();

	void vueMembreConnecter();

	void vueMessage(std::string& uuidRelation);

	void vueConversation(const ReponseServeur& rspSrvConversation);

	void vueAcceuil();

	void vueConnection(int& iTentative);

	/// <summary>
	/// Permet de crée un membre, de l'enregistrer sur le serveur
	/// et d'ainsi déterminer l'utilisateur qui fait usage du client (m_membreConnecter).
	/// Utilise: formulaireMembre(), requete(), fetchRequete()
	/// </summary>
	/// <returns>True si l'action c'est bien déroulée</returns>
	bool creeMembre();

	/// <summary>
	/// Acquière les données de l'usager pour définir le membre au moyen de std::cin
	/// Pour chaque entrée, elles sont "muter" au sein d'un objet json. 
	/// </summary>
	/// <returns>L'objet json pour la requete serveur</returns>
	json formulaireMembre();

	/// <summary>
	/// Même logique applicative que pour créer un membre:
	/// Selon la conversation enregistre le message sur le serveur.
	/// </summary>
	/// <param name="cibleUuid">Le uuid du membre à contacter</param>
	/// <param name="texte">Le texte entrer en console.</param>
	/// <returns>True si l'action c'est bien déroulée</returns>
	bool envoyerMessage(std::string& cibleUuid, std::string& texte);

	/// <summary>
	/// Même logique applicative que le formulaire membre:
	/// Acquière le texte au moyen du paramêtre
	/// Pour chaque entrée, elles sont "muter" au sein d'un objet json. 
	/// </summary>
	/// <param name="cibleUuid">Le uuid du membre à contacter.</param>
	/// <param name="texte">Le texte entrer en console.</param>
	/// <returns>L'objet json pour la requete serveur</returns>
	json formulaireMessage(std::string& uuidCible, std::string& texte);

	/// <summary>
	/// Permet d'acquérir ou de définir le uuid du client.
	/// </summary>
	/// <returns>Uuid HEXA</returns>
	std::string getUuid();


private:
	Serveur m_serveur;

	/// <summary>
	/// Représente un parametre URI du serveur à contacter.
	/// </summary>
	std::string m_serveurUuid;

	/// <summary>
	/// Si le client est connecter via un membre au serveur.
	/// </summary>
	bool m_connecter{false};
	std::string m_version{"1.0"};

	/// <summary>
	/// Le Uuid HEXA du client.
	/// </summary>
	std::string m_uuid{getUuid()};

	/// <summary>
	/// Représente les vues possibles à afficher.
	/// </summary>
	std::string m_menuAcceuil;
	std::string m_menuConnection;
	std::string m_conversation;

	/// <summary>
	/// Le membre utilisant le client.
	/// </summary>
	Membre m_membreConnecter;


	/// <summary>
	/// Construit une structure de requete pouvant être envoyer vers un serveur.
	/// </summary>
	/// <param name="nomRoute">Le nom de la route à contacter.</param>
	/// <param name="data">Le data à envoyer afin que le serveur puisse traiter la demande.</param>
	/// <param name="type">Le type de requete [POST,PUT,GET,DELETE]</param>
	/// <returns>La structure de requete selon la convention.</returns>
	RequeteClient requete(std::string nomRoute, json& data, std::string type);

	/// <summary>
	/// Contacte le serveur selon la structure de requete.
	/// </summary>
	/// <param name="requeteC">La structure représentant la requete à effectuer</param>
	/// <returns>La structure de reponse du serveur.</returns>
	ReponseServeur fetchRequete(RequeteClient& requeteC);
};

