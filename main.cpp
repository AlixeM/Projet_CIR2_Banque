#include "main.h"

int main() {
	Client client1(72,"jean-Pierre","mollefesse",{7,12},"jaimelargent");
	Client client2(89, "Robert", "Francis", {0,38,54}, "vivegiroud");
	ptree arbre1 = client1.creer_ptree_client();
	ptree arbre2 = client2.creer_ptree_client();
	ptree pt_comptes;
	pt_comptes.push_back({ "",arbre1 });
	pt_comptes.push_back({ "",arbre2 });
	ecrire_json_client(pt_comptes);
	ptree testlec = lire_json_client();
	Client search = recherche_numclient(testlec, 89);
	return 1;
}

