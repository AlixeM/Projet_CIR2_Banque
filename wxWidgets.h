#ifndef PATHYS_WXWIDGETS_H
#define PATHYS_WXWIDGETS_H

#endif //PATHYS_WXWIDGETS_H
#include <wx/wx.h>

class TMyFrame : public wxFrame
{
public:
    TMyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,
             long style = wxDEFAULT_FRAME_STYLE);
    void OnQuit(wxCommandEvent& event);
    void OnChgTitre(wxCommandEvent& event);
private:
    wxButton *MonBouton;
    wxButton *MonBouton2;

DECLARE_EVENT_TABLE()
};