#include "client.h"

creer_ptree_client(const Client& client) {
	ptree pt;
	ptree nums_comptes;

	pt.put("Numclient", client.numclient);
	pt.put("Nom", client.nom);
	pt.put("Prenom", client.prenom);
	for (auto& num : client.num_compte){
		ptree dummy_tree;
		//   dummy_tree.put(account_number.first, account_number.second);
		dummy_tree.put_value(num);
		nums_comptes.push_back({ "", dummy_tree });
	}
	pt.add_child("Num_comptes", nums_comptes);

	return pt;
}

Client extraire_client(ptree& pt) {
	int num= pt.get<int>("Numclient", 0);
	std::string nom = pt.get<std::string>("Nom");
	std::string prenom = pt.get<std::string>("Prenom");
	std::vector<int>num_comptes;

	for (ptree::value_type& num_compte : pt.get_child("Num_comptes")) {
		num_comptes.push_back(num_compte.second.get_value<int>());
	}
	Client client(num, std::move(nom), std::move(prenom), std::move(num_comptes));
	return client;
}