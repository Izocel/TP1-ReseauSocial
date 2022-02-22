#include "Utilitaire.h"

/// <summary>
/// Class Client:
/// Classe repr�sentant l'application cot� utilisateur.
/// Regroupe toutes les actions qu'un utilisateur pourrait effectuer avec l'application.
/// Doit impl�menter des m�thodes pour formuler, envoyer et recevoir des donn�es client/serveur.
/// 
/// "Workflow" des donn�es entre client et serveur:
///   (Action->Formulaire->Requete)//([Requete]->Action->Formulaire->Reponse)
/// 
/// 1- D�terminer l'action � effectuer.
/// 2- Acqu�rir les donn�es � envoy�/recevoir.
/// 3- Formater au besoin les instances ou le format natif des donn�es en json/objet/natif.
/// 4- Traiter les donn�es avant de les appliquer selon l'action ou la requete.
/// 5- Appliquer l'action: [Modification/Application/Acquisition]->(Requete/Reponse)
/// 
/// ************
/// --Pour d�monstration le serveur est inject� directement comme membre de Client.
///	--Il suffirait simplement d'ajouter un �couteur/�mmetteur d'API pour les m�thodes
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
	/// Permet de cr�e un membre, de l'enregistrer sur le serveur
	/// et d'ainsi d�terminer l'utilisateur qui fait usage du client (m_membreConnecter).
	/// Utilise: formulaireMembre(), requete(), fetchRequete()
	/// </summary>
	/// <returns>True si l'action c'est bien d�roul�e</returns>
	bool creeMembre();

	/// <summary>
	/// Acqui�re les donn�es de l'usager pour d�finir le membre au moyen de std::cin
	/// Pour chaque entr�e, elles sont "muter" au sein d'un objet json. 
	/// </summary>
	/// <returns>L'objet json pour la requete serveur</returns>
	json formulaireMembre();

	/// <summary>
	/// M�me logique applicative que pour cr�er un membre:
	/// Selon la conversation enregistre le message sur le serveur.
	/// </summary>
	/// <param name="cibleUuid">Le uuid du membre � contacter</param>
	/// <param name="texte">Le texte entrer en console.</param>
	/// <returns>True si l'action c'est bien d�roul�e</returns>
	bool envoyerMessage(std::string& cibleUuid, std::string& texte);

	/// <summary>
	/// M�me logique applicative que le formulaire membre:
	/// Acqui�re le texte au moyen du param�tre
	/// Pour chaque entr�e, elles sont "muter" au sein d'un objet json. 
	/// </summary>
	/// <param name="cibleUuid">Le uuid du membre � contacter.</param>
	/// <param name="texte">Le texte entrer en console.</param>
	/// <returns>L'objet json pour la requete serveur</returns>
	json formulaireMessage(std::string& uuidCible, std::string& texte);

	/// <summary>
	/// Permet d'acqu�rir ou de d�finir le uuid du client.
	/// </summary>
	/// <returns>Uuid HEXA</returns>
	std::string getUuid();


private:
	Serveur m_serveur;

	/// <summary>
	/// Repr�sente un parametre URI du serveur � contacter.
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
	/// Repr�sente les vues possibles � afficher.
	/// </summary>
	std::string m_menuAcceuil;
	std::string m_menuConnection;
	std::string m_conversation;

	/// <summary>
	/// Le membre utilisant le client.
	/// </summary>
	Membre m_membreConnecter;


	/// <summary>
	/// Construit une structure de requete pouvant �tre envoyer vers un serveur.
	/// </summary>
	/// <param name="nomRoute">Le nom de la route � contacter.</param>
	/// <param name="data">Le data � envoyer afin que le serveur puisse traiter la demande.</param>
	/// <param name="type">Le type de requete [POST,PUT,GET,DELETE]</param>
	/// <returns>La structure de requete selon la convention.</returns>
	RequeteClient requete(std::string nomRoute, json& data, std::string type);

	/// <summary>
	/// Contacte le serveur selon la structure de requete.
	/// </summary>
	/// <param name="requeteC">La structure repr�sentant la requete � effectuer</param>
	/// <returns>La structure de reponse du serveur.</returns>
	ReponseServeur fetchRequete(RequeteClient& requeteC);
};

