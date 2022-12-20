#include "client.h"

Client::Client() {
	numclient = 69420;
	nom = "Jean";
	prenom = "Michel";
	num_compte = { 0 };
	mdp = "squidgame";
}

Client::Client(const int& num_client, std::string&& name, std::string&& surname, std::vector<int> vec_compte,std::string password) {
	numclient = num_client;
	nom = name;
	prenom = surname;
	num_compte = vec_compte;
	mdp = password;
}

Compte::Compte() {
	numclient = 69420;
	numcompte = 80085;
	type = 1;
	solde = 0;
	agence = 1;
}

Compte::Compte(const int& num_client, const int& num_compte, const int& compte_type, std::string&& name, const int& argent, const int& agency) {
	numclient = num_client;
	numcompte = num_compte;
	type = compte_type;
	nom = name;
	solde = argent;
	agence = agency;
}

ptree creer_ptree_client(const Client& client) {
	ptree pt;
	ptree nums_comptes;

	pt.put("Numclient", client.numclient);
	pt.put("Nom", client.nom);
	pt.put("Prenom", client.prenom);
	pt.put("MDP", client.mdp);
	for (auto& num : client.num_compte){
		ptree dummy_tree;
		//   dummy_tree.put(account_number.first, account_number.second);
		dummy_tree.put_value(num);
		nums_comptes.push_back({ "", dummy_tree });
	}
	pt.add_child("Num_comptes", nums_comptes);

	return pt;
}

ptree creer_ptree_compte(const Compte& compte) {
	ptree pt;
	pt.put("Numclient", compte.numclient);
	pt.put("Numcompte", compte.numcompte);
	pt.put("Type", compte.type);
	pt.put("Nom", compte.nom);
	pt.put("Solde", compte.solde);
	pt.put("Agence", compte.agence);
	return pt;
}

Client extraire_client(ptree& pt) {
	int num= pt.get<int>("Numclient", 0);
	std::string nom = pt.get<std::string>("Nom");
	std::string prenom = pt.get<std::string>("Prenom");
	std::string mdp = pt.get<std::string>("MDP");
	std::vector<int>num_comptes;

	for (ptree::value_type& num_compte : pt.get_child("Num_comptes")) {
		num_comptes.push_back(num_compte.second.get_value<int>());
	}
	Client client(num, std::move(nom), std::move(prenom), std::move(num_comptes),std::move(mdp));
	return client;
}

Compte extraire_compte(ptree& pt) {
	int numclient = pt.get<int>("Numclient", 0);
	int numcompte = pt.get<int>("Numcompte", 0);
	int type = pt.get<int>("Type");
	std::string nom = pt.get<std::string>("Nom");
	int solde = pt.get<int>("Solde", 0);
	int agence = pt.get<int>("Agence");

	Compte compte(numclient, numcompte, type, std::move(nom), solde, agence);
	return compte;
}

Client transaction(Client client1, Compte compte1, Client client2, Compte compte2, int montant) {
	compte1.solde -= montant;
	compte2.solde += montant;

}

Client retrait_depot(Client client1, Compte compte1, int type, int montant) {
	if (type == 0) {
		compte1.solde -= montant;
	}
	else if (type == 0) {
		compte1.solde += montant;
	}

}