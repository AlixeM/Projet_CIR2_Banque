#include "Customer.hpp"

Client::Client(){}

Client::Client(const int& num_client, std::string&& name, std::string&& surname, std::vector<int>&& vec_compte, std::string&& password) :numclient(num_client), nom(name), prenom(surname), num_compte(vec_compte), mdp(password) {}

std::ostream &operator<<(std::ostream &os, const Client &client) {
  os << "numclient : " << client.numclient<< std::endl;
  os << "nom : " << client.nom << std::endl;
  os << "prenom : " << client.prenom << std::endl;
  for (auto &account : client.num_compte) {
    std::cout << "num_compte : " << account << std::endl;
  }
  os << "mdp : " << client.mdp << std::endl;
  return os;
}



Compte::Compte() {}

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
	for (auto& num : client.num_compte) {
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
	const int num = pt.get<int>("Numclient", 0);
	std::string nom = pt.get<std::string>("Nom");
	std::string prenom = pt.get<std::string>("Prenom");
	std::string mdp = pt.get<std::string>("MDP");
	std::vector<int>num_comptes;

	for (ptree::value_type& num_compte : pt.get_child("Num_comptes")) {
		num_comptes.push_back(num_compte.second.get_value<int>());
	}
	Client client(num, std::move(nom), std::move(prenom), std::move(num_comptes), std::move(mdp));
	return client;
}

Compte extraire_compte(ptree& pt) {
	const int numclient = pt.get<int>("Numclient", 0);
	const int numcompte = pt.get<int>("Numcompte", 0);
	const int type = pt.get<int>("Type");
	std::string nom = pt.get<std::string>("Nom");
	const int solde = pt.get<int>("Solde", 0);
	const int agence = pt.get<int>("Agence");
	Compte compte(numclient, numcompte, type, std::move(nom), solde, agence);
	return compte;
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

