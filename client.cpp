#include "main.hpp"

Client::Client() {
	numclient = 69420;
	nom = "Jean";
	prenom = "Michel";
	adresse = "221B Baker Street";
	std::vector<int> vec;
	num_compte=vec;
	mdp = "squidgame";
}

Client::Client(const int num_client, std::string name, std::string surname,std::string home, std::vector<int> vec_compte,std::string password) {
	numclient = num_client;
	nom = name;
	prenom = surname;
	adresse = home;
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
	nom = pt.get<std::string>("Nom","erreur");
	prenom = pt.get<std::string>("Prenom","erreur");
	adresse = pt.get<std::string>("Adresse","erreur");
	mdp = pt.get<std::string>("MDP","erreur");
	std::vector<int>num_comptes;

	for (ptree::value_type& num_compte : pt.get_child("Num_comptes")) {
		num_comptes.push_back(num_compte.second.get_value<int>());
	}
	num_compte = num_comptes;
}

Compte::Compte(ptree pt) {
	numclient = pt.get<int>("Numclient", 0);
	numcompte = pt.get<int>("Numcompte", 0);
	type = pt.get<int>("Type",0);
	nom = pt.get<std::string>("Nom","erreur");
	solde = pt.get<int>("Solde", 0);
	agence = pt.get<int>("Agence",0);
}
ptree Client::creer_ptree_client() {
	ptree pt;
	ptree nums_comptes;

	pt.put("Numclient",numclient);
	pt.put("Nom", nom);
	pt.put("Prenom", prenom);
	pt.put("Adresse", adresse);
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

Compte Compte::transaction(Compte compte, int montant) {
	if (numclient != compte.numclient) {
		if (solde > montant) {
			solde -= montant;
			compte.solde += montant;
		}
	}
	
	return compte;
}


int Compte::paiement(int montant) {
	if (solde > montant) {
		solde -= montant;
		return 1;
	}
	return 0;
}

void Compte::depot(int montant) {
	solde += montant;
}

Compte Compte::transfert(Compte compte, int montant) {
	if (numclient == compte.numclient) {
		if (solde > montant) {
			solde -= montant;
			compte.solde += montant;

		}
	}
	return compte;
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
	os << "numclient : " << client.numclient << std::endl;
	os << "nom : " << client.nom << std::endl;
	os << "prenom : " << client.prenom << std::endl;
	for (auto& account : client.num_compte) {
		std::cout << "num_compte : " << account << std::endl;
	}
	os << "mdp : " << client.mdp << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Compte& compte) {
	os << "numclient : " << compte.numclient << std::endl;
	os << "numcompte : " << compte.numcompte << std::endl;
	os << "type : " << compte.type << std::endl;
	os << "nom : " << compte.nom << std::endl;
	os << "solde : " << compte.solde << std::endl;
	os << "agence : " << compte.agence << std::endl;
	return os;
}
