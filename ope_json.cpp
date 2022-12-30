#include "main.hpp"

ptree lire_json_client() {
	ptree pt_lecture;
	std::ifstream file_in("../client.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_json_compte() {
	ptree pt_lecture;
	std::ifstream file_in("../compte.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
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
	Client error(0, "Error", "Error","Error",Verr, "error");
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
	std::ifstream file_in("../agence1.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_agence2() {
	ptree pt_lecture;
	std::ifstream file_in("../agence2.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_agence3() {
	ptree pt_lecture;
	std::ifstream file_in("../agence3.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

ptree lire_subclient() {
	ptree pt_lecture;
	std::ifstream file_in("../subclient.json");
	read_json(file_in, pt_lecture);
	file_in.close();
	return pt_lecture;
}

void add_agence1(ptree pt) {
	ptree pt_save = lire_agence1();
	ptree groupe_acc;
	groupe_acc.push_back({ "",pt });
	for (ptree::value_type& compte: pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		groupe_acc.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", groupe_acc);
	std::ofstream file_out("../agence1.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_agence2(ptree pt) {
	ptree pt_save = lire_agence2();
	ptree groupe_acc;
	groupe_acc.push_back({ "",pt });
	for (ptree::value_type& compte : pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		groupe_acc.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", groupe_acc);
	std::ofstream file_out("../agence2.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_agence3(ptree pt) {
	ptree pt_save = lire_agence3();
	ptree groupe_acc;
	groupe_acc.push_back({ "",pt });
	for (ptree::value_type& compte : pt_save.get_child("Comptes")) {
		Compte acc(compte.second);
		ptree arbre = acc.creer_ptree_compte();
		groupe_acc.push_back({ "", arbre });
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Comptes", groupe_acc);
	std::ofstream file_out("../agence3.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void add_subclient(ptree pt) {
	ptree pt_save = lire_subclient();
	Client nouv(pt);
	ptree groupe_custom;
	groupe_custom.push_back({ "",pt });
	for (ptree::value_type& custom : pt_save.get_child("Clients")) {
		Client client(custom.second);
		if (client.numclient != nouv.numclient) {
			ptree arbre = client.creer_ptree_client();
			groupe_custom.push_back({ "", arbre });
		}
	}
	//on réécrit ensuite le json avec les nouvelles données ajoutées aux anciennes
	ptree pt_write;
	pt_write.add_child("Clients", groupe_custom);
	std::ofstream file_out("../subclient.json");
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
	std::ofstream file_out("../compte.json");
	write_json(file_out, pt_write);
	file_out.close();
}

void update_centrale_client(ptree pt) {
	std::ofstream file_out("../client.json");
	write_json(file_out, pt);
	file_out.close();
}

int random_number_client() {
	srand((unsigned int) time(0));
	ptree verif = lire_json_client();
	int validation = 1;
	int val = 0;
	while (validation != 0) {
		validation = 1;
		val = rand() % 10000 + 1;
		for (ptree::value_type& client : verif.get_child("Clients"))
		{
			Client custom(client.second);
			if (val == custom.numclient) {
				validation += 1;
			}
		}
		validation -= 1;
	}
	return val;
}

int random_number_compte() {
	srand((unsigned int)time(0));
	ptree verif = lire_json_client();
	int validation = 1;
	int val = 0;
	while (validation != 0) {
		validation = 1;
		val = rand() % 10000 + 1;
		for (ptree::value_type& compte : verif.get_child("Clients"))
		{
			Compte acc(compte.second);
			if (val == acc.numcompte) {
				validation += 1;
			}
		}
		validation -= 1;
	}
	return val;
}

void tri_json() {
	ptree root = lire_json_compte();
	ptree agency1;
	ptree agency2;
	ptree agency3;
	for (ptree::value_type& compte : root.get_child("Comptes"))
	{
		Compte acc(compte.second);
		ptree arbre=acc.creer_ptree_compte();
		if(acc.agence==1){
			agency1.push_back({ "",arbre });
		}
		if (acc.agence = 2) {
			agency2.push_back({ "",arbre });
		}
		if (acc.agence = 3) {
			agency3.push_back({ "",arbre });
		}
	}
	tri1(agency1);
	tri2(agency2);
	tri3(agency3);
}

void tri1(ptree pt) {
	ptree pt1;
	pt1.add_child("Comptes", pt);
	std::ofstream file_out("../agence1.json");
	write_json(file_out, pt1);
	file_out.close();
}

void tri2(ptree pt) {
	ptree pt2;
	pt2.add_child("Comptes", pt);
	std::ofstream file_out("../agence2.json");
	write_json(file_out, pt2);
	file_out.close();
}

void tri3(ptree pt) {
	ptree pt3;
	pt3.add_child("Comptes", pt);
	std::ofstream file_out("../agence3.json");
	write_json(file_out, pt3);
	file_out.close();
}