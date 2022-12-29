//
// blocking_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <thread>
#include <chrono>

#include "client.hpp"
#include "socket_tools.hpp"

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

int client(std::string agence,int demande_type)
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

            //write(socket, buffer des données à communiquer)
            boost::asio::write(s, boost::asio::buffer(line));
        }
        else if (demande_type == 2) {
            Client customer(1001, "Tartempion1", "la", { 10000, 10001 }, "123");
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
            //demande à la BDD pour recuperer les nouvelles infos
            std::string line = "Passez les infos plz + les interets plz 19";
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
                Client customer_back(1001, "10", "20", { 2, 30 }, "40");
                std::cout << "Customer sent :" << std::endl << customer_back << std::endl;
                auto line = get_string_from_data(customer_back, 2);
                boost::asio::write(*sock, boost::asio::buffer(line));
            }
            else if (get_data_from_string0(data) == " 2") {
                Client customer = get_data_from_string<Client>(data);
                std::cout << "Customer received :" << std::endl << customer << std::endl;
                /////////////////////////////////////////
                Client customer_back(1001, "10", "20", { 2, 30 }, "40");
                std::cout << "Customer sent :" << std::endl << customer_back << std::endl;
                auto line = get_string_from_data(customer_back, 2);
                boost::asio::write(*sock, boost::asio::buffer(line));
            }
            else if (get_data_from_string0(data) == " 3") {
                std::cout << "demande de transaction recu" << std::endl;

                client("777", 13);

                boost::asio::write(*sock, boost::asio::buffer("Nous avons bien recu votre demande de transaction 3"));
            }
            else if (get_data_from_string0(data) == "13") {
                std::cout << "demande BDD recu" << std::endl;
                boost::asio::write(*sock, boost::asio::buffer("Nous avons bien recu votre demande de BDD 13"));

            }
            else if (get_data_from_string0(data) == " 9") {
                //établi la connexion entre les agences et la BDD
                client("777", 19);
                boost::asio::write(*sock, boost::asio::buffer("message de confirmation 9"));
            }
            else if (get_data_from_string0(data) == "19") {
                //recuperation des infos par la BDD
                //fonction appelé pour envoie dans la BDD
                boost::asio::write(*sock, boost::asio::buffer("message de confirmation 19"/*infos sous forme de vecteur ??? ou plusieurs boost::asio::write ????*/));
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
        //toutes les 30 secondes interroge et rassemble l’ensemble des modifications sur les transactions, situations financières,création de comptes...
        //effectuées dans les agences décentralisées et met à jour sa base de données.
        std::chrono::seconds five_seconds = std::chrono::seconds(5);
        std::this_thread::sleep_for(five_seconds);
        //demande à A1,A2 et A3 les nouvelles infos
        client("1234", 9);
        client("2345", 9);
        client("3333", 9);
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
        a.accept(*sock); //moment où ça ecrit dans l'interface 
        boost::thread t(boost::bind(session, sock));
        color(couleur);

    }
}

int main(int argc, char* argv[])
{
    try
    {
        int demande_type;
        std::thread AgenceA(server, 4, 1234);
        std::thread AgenceB(server, 2, 2345);
        std::thread AgenceC(server, 3, 3333);
        std::thread AgenceBDD(server, 8, 777);
        std::thread BDD(BDD);

        std::string Agence;
        std::cout << "Dans quelle agence êtes-vous ? (A) , (B) ou (C) ";
        std::cin >> Agence;

        if (Agence == "A" || Agence == "a") Agence = "1234";
        else if (Agence == "B" || Agence == "b") Agence = "2345";
        else if (Agence == "C" || Agence == "c") Agence = "3333";
        else std::cout << "cette agence n'exite pas" << std::endl;


        while(Agence == "1234"|| Agence == "2345" || Agence == "3333") {
            color(1);
            std::cout << "Quelle numero de demande voulez-vous faire ?"<<std::endl<<"(1) Compte"<<std::endl<<"(2) Client"<<std::endl<< "(3) Demande de transaction"<<std::endl;
            std::cin >> demande_type;
            std::thread client0(client, Agence,demande_type);
            client0.join();
        }
        if (Agence == "s") {
            AgenceBDD.detach(); 
            AgenceA.detach();
            AgenceB.detach();
            AgenceC.detach();

        }
        else {
            AgenceBDD.join();
            AgenceA.join();
            AgenceB.join();
            AgenceC.join();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}

//Taken from "https://www.boost.org/doc/libs/1_80_0/doc/html/boost_asio/example/cpp11/echo/blocking_tcp_echo_client.cpp" with modifications


