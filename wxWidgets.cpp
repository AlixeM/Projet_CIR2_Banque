#include "wxWidgets.h"

#define ID_APP_QUIT 1
#define ID_CHG_TITRE 2

BEGIN_EVENT_TABLE(TMyFrame, wxFrame)
                EVT_BUTTON(ID_APP_QUIT,  TMyFrame::OnQuit)
                EVT_BUTTON(ID_CHG_TITRE,  TMyFrame::OnChgTitre)
END_EVENT_TABLE()

TMyFrame::TMyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
                   long style) : wxFrame(NULL, -1, title, pos, size, style)
{
    SetIcon(wxICON(monicone));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    MonBouton = new wxButton(this,ID_CHG_TITRE,"Chgt Titre", wxPoint(20,20),
                             wxDefaultSize);
    MonBouton2 = new wxButton(this,ID_APP_QUIT,"Quitter", wxPoint(20,60),
                              wxDefaultSize);
}