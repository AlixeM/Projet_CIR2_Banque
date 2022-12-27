#pragma once
#ifndef PATHYS_MAIN_H
#define PATHYS_MAIN_H

#endif //PATHYS_MAIN_H



#include <wx/wx.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::cout;
using std::endl;

class Client {
public:
	int numclient;
	std::string nom;
	std::string prenom;
	std::vector<int> num_compte;
	std::string mdp;
	Client();
	Client(const int num_client, std::string name, std::string surname, std::vector<int> vec_compte, std::string password);
	Client(ptree pt);
	ptree creer_ptree_client();
	void ajout_compte(Compte compte);
};

class Compte {
public:
	int numclient;
	int numcompte;
	std::string nom;
	int type;
	int solde;
	int agence;
	Compte();
	Compte(const int num_client, const int num_compte, const int compte_type, std::string name,int argent, const int agency);
	Compte(ptree pt);
	ptree creer_ptree_compte();
	int transaction(Compte compte,int montant);
	int paiement(int montant);
	void depot(int montant);
	int transfert(Compte compte,int montant);
};

ptree lire_json_client();

ptree lire_json_compte();

ptree lire_agence1();

ptree lire_agence2();

ptree lire_agence3();

ptree lire_subclient();

ptree json_assemble(ptree pt1, ptree pt2, ptree pt3);

void add_agence1(ptree pt);

void add_agence2(ptree pt);

void add_agence3(ptree pt);

void add_subclient(ptree pt);

void add_json_client(ptree pt);

void add_json_compte(ptree pt);

Client recherche_numclient(ptree pt, int num);

Compte search_numcompte(ptree pt, int num);

int valid_mdp(int numclient, std::string mdp);

void update_centrale_compte(ptree pt);

void update_centrale_client(ptree pt);


