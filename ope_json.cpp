#include "ope_json.h"

ptree lire_json_client() {
	ptree pt_lecture;
	std::ifstream file_in("client.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_json_compte() {
	ptree pt_lecture;
	std::ifstream file_in("compte.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

void ecrire_json_client(ptree& pt) {
	//la fonction ne sert qu'à écrire dans le json, on modifie les arbres ailleurs
	ptree pt_write;
	pt_write.add_child("Clients", pt);
	std::ofstream file_out("client.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void ecrire_json_compte(ptree& pt) {
	//la fonction ne sert qu'à écrire dans le json, on modifie les arbres ailleurs
	ptree pt_write;
	pt_write.add_child("Comptes", pt);
	std::ofstream file_out("compte.json");
	write_json(file_out, pt_write);
	file_out.close();
}

Client recherche_numclient(ptree& pt, int num) {
	for (ptree::value_type& client : pt.get_child("Clients"))
	{
		auto custom = extraire_client(client.second);

		
		if (custom.numclient == num) {
			std::cout << custom << std::endl;
			return custom;
		}
	}
}

Compte recherche_numcompte(ptree& pt, int num) {
	for (ptree::value_type& compte : pt.get_child("Comptes"))
	{
		auto acc = extraire_compte(compte.second);


		if (acc.numcompte == num) {
			std::cout << acc << std::endl;
			return acc;
		}
	}
}


