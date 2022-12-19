#include "main.h"

IMPLEMENT_APP(TMyApp)

bool TMyApp::OnInit()
{
    TMyFrame *frame = new TMyFrame("Pathys bank",wxPoint(150, 150), wxSize(480, 360));
    frame->Show(true);
    return true;
}