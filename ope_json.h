#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

#include "client.h"


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using std::cout;
using std::endl;
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