#include "main.h"
#include "wxWidgets.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    Ident *ident = new Ident(wxT("PATHYS BANQUE"));
    ident->Show(true);

    return true;
}