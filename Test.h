
namespace Test {
	int inputOutputJson();
}



// Asserts testinputOutput
/*
*
* 

 Ajout des membre m1,m2,m3 et m4 //////////////////////////////////////////////////

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"vign","prenom":"raph","relations":{},"uuid":"vigrap1645498531164549853141"}

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"eponge","prenom":"bob","relations":{},"uuid":"epobob1645498531164549853134"}

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"doe","prenom":"john","relations":{},"uuid":"doejoh1645498531164549853124"}

{"courriel":"","date":1645498531,"mdp":"","messages":{},"nom":"doll","prenom":"jane","relations":{},"uuid":"doljan1645498531164549853166"}

 Ajout des relations avec m2,m3,m4 pour m1 ///////////////////////////////////////////

{"relationUuid":"epobob1645498531164549853134","uuid":"vigrap1645498531164549853141"}

{"relationUuid":"doejoh1645498531164549853124","uuid":"vigrap1645498531164549853141"}

 DEBUT Scale test relations //////////////////////////////

 IN:
{"membreUuid":"vigrap1645498531164549853141"}

 OUT:
["epobob1645498531164549853134","doejoh1645498531164549853124"]

 FIN Scale test relations ///////////////////////////////

{"relationUuid":"doljan1645498531164549853166","uuid":"vigrap1645498531164549853141"}

 Integrity test relations /////////////////////////////////////////////////////////////

 IN:
{"membreUuid":"vigrap1645498531164549853141"}

 OUT:
["epobob1645498531164549853134","doejoh1645498531164549853124","doljan1645498531164549853166"]

 Inter-relation: relation de m2,m3,m4 //////////////////////

 IN:
{"membreUuid":"epobob1645498531164549853134"}

 OUT:
["vigrap1645498531164549853141"]

 IN:
{"membreUuid":"doejoh1645498531164549853124"}

 OUT:
["vigrap1645498531164549853141"]

 IN:
{"membreUuid":"doljan1645498531164549853166"}

 OUT:
["vigrap1645498531164549853141"]

 Envoit des messages par m1 -> mN /////////////////////////////////////////////////

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 IN MOCK: vigrap1645498531164549853141epobob1645498531164549853134: {"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}

 OUT: [{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN RQST: {"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}

 IN MOCK: vigrap1645498531164549853141doejoh1645498531164549853124: {"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}

 OUT: [{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}]

 IN RQST: {"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}

 IN MOCK: vigrap1645498531164549853141doljan1645498531164549853166: {"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}

 OUT: [{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]

 Lecture des messages pour m1m2,m1m3,m1m4 ///////////////////////////

 IN:
{"cible":"epobob1645498531164549853134","source":"vigrap1645498531164549853141"}

 OUT:
[{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN:
{"cible":"vigrap1645498531164549853141","source":"epobob1645498531164549853134"}

 OUT:
[{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}]

 IN:
{"cible":"doejoh1645498531164549853124","source":"vigrap1645498531164549853141"}

 OUT:
[{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}]

 IN:
{"cible":"vigrap1645498531164549853141","source":"doejoh1645498531164549853124"}

 OUT:
[{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}]

 IN:
{"cible":"doljan1645498531164549853166","source":"vigrap1645498531164549853141"}

 OUT:
[{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]

 IN:
{"cible":"vigrap1645498531164549853141","source":"doljan1645498531164549853166"}

 OUT:
[{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]

Requete get tout les messages de m1

 IN:
0

 OUT:
[[{"cible":"epobob1645498531164549853134","date":1645498532,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498533,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498534,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"},{"cible":"epobob1645498531164549853134","date":1645498535,"source":"vigrap1645498531164549853141","texte":"Hello M2 !!!"}],[{"cible":"doejoh1645498531164549853124","date":1645498536,"source":"vigrap1645498531164549853141","texte":"Hello M3 !!!"}],[{"cible":"doljan1645498531164549853166","date":1645498537,"source":"vigrap1645498531164549853141","texte":"Hello M4 !!!"}]]
* 
* **/