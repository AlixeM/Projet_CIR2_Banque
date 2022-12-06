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


#ifndef PATHYS_CLIENT_H
#define PATHYS_CLIENT_H

#endif //PATHYS_CLIENT_H

class Client {
public :
	int numclient;
	std::string nom;
	std::string prenom;
	std::vector<int> num_compte;
	Client();
	Client(const int& numclient, std::string&& name, std::string&& prenom,std::vector<int> num_compte);
};

class Compte {
	int numclient;
	int numcompte;
	int type;
	int solde;
	int agence;
	Compte();
	Compte(const int& numclient,const int& numcompte, const int& type, const int& solde, const int& agence);
};

ptree creer_ptree_client(const Client& client);

ptree creer_ptree_compte(const Compte& compte);

Client extraire_client(ptree& pt);

Compte extraire_compte(ptree& pt);