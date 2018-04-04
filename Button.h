#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include "grman/grman.h"

class Button
{
    public:
        Button(int _x, int _y, int _w, int _h, std::string _text);
        virtual ~Button();

        int Getx() { return m_x; }
        void Setx(int val) { m_x = val; }
        int Gety() { return m_y; }
        void Sety(int val) { m_y = val; }
        int Getw() { return m_w; }
        void Setw(int val) { m_w = val; }
        int Geth() { return m_h; }
        void Seth(int val) { m_h = val; }
        std::string Gettext() { return m_text; }
        void Settext(std::string val) { m_text = val; }
        bool Getcurstate() { return m_curstate; }
        void Setcurstate(bool val) { m_curstate = val; }
        bool Getprevstate() { return m_prevstate; }
        void Setprevstate(bool val) { m_prevstate = val; }
        bool Gethover() { return m_hover; }
        void Sethover(bool val) { m_hover = val; }

        void update();
        bool isClicked();
        void show();

    protected:

    private:
        int m_x;
        int m_y;
        int m_w;
        int m_h;
        std::string m_text;
        bool m_curstate;
        bool m_prevstate;
        bool m_hover;
};

#endif // BUTTON_H
