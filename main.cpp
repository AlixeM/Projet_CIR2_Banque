#include "wx/wxprec.h"
#include "wx/fontdlg.h"
#include "wx/colordlg.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "main.h"

int main() {
	Client client1(72,"jean-Pierre","mollefesse",{7,12},"jaimelargent");
	Client client2(89, "Robert", "Francis", {0,38,54}, "vivegiroud");
	ptree arbre1 = client1.creer_ptree_client();
	ptree arbre2 = client2.creer_ptree_client();
	ptree pt_comptes;
	pt_comptes.push_back({ "",arbre1 });
	pt_comptes.push_back({ "",arbre2 });
	ecrire_json_client(pt_comptes);
	ptree testlec = lire_json_client();
	Client search = recherche_numclient(testlec, 89);
	return 1;
}

//------------------------------------------------------------------------------
//WxWidget
//------------------------------------------------------------------------------

wxString Agence;

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
                EVT_BUTTON(Tran, Frame3::Transaction)
                EVT_BUTTON(Dep, Frame3::Depot)
                EVT_BUTTON(Ret, Frame3::Retrait)
                EVT_BUTTON(Trans, Frame3::Transfert)
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
Frame3::Frame3(const wxString& title, const wxPoint& pos, const wxSize& size,
               long style) : wxFrame(NULL, -1, title, pos, size, style)
{
    SetIcon(wxICON(monicone));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

    wxMenu *menuFichier = new wxMenu;

    menuFichier->Append(App_Quit,"Quitter l'application");
    wxMenuBar *menuBarre = new wxMenuBar();
    menuBarre->Append(menuFichier,("Fichier"));
    SetMenuBar(menuBarre);

    tran = new wxButton(this,Tran,"Transaction", wxPoint(110,60),wxDefaultSize);
    dep = new wxButton(this,Dep,"Depot", wxPoint(110,100),wxDefaultSize);
    ret = new wxButton(this,Ret,"Retrait", wxPoint(110,140),wxDefaultSize);
    trans = new wxButton(this,Trans,"Transfet", wxPoint(110,180),wxDefaultSize);
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
    Frame2 *frame = new Frame2("Pathys Bank test", wxPoint(150, 150), wxSize(480, 380));
    frame->Show();
}
//------------------------------------------------------------------------------
void Frame::OnSubmitUpdate(wxCommandEvent& WXUNUSED(event))
{
    Dialog dialog(NULL,-1,"Choisissez votre agence",Chiffre);
    if ( dialog.ShowModal() == wxID_OK )
    {
        wxString st = "Aucun";
        Chiffre = dialog.GetValue();
        switch(Chiffre)
        {
            case 1 : st = "Listenbourg";
                break;
            case 2 : st = "Lille";
                break;
            case 3 : st = "Londres";
                break;
        }
        Agence = st;
    }
    Close();
    Frame3 *frame = new Frame3("Pathys Bank test3", wxPoint(150, 150), wxSize(480, 380));
    frame->Show();
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
    wxMessageBox("Votre identifiant client est le :","INFORMATION");
    Close();
}


//------------------------------------------------------------------------------
//Frame3 : Actions
//------------------------------------------------------------------------------
void Frame3::Quit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame3::Transaction(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame3::Depot(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame3::Retrait(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
//------------------------------------------------------------------------------
void Frame3::Transfert(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

