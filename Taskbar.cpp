#include "Taskbar.h"

Taskbar::Taskbar()
{
    m_connexite = new Button(30, 40, 20, 20, "CONNEX");
    m_G1 = new Button(30, 80, 20, 20, "G2");
    m_G2 = new Button(30, 120, 20, 20, "G2");
    m_G3 = new Button(30, 160, 20, 20, "G3");
    m_simu = new Button(30, 200, 20, 20, "SIM");
    m_differe = new Button(30, 240, 20, 20, "DIFF");
}

Taskbar::~Taskbar()
{
    //dtor
}
