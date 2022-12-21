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
			cout << "Nom : " << custom.nom << endl;
			cout << "Prenom : " << custom.prenom << endl;
			return custom;
		}
	}
	Client error(0, "Error", "Error", { 0 }, "error");
	return error;
}

Compte recherche_numcompte(ptree& pt, int num) {
	for (ptree::value_type& compte : pt.get_child("Comptes"))
	{
		auto acc = extraire_compte(compte.second);


		if (acc.numcompte == num) {
			std::cout << "Nom : " << acc.nom << std::endl;
			std::cout << "Numéro de compte : " << acc.numcompte << std::endl;
			std::cout << "Solde : " << acc.solde << std::endl;

			return acc;
		}
	}
	Compte error(0, 0, 0, "error", 0, 0);
	return error;
}

int main() {
	Client client1(72,"Jean-Pierre","Mollefesse",{7,12},"jaimelargent");
	Client client2(89, "Robert", "Francis", { 0,38,54 }, "vivegiroud");

	ptree arbre1= creer_ptree_client(client1);
	ptree arbre2= creer_ptree_client(client2);
	ptree pt_comptes;
	pt_comptes.push_back({ "",arbre1 });
	pt_comptes.push_back({ "",arbre2 });
	ecrire_json_client(pt_comptes);
	ptree testlec = lire_json_client();
	Client search = recherche_numclient(testlec,89);
}


