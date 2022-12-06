#include "main.h"
#include "wxWidgets.h"

bool Mybank::OnInit()
{
    Mybank *frame = new Mybank("Ma première application",wxPoint(150, 150), wxSize(480, 360));
    frame->Show(true);
    return true;
}
