//
// blocking_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "socket_tools.cpp"

//Taken from "https://www.boost.org/doc/libs/1_80_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_server.cpp" with modifications

using boost::asio::ip::tcp;

const int max_length = 1024;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void color(int a) {
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, a);
    if (a == 4) std::cout << "----------------Agence A----------------" << std::endl;
    else if (a == 2) std::cout << "----------------Agence B----------------" << std::endl;
    else if (a == 3) std::cout << "----------------Agence C----------------" << std::endl;
    else if (a == 8) std::cout << "------------------BDD-------------------" << std::endl;
    else if (a == 1) std::cout << "-----------------Client-----------------" << std::endl;
    SetConsoleTextAttribute(console_color, 7);
}

int client(std::string agence,int demande_type, Compte compteC, Client clientC,int intI,std::string stringS)
{
    try
    {
        boost::asio::io_service io_service;
        tcp::socket s(io_service);

        tcp::resolver resolver(io_service);
        boost::asio::connect(s, resolver.resolve({ "127.0.0.1", agence })); //agence = port de l'agence ("1234","2345" ou "3333") ("777 pour l'agence centrale)

        if (demande_type == 1) {
            Compte customer(1001, 10, 20, "okayyyy", 30, 40);
            //transformation des infos du Customer en un string et affichage du Customer
            auto line = get_string_from_data(customer,demande_type);
            //std::cout << "Customer sent :" << std::endl << customer << std::endl;

            //write(socket, buffer des donn?es ? communiquer)
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 2) {
            Client customer(1001, "Tartempion1", "la","truc",{ 10000, 10001 }, "123");
            auto line = get_string_from_data(customer,demande_type);
            //std::cout << "Customer sent :" << std::endl << customer << std::endl;
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 3) {
            std::string line = "Demande Transaction 3";
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 13) {
            std::string line = "Demande Transaction BDD 13";
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 9) {
            //demande aux agences d'envoyer les nouvelles infos + envoyer siganl pour les interet 
            std::string line = "Passez les infos plz + les interets plz 9";
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 19) {
            //demande ? la BDD pour recuperer les nouvelles infos
            std::string line = "Passez les infos plz + les interets plz 19";
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 21) {
            //int valid_mdp(int numclient, std::string mdp);
            std::string line = std::to_string(intI) + " " + stringS + " 21";
            std::cout << line << std::endl;
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 22) {
            auto line = get_string_from_data(clientC, demande_type);
            boost::asio::write(s, boost::asio::buffer(line));
        }

        //REPONSE
        char reply[max_size_data];
        boost::system::error_code error;
        size_t length = s.read_some(boost::asio::buffer(reply), error);

        if (get_data_from_string0(reply) == " 1") {
            Compte customer_back = get_data_from_string<Compte>(reply);
            std::cout << "Customer received :" << std::endl << customer_back << std::endl; 
        }
        else if (get_data_from_string0(reply) == " 2") { 
            Client customer_back = get_data_from_string<Client>(reply);
            std::cout << "Customer received :" << std::endl << customer_back << std::endl;
        }
        else if (get_data_from_string0(reply) == " 3") {
            std::cout << reply << std::endl;
        }
        else if (get_data_from_string0(reply) == "13") {
            std::cout << reply << std::endl;
        }
        else if (get_data_from_string0(reply) == "9") {

        }
        else if (get_data_from_string0(reply) == "21") {
            std::string tmp = reply;
            std::string tmp2 = tmp.substr(0, 1);
            return stoi(tmp2);
        }
        else if (get_data_from_string0(reply) == " 2") {
            Client customer_back = get_data_from_string<Client>(reply);
            
        }
        else std::cout << "error : " << std::endl << get_data_from_string0(reply) << std::endl;

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

void session(socket_ptr sock)
{
    try{
        for (;;){

            char data[max_size_data] = {};
            boost::system::error_code error;
            size_t length = sock->read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.
            

            if (get_data_from_string0(data) == " 1") {
                Compte customer = get_data_from_string<Compte>(data);
                std::cout << "Customer received :" << std::endl << customer << std::endl;
                ///////////////////////////////////////////////////
                Client customer_back(1001, "10", "20","truc" ,{ 2, 30 }, "40");
                std::cout << "Customer sent :" << std::endl << customer_back << std::endl;
                auto line = get_string_from_data(customer_back, 2);
                boost::asio::write(*sock, boost::asio::buffer(line));
            }
            else if (get_data_from_string0(data) == " 2") {
                Client customer = get_data_from_string<Client>(data);
                std::cout << "Customer received :" << std::endl << customer << std::endl;
                /////////////////////////////////////////
                Client customer_back(1001, "10", "20", "truc", { 2, 30 }, "40");
                std::cout << "Customer sent :" << std::endl << customer_back << std::endl;
                auto line = get_string_from_data(customer_back, 2);
                boost::asio::write(*sock, boost::asio::buffer(line));
            }
            else if (get_data_from_string0(data) == " 3") {
                std::cout << "demande de transaction recu" << std::endl;

                client("777", 13, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), 0, "def");

                boost::asio::write(*sock, boost::asio::buffer("Nous avons bien recu votre demande de transaction 3"));
            }
            else if (get_data_from_string0(data) == "13") {
                std::cout << "demande BDD recu" << std::endl;
                boost::asio::write(*sock, boost::asio::buffer("Nous avons bien recu votre demande de BDD 13"));

            }
            else if (get_data_from_string0(data) == " 9") {
                //?tabli la connexion entre les agences et la BDD
                client("777", 19, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), 0, "def");
                boost::asio::write(*sock, boost::asio::buffer("message de confirmation 9"));
            }
            else if (get_data_from_string0(data) == "19") {
                //recuperation des infos par la BDD
                //fonction appel? pour envoie dans la BDD
                boost::asio::write(*sock, boost::asio::buffer("message de confirmation 19"/*infos sous forme de vecteur ??? ou plusieurs boost::asio::write ????*/));
            }
            else if (get_data_from_string0(data) == "21") {
                std::vector<std::string> tmp2 = separerString(data);
                int tmp3 = stoi(tmp2[0]);
                std::string tmp4 = tmp2[1];
                int tmp5 = 1; //valid_mdp(tmp3, tmp4);
                std::string retour = std::to_string(tmp5) +"21";
                boost::asio::write(*sock, boost::asio::buffer(retour));
            }

            else std::cout << "Customer received :" << std::endl << get_data_from_string0(data) << std::endl;

        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}
void BDD() {
    for (;;) {
        //toutes les 30 secondes interroge et rassemble l?ensemble des modifications sur les transactions, situations financi?res,cr?ation de comptes...
        //effectu?es dans les agences d?centralis?es et met ? jour sa base de donn?es.
        std::chrono::seconds five_seconds = std::chrono::seconds(5);
        std::this_thread::sleep_for(five_seconds);
        //demande ? A1,A2 et A3 les nouvelles infos
        //client("1234", 9, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), 0, "def");
        //client("2345", 9, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), 0, "def");
       // client("3333", 9, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), 0, "def");
       //interet();
    }
}

void server(int couleur, short port)
{
    boost::asio::io_service io_service;
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));

    for (;;)
    {
        socket_ptr sock(new tcp::socket(io_service));
        //add boucle pour BDD pour savoir si socket recu ou non piur pas bloquer programme pour la boucle 5s
        a.accept(*sock); //moment o? ?a ecrit dans l'interface 
        boost::thread t(boost::bind(session, sock));
        color(couleur);

    }
}


//Taken from "https://www.boost.org/doc/libs/1_80_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_client.cpp" with modifications


