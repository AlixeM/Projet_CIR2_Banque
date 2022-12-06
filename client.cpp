#include "client.h"

creer_ptree_client(const Client& client) {
	ptree pt;

	pt.put("Numclient", client.numclient);
	pt.put("Nom", client.nom);
	pt.put("Prenom", client.prenom);

	return pt;
}

Client extraire_client(ptree& pt) {
	pt.get<int>("Numclient", 0);
	std::string nom = pt.get("Nom");
	std::string prenom = pt.get("Prenom");
}