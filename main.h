#pragma once
#ifndef PATHYS_MAIN_H
#define PATHYS_MAIN_H

#endif //PATHYS_MAIN_H



#include <wx/wx.h>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <random>

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
    std::string adresse;
	Client();
	Client(const int num_client, std::string name, std::string surname, std::string home, std::vector<int> vec_compte, std::string password);
	Client(ptree pt);
	void add_account(int num);
	ptree creer_ptree_client();
	
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

int random_number_compte();

int random_number_client();


//------------------------------------------------------------------------------
//WxWIDGET
//------------------------------------------------------------------------------
class Application : public wxApp
{
public:
    virtual bool OnInit();
};

//------------------------------------------------------------------------------
class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size,
          long style = wxDEFAULT_FRAME_STYLE);
private:
    wxStaticText *Label;
    wxTextCtrl *ID_client;
    wxTextCtrl *MDP_client;
    wxButton *submit;
    int Chiffre;
    void OnQuit(wxCommandEvent& event);
    void Client(wxCommandEvent& event);
    void OnTextUpdate(wxCommandEvent& event);
    void OnMdpUpdate(wxCommandEvent& event);
    void OnSubmitUpdate(wxCommandEvent& event);
    enum
    {
        App_Quit = 1,
        New_client,
        TextEdit,
        MdpEdit,
        Btsubmit,
    };

    DECLARE_EVENT_TABLE()
};

//------------------------------------------------------------------------------

class Frame2 : public wxFrame
{
public:
    Frame2(const wxString& title, const wxPoint& pos, const wxSize& size,
           long style = wxDEFAULT_FRAME_STYLE);
private:
    wxStaticText *Label;
    wxTextCtrl *nom_client;
    wxTextCtrl *prenom_client;
    wxTextCtrl *adresse_client;
    wxTextCtrl *mdp_client;
    wxButton *submit;
    void Quit(wxCommandEvent& event);
    void Ncli(wxCommandEvent& event);
    void Pcli(wxCommandEvent& event);
    void Acli(wxCommandEvent& event);
    void Mcli(wxCommandEvent& event);
    void Submit(wxCommandEvent& event);
    enum
    {
        App_Quit = 1,
        Nomclient,
        Prenomclient,
        Adresseclient,
        Mdpclient,
        Inscription,
    };

    DECLARE_EVENT_TABLE()
};
//------------------------------------------------------------------------------

class Frame3 : public wxFrame
{
public:
    Frame3(const wxString& title, const wxPoint& pos, const wxSize& size,
           long style = wxDEFAULT_FRAME_STYLE);
private:
    wxButton *tran;
    wxButton *dep;
    wxButton *ret;
    wxButton *trans;
    void Quit(wxCommandEvent& event);
    void Transaction(wxCommandEvent& event);
    void Depot(wxCommandEvent& event);
    void Retrait(wxCommandEvent& event);
    void Transfert(wxCommandEvent& event);
    enum
    {
        App_Quit = 1,
        Tran,
        Dep,
        Ret,
        Trans,
    };

    DECLARE_EVENT_TABLE()
};

//------------------------------------------------------------------------------
class Dialog : public wxDialog
{
public:
    Dialog(wxWindow* parent, wxWindowID id, const wxString& title, int nb = 0);
    int GetValue();
    void SetValue(int);
private:
    wxRadioButton *RadioBouton1;
    wxRadioButton *RadioBouton2;
    wxRadioButton *RadioBouton3;
    wxString Agence;
};

