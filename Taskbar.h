#ifndef TASKBAR_H
#define TASKBAR_H

#include <iostream>
#include <string>
#include "grman/grman.h"

class Taskbar
{
    public:
        Taskbar();
        virtual ~Taskbar();
        void show();

    protected:

    private:
        grman::WidgetButton m_g1;
        grman::WidgetButton m_g2;
        grman::WidgetButton m_g3;
        grman::WidgetButton m_connexite;
        grman::WidgetButton m_simu;
        grman::WidgetButton m_differe;
};

#endif // TASKBAR_H
