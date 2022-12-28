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

#include "Customer.hpp" //a effacer
/*#include "client.h"*/
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
    SetConsoleTextAttribute(console_color, 7);
}
int client(std::string agence, int demande_type)
{
    try
    {
        boost::asio::io_service io_service;
        tcp::socket s(io_service);

        tcp::resolver resolver(io_service);
        boost::asio::connect(s, resolver.resolve({ "127.0.0.1", agence })); //agence = port de l'agence ("1234","2345" ou "3333")

        if (demande_type == 01) {
            Compte customer(1001, 10, 20, "okayyyy", 30, 40);
            //transformation des infos du Customer en un string et affichage du Customer
            auto line = get_string_from_data(customer);
            std::cout << "Customer sent :" << std::endl << customer << std::endl;
            //write(socket, buffer des données à communiquer)
            boost::asio::write(s, boost::asio::buffer(line.c_str(), line.size()));
        }
        else if (demande_type == 2) {
            Client customer(1001, "Tartempion1", "la", { 10000, 10001 }, "123");
            auto line = get_string_from_data(customer);
            std::cout << "Customer sent :" << std::endl << customer << std::endl;
            boost::asio::write(s, boost::asio::buffer(line.c_str(), line.size()));
        }

        //
        char reply[max_size_data];
        boost::system::error_code error;
        size_t length = s.read_some(boost::asio::buffer(reply), error);

        //création du Customer et son affichage
        Client customer_back = get_data_from_string<Client>(reply);
        //std::cout << "Customer received :" << std::endl << customer_back << std::endl;

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

void session(socket_ptr sock)
{
    try
    {
        for (;;)
        {
            char data[max_size_data] = {};

            boost::system::error_code error;
            size_t length = sock->read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.

            Compte customer = get_data_from_string<Compte>(data);
            std::cout << "Customer received :" << std::endl << customer << std::endl;


            Client customer_back(1001, "10", "20", { 2, 30 }, "40");

            //std::cout << "Customer sent :" << std::endl << customer_back << std::endl;

            auto line = get_string_from_data(customer_back);

            boost::asio::write(*sock, boost::asio::buffer(line.c_str(), line.size()));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

void server(int couleur, short port)
{
    boost::asio::io_service io_service;
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    for (;;)
    {
        //std::cout << "ah" << std::endl;
        socket_ptr sock(new tcp::socket(io_service));
        //std::cout << "bh" << std::endl;
        a.accept(*sock); //moment où ça ecrit dans l'interface 
        //std::cout << "ch" << std::endl;
        boost::thread t(boost::bind(session, sock));
        color(couleur);
        //std::cout << "euh" << std::endl;

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

        std::string tmp;

        while (tmp != "s") {
            std::cout << "Envoyer socket a l'agence A , B ou C ? ";
            std::cin >> tmp;

            if (tmp == "A" || tmp == "a") tmp = "1234";
            else if (tmp == "B" || tmp == "b") tmp = "2345";
            else if (tmp == "C" || tmp == "c") tmp = "3333";
            else if (tmp != "s") {
                std::cout << "cette agence n'exite pas" << std::endl;
                tmp = "error";
            }
            if (tmp != "error") {
                std::cout << "Quelle num de demande voulez-vous faire ?";
                std::cin >> demande_type;
                std::thread client0(client, tmp, demande_type);
                client0.join();
            }
        }
        if (tmp == "s") {
            AgenceA.detach();
            AgenceB.detach();
            AgenceC.detach();

        }
        else {
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


