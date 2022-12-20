#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#include "client.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

ptree lire_json_client();
ptree lire_json_compte();

void ecrire_json_client(ptree& pt);

void ecrire_json_compte(ptree& pt);

Client recherche_numclient(ptree& pt, int num);

Compte recherche_numcompte(ptree& pt, int num);