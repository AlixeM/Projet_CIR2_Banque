#include "wx/wxprec.h"
#include "wx/fontdlg.h"
#include "wx/colordlg.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/statline.h"
#endif
#include "main.hpp"
#include "socket.cpp"
#include <future>

int main() {
    /*try
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


        while (Agence == "1234" || Agence == "2345" || Agence == "3333") {
            color(1);
            std::cout << "Quelle numero de demande voulez-vous faire ?" << std::endl << "(1) Compte" << std::endl << "(2) Client" << std::endl << "(3) Demande de transaction" << std::endl;
            std::cin >> demande_type;
            std::thread client0(client, Agence, 21, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"),1,"truc");
            std::future<int> resultat = std::async(client, Agence, 21, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), 1, "truc");
            int valeur = resultat.get();


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
    }*/
    Compte compte1(15, 57, 1, "truc", 500, 2);
    Compte compte2(69, 420, 1, "truc", 300, 2);
    Compte final=compte1.transaction(compte2, 50);
    cout << final.solde << endl;
    cout << compte1.solde << endl;
    compte1.paiement(200);
    cout << compte1.solde << endl;


    return 1;
}


//------------------------------------------------------------------------------
//WxWidget
//------------------------------------------------------------------------------
int nbcompte = 0;

BEGIN_EVENT_TABLE(Frame, wxFrame)
                EVT_MENU(App_Quit,  Frame::OnQuit)
                EVT_MENU(New_client,  Frame::Client)
                EVT_TEXT(TextEdit, Frame::OnTextUpdate)
                EVT_TEXT(MdpEdit, Frame::OnMdpUpdate)
                EVT_BUTTON(Btsubmit, Frame::OnSubmitUpdate)
END_EVENT_TABLE()


BEGIN_EVENT_TABLE(Frame2, wxFrame)
                EVT_MENU(App_Quit,  Frame2::Quit)
                EVT_TEXT(Nomclient, Frame2::Ncli)
                EVT_TEXT(Prenomclient, Frame2::Pcli)
                EVT_TEXT(Adresseclient, Frame2::Acli)
                EVT_TEXT(Mdpclient, Frame2::Mcli)
                EVT_BUTTON(Inscription, Frame2::Submit)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Frame3, wxFrame)
                EVT_MENU(App_Quit,  Frame3::Quit)
                EVT_BUTTON(wxID_ADD, Frame3::OnCreateAccount)
                EVT_BUTTON(wxID_NEW, Frame3::OnNewAccount)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(Frame4, wxFrame)
                EVT_MENU(App_Quit,  Frame4::Quit)
                EVT_BUTTON(Tran, Frame4::Transaction)
                EVT_BUTTON(Dep, Frame4::Depot)
                EVT_BUTTON(Ret, Frame4::Retrait)
                EVT_BUTTON(Trans, Frame4::Transfert)
END_EVENT_TABLE()


IMPLEMENT_APP(Application)

bool Application::OnInit()
{
    Frame *frame = new Frame("Pathys Bank", wxPoint(150, 150), wxSize(480, 360));
    frame->Show();
    return true;
}
//------------------------------------------------------------------------------
Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style) : wxFrame(NULL, -1, title, pos, size, style)
{

    SetIcon(wxICON(monicone));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    wxMenu *menuFichier = new wxMenu;
    menuFichier->Append(New_client,"Nouveau client");
    menuFichier->AppendSeparator();
    menuFichier->Append(App_Quit,"Quitter l'application");
    wxMenuBar *menuBarre = new wxMenuBar();
    menuBarre->Append(menuFichier,("Fichier"));
    SetMenuBar(menuBarre);

    Label = new wxStaticText(this,-1,"Bienvenue chez Pathys banque ! ",wxPoint(115,15), wxSize(-1, 10),wxALIGN_CENTRE);
    Label->SetFont(wxFont(12, wxSWISS , wxNORMAL, wxBOLD, false, "Arial"));

    auto *labelPrenom = new wxStaticText(this, -1, _T("Identifiant :"), wxPoint(110,60));
    ID_client = new wxTextCtrl(this, TextEdit, _T(""), wxPoint(110,80), wxSize(250, wxDefaultSize.GetHeight()));

    auto *mdp = new wxStaticText(this, -1, _T("Mot de passe :"), wxPoint(110,120));
    MDP_client = new wxTextCtrl(this, MdpEdit, _T(""), wxPoint(110,140), wxSize(250, wxDefaultSize.GetHeight()), wxTE_PASSWORD);

    submit = new wxButton(this,Btsubmit,"Connexion", wxPoint(110,180),wxDefaultSize);

    wxBoxSizer *Psizer = new wxBoxSizer( wxVERTICAL );
    Psizer->Add(-1,60);
    SetSizer(Psizer);

    Chiffre = 0;
}

//------------------------------------------------------------------------------
Frame2::Frame2(const wxString& title, const wxPoint& pos, const wxSize& size,
               long style) : wxFrame(NULL, -1, title, pos, size, style)
{

    SetIcon(wxICON(monicone));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    wxMenu *menuFichier = new wxMenu;
    menuFichier->Append(App_Quit,"Quitter l'application");
    wxMenuBar *menuBarre = new wxMenuBar();
    menuBarre->Append(menuFichier,("Fichier"));
    SetMenuBar(menuBarre);

    Label = new wxStaticText(this,-1,"Bienvenue chez Pathys banque ! ",wxPoint(115,15), wxSize(-1, 10),wxALIGN_CENTRE);
    Label->SetFont(wxFont(12, wxSWISS , wxNORMAL, wxBOLD, false, "Arial"));

    auto *nom = new wxStaticText(this, -1, _T("Nom :"), wxPoint(110,40));
    nom_client = new wxTextCtrl(this, Nomclient, _T(""), wxPoint(110,60), wxSize(250, wxDefaultSize.GetHeight()));

    auto *prenom = new wxStaticText(this, -1, _T("Prenom :"), wxPoint(110,90));
    prenom_client = new wxTextCtrl(this, Prenomclient, _T(""), wxPoint(110,110), wxSize(250, wxDefaultSize.GetHeight()));

    auto *adresse = new wxStaticText(this, -1, _T("Adresse :"), wxPoint(110,150));
    adresse_client = new wxTextCtrl(this, Adresseclient, _T(""), wxPoint(110,170), wxSize(250, wxDefaultSize.GetHeight()));

    auto *mdp = new wxStaticText(this, -1, _T("Mot de passe :"), wxPoint(110,210));
    mdp_client = new wxTextCtrl(this, Mdpclient, _T(""), wxPoint(110,230), wxSize(250, wxDefaultSize.GetHeight()), wxTE_PASSWORD);

    submit = new wxButton(this,Inscription,"Inscription", wxPoint(110,270),wxDefaultSize);

}

//------------------------------------------------------------------------------
Frame3::Frame3(const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(NULL, -1, title, pos, size, style)
{
    SetIcon(wxICON(monicone));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    wxMenu *menuFichier = new wxMenu;
    menuFichier->Append(App_Quit,"Quitter l'application");
    wxMenuBar *menuBarre = new wxMenuBar();
    menuBarre->Append(menuFichier,("Fichier"));
    SetMenuBar(menuBarre);

    m_panel1 = new wxPanel(this, wxID_ANY);
    m_panel2 = new wxPanel(this, wxID_ANY);

    wxStaticLine* separator = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL);

    // Création d'un sizer vertical pour aligner le texte et l'icône au milieu du panel gauche
    wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);

    // Création des contrôles de texte pour chaque ligne de texte
    ptree nom = lire_json_client();
    Client client = recherche_numclient(nom,wxGetApp().m_idClient);

    std::string name = client.nom;
    wxString name1 = wxString::Format("Nom : %s", name);
    wxStaticText* nameText = new wxStaticText(m_panel1, wxID_ANY, name1, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    std::string name2 = client.prenom;
    wxString name3 = wxString::Format("Prenom : %s", name2);
    wxStaticText* firstNameText = new wxStaticText(m_panel1, wxID_ANY, name3, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxString id = wxString::Format("Identifiant : %d", wxGetApp().m_idClient);
    wxStaticText* idText = new wxStaticText(m_panel1, wxID_ANY, id, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    //size_t str = client.num_compte.size();
    //wxString nbc = wxString::Format("Nb compte : %d", str);
    //wxStaticText* accountNumberText = new wxStaticText(m_panel1, wxID_ANY, nbc, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);


    // Chargement de l'icône de silhouette
    wxIcon icon(wxICON(monicone2));

// Création de l'icône à partir de l'icône chargée
    wxStaticBitmap* iconBitmap = new wxStaticBitmap(m_panel1, wxID_ANY, icon);

// Ajout du texte et de l'icône au sizer vertical
    vBoxSizer->AddSpacer(20);
    vBoxSizer->Add(iconBitmap, 0, wxALIGN_CENTER | wxALL, 10);
    vBoxSizer->AddSpacer(20);
    vBoxSizer->Add(nameText, 0, wxALIGN_LEFT  | wxALL, 10);
    vBoxSizer->Add(firstNameText, 0, wxALIGN_LEFT  | wxALL, 10);
    vBoxSizer->Add(idText, 0, wxALIGN_LEFT  | wxALL, 10);

    //vBoxSizer->Add(accountNumberText, 0, wxALIGN_LEFT  | wxALL, 10);
    vBoxSizer->AddSpacer(80);

// Ajout du sizer vertical au panel gauche
    m_panel1->SetSizer(vBoxSizer);

// Création du bouton "Ajouter un compte"
    wxButton* addButton = new wxButton(m_panel2, wxID_ADD, "Ajouter un compte",wxPoint(300,180));//


    size_t taillevect = client.num_compte.size();
    ptree button = lire_json_compte();

// Création d'un sizer vertical pour aligner les boutons en colonne sur la droite
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    for (size_t i=0; i<taillevect; i++){
        Compte compte = search_numcompte(button, client.num_compte[i]);
        wxButton* compteButton = new wxButton(m_panel2, wxID_NEW, compte.nom);
        // Ajout du bouton au sizer vertical
        vbox->Add(compteButton, 0, wxALIGN_RIGHT | wxBOTTOM, 5);
    }

// Création d'un sizer principal qui va contenir le sizer vertical et le bouton "addButton"
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

// Ajout du sizer vertical au sizer principal
    mainSizer->Add(vbox, 0, wxALIGN_RIGHT, 0);

// Ajout du bouton "addButton" au sizer principal en dessous du sizer vertical
    mainSizer->Add(addButton, 0, wxALIGN_CENTER | wxALL, 5);

// Ajout du sizer principal au panel droit
    m_panel2->SetSizer(mainSizer);

// Création du sizer horizontal pour ajouter les panels et la ligne de séparation
    m_hBoxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_hBoxSizer->Add(m_panel1, 1, wxEXPAND);
    m_hBoxSizer->Add(separator, 0, wxEXPAND | wxALL, 5);
    m_hBoxSizer->Add(m_panel2, 2, wxEXPAND);

// Centrer le sizer horizontal dans la fenêtre
    wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
    topSizer->Add(m_hBoxSizer, 0, wxALIGN_CENTER | wxALL, 5);
    SetSizer(topSizer);
    SetAutoLayout(true);
    topSizer->SetSizeHints(this);
}

//------------------------------------------------------------------------------
Frame4::Frame4(const wxString& title, const wxPoint& pos, const wxSize& size,
               long style) : wxFrame(NULL, -1, title, pos, size, style)
{
    SetIcon(wxICON(monicone));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    wxMenu *menuFichier = new wxMenu;
    menuFichier->Append(App_Quit,"Quitter l'application");
    wxMenuBar *menuBarre = new wxMenuBar();
    menuBarre->Append(menuFichier,("Fichier"));
    SetMenuBar(menuBarre);

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(topSizer);

    ptree compte = lire_json_compte();
    Compte compte2 = search_name(compte,wxGetApp().NomCompte,wxGetApp().m_idClient);
    int idCompte = compte2.numcompte;
    int solde = compte2.solde;

    wxStaticText *label = new wxStaticText(this, wxID_STATIC, wxString::Format("Numero du compte : %d", idCompte));
    label->SetFont(wxFont(12, wxSWISS , wxNORMAL, wxBOLD, false, "Arial"));
    topSizer->Add(label, 0, wxALIGN_CENTER | wxALL, 5);

    wxStaticText *label2 = new wxStaticText(this, wxID_STATIC, wxString::Format("Solde : %d", solde));
    label2->SetFont(wxFont(8, wxSWISS , wxNORMAL, wxBOLD, false, "Arial"));
    topSizer->Add(label2, 0, wxALIGN_CENTER | wxALL, 5);

    tran = new wxButton(this,Tran,"Transaction", wxPoint(110,60),wxDefaultSize);
    dep = new wxButton(this,Dep,"Depot", wxPoint(110,100),wxDefaultSize);
    ret = new wxButton(this,Ret,"Retrait", wxPoint(110,140),wxDefaultSize);
    trans = new wxButton(this,Trans,"Transfert", wxPoint(110,180),wxDefaultSize);
}

//------------------------------------------------------------------------------
//LA BOÎTE DE DIALOGUE
//------------------------------------------------------------------------------
Dialog::Dialog(wxWindow* parent, wxWindowID id, const wxString& titre, int nb): wxDialog(parent,id,titre,wxDefaultPosition,wxSize(240, 200))
{
    RadioBouton1 = new wxRadioButton(this,-1,"Listenbourg");
    RadioBouton2 = new wxRadioButton(this,-1,"Lille");
    RadioBouton3 = new wxRadioButton(this,-1,"Londres");
    wxButton *MonBouton1 = new wxButton(this,wxID_OK,"Ok");
    wxButton *MonBouton2 = new wxButton(this,wxID_CANCEL,"Annuler");

    wxBoxSizer *sizer1 = new wxBoxSizer( wxVERTICAL );
    sizer1->Add(-1,25);
    sizer1->Add(RadioBouton1,0,wxALL,5);
    sizer1->Add(RadioBouton2,0,wxALL,5);
    sizer1->Add(RadioBouton3,0,wxALL,5);

    wxBoxSizer *sizer2 = new wxBoxSizer( wxHORIZONTAL );
    sizer2->Add(MonBouton1,0,wxBOTTOM | wxLEFT | wxRIGHT ,5);
    sizer2->Add(MonBouton2,0,wxBOTTOM | wxLEFT | wxRIGHT ,5);

    wxBoxSizer *Psizer = new wxBoxSizer( wxVERTICAL );
    Psizer->Add(sizer1,3,wxALIGN_CENTER);
    Psizer->Add(sizer2,1,wxALIGN_CENTER);
    SetSizer(Psizer);
    SetValue(nb);
}
//------------------------------------------------------------------------------
int Dialog::GetValue()
{
    int x = 0;
    if( RadioBouton1->GetValue() ) x = 1;
    if( RadioBouton2->GetValue() ) x = 2;
    if( RadioBouton3->GetValue() ) x = 3;
    return x;
}
//------------------------------------------------------------------------------
void Dialog::SetValue(int x)
{
    switch(x)
    {
        case 1 : RadioBouton1->SetValue(true);
            break;
        case 2 : RadioBouton2->SetValue(true);
            break;
        case 3 : RadioBouton3->SetValue(true);
            break;
    }
}



//------------------------------------------------------------------------------
//Frame1 : Connection
//------------------------------------------------------------------------------
void Frame::OnTextUpdate(wxCommandEvent& WXUNUSED(event))
{
    ID_client->GetValue();
}
//------------------------------------------------------------------------------
void Frame::OnMdpUpdate(wxCommandEvent& WXUNUSED(event))
{
    MDP_client->GetValue();
}
//------------------------------------------------------------------------------
void Frame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame::Client(wxCommandEvent& WXUNUSED(event))
{
    Frame2 *frame = new Frame2("Pathys Bank", wxPoint(150, 150), wxSize(480, 380));
    frame->Show();
}
//------------------------------------------------------------------------------
void Frame::OnSubmitUpdate(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().m_idClient = wxAtoi(ID_client->GetValue());
    std::string mdp_client = MDP_client->GetValue().ToStdString();
    if (mdp_client.empty()||wxGetApp().m_idClient == 0) {
        wxMessageBox("Il y a un champ vide !", "Erreur", wxOK | wxICON_ERROR);
    }
    else {
        //std::thread client0(client, "777", 21, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), wxGetApp().m_idClient, mdp_client);
        //std::future<int> resultat = std::async(client, "777", 21, Compte(0, 0, 0, "def", 0, 0), Client(0, "def", "def", "def", { 0 }, "def"), wxGetApp().m_idClient, mdp_client);
        //client0.join();
        //if(resultat.get() ==1) {
        if(valid_mdp(wxGetApp().m_idClient,mdp_client)==1) {
            Dialog dialog(NULL, -1, "Choisissez votre agence", Chiffre);
    if (dialog.ShowModal() == wxID_OK) {
        int st = 0;
        Chiffre = dialog.GetValue();
        switch (Chiffre) {
            case 1 :
                st = 1;
                break;
            case 2 :
                st = 2;
                break;
            case 3 :
                st = 3;
                break;
        }
        wxGetApp().agence = st;
    }
    Close();
    Frame3* frame = new Frame3("Pathys Bank", wxPoint(150, 150), wxSize(480, 360), wxDEFAULT_FRAME_STYLE);
    frame->Show(true);
    }
    else{
        wxMessageBox("Mot de passe ou identifiant incorrect","ERREUR", wxOK | wxICON_ERROR);
    }
}
}



//------------------------------------------------------------------------------
//Frame2 : Inscription
//------------------------------------------------------------------------------
void Frame2::Quit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame2::Ncli(wxCommandEvent& WXUNUSED(event))
{
    nom_client->GetValue();
}
//------------------------------------------------------------------------------
void Frame2::Pcli(wxCommandEvent& WXUNUSED(event))
{
    prenom_client->GetValue();
}
//------------------------------------------------------------------------------
void Frame2::Acli(wxCommandEvent& WXUNUSED(event))
{
    adresse_client->GetValue();
}
//------------------------------------------------------------------------------
void Frame2::Mcli(wxCommandEvent& WXUNUSED(event))
{
    mdp_client->GetValue();
}
//------------------------------------------------------------------------------
void Frame2::Submit(wxCommandEvent& WXUNUSED(event))
{
    std::string nom = nom_client->GetValue().ToStdString();
    std::string prenom = prenom_client->GetValue().ToStdString();
    std::string adresse = adresse_client->GetValue().ToStdString();
    std::string mdp = mdp_client->GetValue().ToStdString();
    if (mdp.empty()||prenom.empty()||adresse.empty()||nom.empty()) {

    wxMessageBox("Il y a un champ vide !", "Erreur", wxOK | wxICON_ERROR);
    }
    else {
        int num = random_number_client();
        std::vector<int> vect;
        Client client(num, nom, prenom, adresse, vect, mdp);
        //std::thread client0(client, agence, 2, Compte(0, 0, 0, "def", 0, 0), client, wxGetApp().m_idClient, mdp_client);
        //std::future<int> resultat = std::async(client, agence, 2, Compte(0, 0, 0, "def", 0, 0), client, wxGetApp().m_idClient, mdp_client);
        //client0.join();
        //if(resultat.get() ==1) {
        ptree tamere = client.creer_ptree_client();
        add_subclient(tamere);
        ptree tonpere = lire_subclient();
        update_centrale_client(tonpere);

        wxString message = wxString::Format("Votre identifiant client est le : %d", num);
        wxMessageBox(message, "INFORMATION", wxOK | wxICON_INFORMATION, this);
        Close();
    }
}



//------------------------------------------------------------------------------
//Frame3 : Compte
//------------------------------------------------------------------------------
void Frame3::Quit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
wxBoxSizer* vBoxSizer = new wxBoxSizer(wxVERTICAL);
bool firstButton = true;

void Frame3::OnCreateAccount(wxCommandEvent& event) {
    // Incrémenter le compteur de comptes
    nbcompte += 1;

    // Obtenir le nom du compte à partir de l'utilisateur
    wxString name = wxGetTextFromUser("Entrez le nom du compte :", "Nom du compte", "", this);
    std::string name2 = name.ToStdString();



// Afficher la boîte de dialogue de sélection de type de compte
    wxArrayString accountTypes;
    accountTypes.Add("Epargne");
    accountTypes.Add("Courant");
    wxSingleChoiceDialog typeDialog(this, "Choisissez le type de compte", "Type de compte", accountTypes);

    if (typeDialog.ShowModal() == wxID_OK)
    {
        int idCompte = random_number_compte();
        wxGetApp().idCompte = idCompte;
        int typeCompte;
        int solde = 0;

        wxString type = accountTypes[typeDialog.GetSelection()];
        if (type == "Epargne"){
            typeCompte = 2;
        }
        else{
            typeCompte = 1;
        }

        Compte compte(wxGetApp().m_idClient, wxGetApp().idCompte, typeCompte, name2, solde, wxGetApp().agence);
        ptree treecompte = compte.creer_ptree_compte();
        if (wxGetApp().agence == 1){
            add_agence1(treecompte);
        }
        if (wxGetApp().agence == 2){
            add_agence2(treecompte);
        }
        if (wxGetApp().agence == 3){
            add_agence3(treecompte);
        }

        ptree nom = lire_json_client();
        Client client = recherche_numclient(nom,wxGetApp().m_idClient);
        client.add_account(wxGetApp().idCompte);
        ptree truc = client.creer_ptree_client();
        add_subclient(truc);
        ptree machin = lire_subclient();
        update_centrale_client(machin);

        ptree ag1 = lire_agence1();
        ptree ag2 = lire_agence2();
        ptree ag3 = lire_agence3();

        ptree sum = json_assemble(ag1,ag2,ag3);
        update_centrale_compte(sum);

        // Créer le nouveau bouton
        wxButton* accountButton = new wxButton(m_panel2, wxID_NEW, name);
        wxGetApp().NomCompte = name;

        // Ajouter un espace de 20 pixels et le bouton au sizer, si c'est le premier bouton
        if (client.num_compte.size()==0){
            if (firstButton)
            {
                vBoxSizer->AddSpacer(25);
                firstButton = false;
            }
        }

        vBoxSizer->Add(accountButton, 0, wxALIGN_LEFT | wxALL, 5);

        // Mettre à jour le sizer du panel
        m_panel2->SetSizer(vBoxSizer);
        m_panel2->Layout();

        // Connecter l'événement "cliqué" du bouton au gestionnaire d'événements OnNewAccount
        accountButton->Connect(wxID_NEW, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Frame3::OnNewAccount));
    }
}
//------------------------------------------------------------------------------
void Frame3::OnNewAccount(wxCommandEvent& event)
{
    try
    {
        Frame4* frame = new Frame4("Pathys Bank", wxPoint(150, 150), wxSize(320, 360));
        frame->Show(true);
    }
    catch (const std::exception& ex)
    {
        // Afficher un message d'erreur à l'utilisateur
        wxMessageBox(ex.what(), "Erreur", wxOK | wxICON_ERROR);
    }
}


//------------------------------------------------------------------------------
//Frame4 : Actions
//------------------------------------------------------------------------------
void Frame4::Quit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame4::Transaction(wxCommandEvent& WXUNUSED(event))
{
    TransactionDialog dlg(this, -1, "Transaction");
    if (dlg.ShowModal() == wxID_OK)
    {
        // Récupérez les valeurs entrées par l'utilisateur ici.
    }
}
//------------------------------------------------------------------------------
void Frame4::Depot(wxCommandEvent& WXUNUSED(event))
{
    DepotDialog dlg(this, -1, "Depot");
    if (dlg.ShowModal() == wxID_OK)
    {
        // Récupérez les valeurs entrées par l'utilisateur ici.
    }
}
//------------------------------------------------------------------------------
void Frame4::Retrait(wxCommandEvent& WXUNUSED(event))
{
    RetraitDialog dlg(this, -1, "Retrait");
    if (dlg.ShowModal() == wxID_OK)
    {
        // Récupérez les valeurs entrées par l'utilisateur ici.
    }
}
//------------------------------------------------------------------------------
void Frame4::Transfert(wxCommandEvent& WXUNUSED(event))
{
    TransferDialog dlg(this, -1, "Transfert");
    if (dlg.ShowModal() == wxID_OK)
    {
        // Récupérez les valeurs entrées par l'utilisateur ici.
    }
}


//------------------------------------------------------------------------------
//Frame4 : Dialogues
//------------------------------------------------------------------------------
TransactionDialog::TransactionDialog(wxWindow *parent,
                                     wxWindowID id,
                                     const wxString &title,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style)
        : wxDialog(parent, id, title, pos, size, style)
{
    CreateControls();
}

void TransactionDialog::CreateControls() {

    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(topSizer);

    wxBoxSizer *account2Sizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(account2Sizer, 0, wxALIGN_LEFT | wxALL, 5);

    wxStaticText *account2Label = new wxStaticText(this, wxID_STATIC, "Numero du compte recepteur :");
    account2Sizer->Add(account2Label, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_account2Ctrl = new wxTextCtrl(this, wxID_ANY);
    account2Sizer->Add(m_account2Ctrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *amountSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(amountSizer, 0, wxALIGN_LEFT | wxALL, 5);

    wxStaticText *amountLabel = new wxStaticText(this, wxID_STATIC, "Montant :");
    amountSizer->Add(amountLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_amountCtrl = new wxTextCtrl(this, wxID_ANY);
    amountSizer->Add(m_amountCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *okButton = new wxButton(this, wxID_OK, "Envoyer");
    okButton->SetDefault();
    buttonSizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Annuler");
    buttonSizer->Add(cancelButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSize(300, 250);
}


//------------------------------------------------------------------------------
DepotDialog::DepotDialog(wxWindow *parent,
                         wxWindowID id,
                         const wxString &title,
                         const wxPoint &pos,
                         const wxSize &size,
                         long style)
        : wxDialog(parent, id, title, pos, size, style)
{
    CreateControls();
}

void DepotDialog::CreateControls()
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(topSizer);

    wxBoxSizer *amountSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(amountSizer, 0, wxALIGN_LEFT | wxALL, 5);

    wxStaticText *amountLabel = new wxStaticText(this, wxID_STATIC, "Montant a deposer :");
    amountSizer->Add(amountLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_amountCtrl = new wxTextCtrl(this, wxID_ANY);
    amountSizer->Add(m_amountCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *okButton = new wxButton(this, wxID_OK, "Deposer");
    okButton->SetDefault();
    buttonSizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Annuler");
    buttonSizer->Add(cancelButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSize(300, 250);
}


//------------------------------------------------------------------------------
RetraitDialog::RetraitDialog(wxWindow *parent,
                             wxWindowID id,
                             const wxString &title,
                             const wxPoint &pos,
                             const wxSize &size,
                             long style)
        : wxDialog(parent, id, title, pos, size, style)
{
    CreateControls();
}

void RetraitDialog::CreateControls()
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(topSizer);

    wxBoxSizer *amountSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(amountSizer, 0, wxALIGN_LEFT | wxALL, 5);

    wxStaticText *amountLabel = new wxStaticText(this, wxID_STATIC, "Montant a retirer :");
    amountSizer->Add(amountLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_amountCtrl = new wxTextCtrl(this, wxID_ANY);
    amountSizer->Add(m_amountCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *okButton = new wxButton(this, wxID_OK, "Retirer");
    okButton->SetDefault();
    buttonSizer->Add(okButton, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Annuler");
    buttonSizer->Add(cancelButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSize(300, 250);
}


//------------------------------------------------------------------------------
TransferDialog::TransferDialog(wxWindow *parent,
                               wxWindowID id,
                               const wxString &title,
                               const wxPoint &pos,
                               const wxSize &size,
                               long style)
        : wxDialog(parent, id, title, pos, size, style)
{
    CreateControls();
}

void TransferDialog::CreateControls()
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(topSizer);

    wxBoxSizer *accountSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(accountSizer, 0, wxALIGN_LEFT | wxALL, 5);

    wxStaticText *accountLabel = new wxStaticText(this, wxID_STATIC, "Numero de compte recepteur :");
    accountSizer->Add(accountLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_accountCtrl = new wxTextCtrl(this, wxID_ANY);
    accountSizer->Add(m_accountCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *amountSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(amountSizer, 0, wxALIGN_LEFT | wxALL, 5);

    wxStaticText *amountLabel = new wxStaticText(this, wxID_STATIC, "Montant a transferer :");
    amountSizer->Add(amountLabel, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    m_amountCtrl = new wxTextCtrl(this, wxID_ANY);
    amountSizer->Add(m_amountCtrl, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *transferButton = new wxButton(this, wxID_OK, "Transferer");
    transferButton->SetDefault();
    buttonSizer->Add(transferButton, 0, wxALIGN_CENTER | wxALL, 5);

    wxButton *cancelButton = new wxButton(this, wxID_CANCEL, "Annuler");
    buttonSizer->Add(cancelButton, 0, wxALIGN_CENTER | wxALL, 5);

    SetSize(300, 250);
}
