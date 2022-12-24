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
	Client(const int& numclient, std::string&& name, std::string&& prenom, std::vector<int>&& num_compte, std::string&& password);
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
	Compte(const int& numclient, const int& numcompte, const int& type, std::string&& name, const int& solde, const int& agence);
};

ptree creer_ptree_client(const Client& client);

ptree creer_ptree_compte(const Compte& compte);

Client extraire_client(ptree& pt);

Compte extraire_compte(ptree& pt);

ptree lire_json_client();

ptree lire_json_compte();

void ecrire_json_client(ptree& pt);

void ecrire_json_compte(ptree& pt);

Client recherche_numclient(ptree& pt, int num);

Compte search_numcompte(ptree& pt, int num);

int valid_mdp(int numclient, std::string mdp);

