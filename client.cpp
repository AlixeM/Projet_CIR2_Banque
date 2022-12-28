#include "main.h"

Client::Client() {
	numclient = 69420;
	nom = "Jean";
	prenom = "Michel";
	std::vector<int> vec{ 0 };
	num_compte=vec;
	mdp = "squidgame";
}

Client::Client(const int num_client, std::string name, std::string surname, std::vector<int> vec_compte,std::string password) {
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

Compte::Compte(const int num_client, const int num_compte, const int compte_type, std::string name, int argent,const int agency) {
	numclient = num_client;
	numcompte = num_compte;
	type = compte_type;
	nom = name;
	solde = argent;
	agence = agency;
}
Client::Client(ptree pt) {
	numclient = pt.get<int>("Numclient", 0);
	nom = pt.get<std::string>("Nom");
	prenom = pt.get<std::string>("Prenom");
	mdp = pt.get<std::string>("MDP");
	std::vector<int>num_comptes;

	for (ptree::value_type& num_compte : pt.get_child("Num_comptes")) {
		num_comptes.push_back(num_compte.second.get_value<int>());
	}
	num_compte = num_comptes;
}

Compte::Compte(ptree pt) {
	numclient = pt.get<int>("Numclient", 0);
	numcompte = pt.get<int>("Numcompte", 0);
	type = pt.get<int>("Type");
	nom = pt.get<std::string>("Nom");
	solde = pt.get<int>("Solde", 0);
	agence = pt.get<int>("Agence");
}
ptree Client::creer_ptree_client() {
	ptree pt;
	ptree nums_comptes;

	pt.put("Numclient",numclient);
	pt.put("Nom", nom);
	pt.put("Prenom", prenom);
	pt.put("MDP", mdp);
	for (auto& num : num_compte){
		ptree dummy_tree;
		//   dummy_tree.put(account_number.first, account_number.second);
		dummy_tree.put_value(num);
		nums_comptes.push_back({ "", dummy_tree });
	}
	pt.add_child("Num_comptes", nums_comptes);

	return pt;
}

ptree Compte::creer_ptree_compte() {
	ptree pt;
	pt.put("Numclient", numclient);
	pt.put("Numcompte", numcompte);
	pt.put("Type", type);
	pt.put("Nom", nom);
	pt.put("Solde", solde);
	pt.put("Agence", agence);
	return pt;
}

void Client::add_account(int num) {
	num_compte.push_back(num);
}

int Compte::transaction(Compte compte, int montant) {
	if (numclient = compte.numclient) {
		return 0;
	}
	if (solde < montant) {
		return 0;
	}
	else {
		solde -= montant;
		compte.solde += montant;
		return 1;
	}
}

int Compte::paiement(int montant) {
	if (solde < montant) {
		return 0;
	}
	else {
		solde -= montant;
		return 1;
	}
}

void Compte::depot(int montant) {
	solde += montant;
}

int Compte::transfert(Compte compte, int montant) {
	if (numclient != compte.numclient) {
		return 0;
	}
	if (solde < montant) {
		return 0;
	}
	else {
		solde -= montant;
		compte.solde += montant;
		return 1;
	}
}

/*Client transaction(Client client1, Compte compte1, Client client2, Compte compte2, int montant) {
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

}*/
