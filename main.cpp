#include "main.h"
#include "wxWidgets.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    Simple *simple = new Simple(wxT("PATHYS BANQUE"));
    simple->Show(true);

    Icon *icon = new Icon(wxT("Icon"));
    icon->Show(true);

    return true;
}
