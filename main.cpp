#include "main.h"
#include "wxWidgets.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Simple *simple = new Simple(wxT("PATHYS BANQUE"));
    simple->Show(true);

    return true;
}