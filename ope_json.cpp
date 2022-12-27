#include "main.h"

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

void add_json_client(ptree pt) {
	//on ajoute à l'arbre en paramètre les données déjà présentes sur le json
	ptree pt_save = lire_json_client();
	for (ptree::value_type& client : pt_save.get_child("Clients")) {
		Client custom(client.second);
		ptree arbre = custom.creer_ptree_client();
		pt.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Clients", pt);
	std::ofstream file_out("client.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_json_compte(ptree pt) {
	//on ajoute à l'arbre en paramètre les données déjà présentes sur le json
	ptree pt_save = lire_json_compte();
	for (ptree::value_type& compte : pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		pt.push_back({ "",arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", pt);
	std::ofstream file_out("compte.json");
	write_json(file_out, pt_write);
	file_out.close();
}

Client recherche_numclient(ptree pt, int num) {
	for (ptree::value_type& client : pt.get_child("Clients"))
	{
		Client custom(client.second);

		
		if (custom.numclient == num) {
			cout << "Nom : " << custom.nom << endl;
			cout << "Prenom : " << custom.prenom << endl;
			return custom;
		}
	}
	std::vector<int> Verr;
	Verr.push_back(0);
	Client error(0, "Error", "Error", { 0 }, "error");
	return error;
}

Compte search_numcompte(ptree pt, int num) {
	for (ptree::value_type& compte : pt.get_child("Comptes"))
	{
		Compte acc(compte.second);


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

int valid_mdp(int numclient, std::string mdp) {
	ptree pt = lire_json_client();
	Client connect = recherche_numclient(pt,numclient);
	if (connect.mdp == mdp) {
		return 1;
	}
	else { return 0; }
}

ptree lire_agence1() {
	ptree pt_lecture;
	std::ifstream file_in("agence1.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_agence2() {
	ptree pt_lecture;
	std::ifstream file_in("agence2.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_agence3() {
	ptree pt_lecture;
	std::ifstream file_in("agence3.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_subclient() {
	ptree pt_lecture;
	std::ifstream file_in("subclient.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

void add_agence1(ptree pt) {
	ptree pt_save = lire_agence1();
	for (ptree::value_type& compte: pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		pt.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", pt);
	std::ofstream file_out("agence1.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_agence2(ptree pt) {
	ptree pt_save = lire_agence2();
	for (ptree::value_type& compte : pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		pt.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", pt);
	std::ofstream file_out("agence2.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_agence3(ptree pt) {
	ptree pt_save = lire_agence3();
	for (ptree::value_type& compte : pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		pt.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", pt);
	std::ofstream file_out("agence3.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_subclient(ptree pt) {
	ptree pt_save = lire_subclient();
	for (ptree::value_type& compte : pt_save.get_child("Clients")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		pt.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Clients", pt);
	std::ofstream file_out("subclient.json");
	write_json(file_out, pt_write);
	file_out.close();
}

ptree json_assemble(ptree pt1, ptree pt2, ptree pt3) {
	ptree sumpt;
	for (ptree::value_type& compte : pt1.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		sumpt.push_back({ "", arbre });
	}
	for (ptree::value_type& compte : pt2.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		sumpt.push_back({ "", arbre });
	}
	for (ptree::value_type& compte : pt3.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		sumpt.push_back({ "", arbre });
	}
	return sumpt;
}

void update_centrale_compte(ptree pt) {
	ptree pt_write;
	pt_write.add_child("Comptes", pt);
	std::ofstream file_out("compte.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void update_centrale_client(ptree pt) {
	ptree pt_write;
	pt_write.add_child("Clients", pt);
	std::ofstream file_out("client.json");
	write_json(file_out, pt_write);
	file_out.close();
}

