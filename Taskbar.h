#ifndef TASKBAR_H
#define TASKBAR_H

#include <iostream>
#include <string>
#include "Button.h"

class Taskbar
{
    public:
        Taskbar();
        virtual ~Taskbar();

    protected:

    private:
        Button * m_connexite;
        Button * m_G1;
        Button * m_G2;
        Button * m_G3;
        Button * m_simu;
        Button * m_differe;
};

#endif // TASKBAR_H
