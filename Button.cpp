#include "Button.h"

Button::Button(int _x, int _y, int _w, int _h, std::string _text)
{
    m_x = _x;
    m_y = _y;
    m_w = _w;
    m_h = _h;
    m_text = _text;
    m_curstate = false;
    m_prevstate = false;
    m_hover = false;
}

Button::~Button()
{
    //dtor
}

void Button::update() {
    // update hover state
    if (mouse_x > m_x && mouse_x < m_x + m_w && mouse_y > m_y && mouse_y < m_y + m_h) {
        m_hover = true;
    } else {
        m_hover = false;
    }

    // update clicstate

    // save the previous click state
    m_prevstate = m_curstate;
    // get the new one
    m_curstate = (mouse_b&1);
}

bool Button::isClicked() {
    /* button has been clicked if :
     *  1. the mouse button is currently being held down
     *  2. AND the mouse button was not previously being held down
     *  3. AND the button is being hovered by the cursor
    */
    return (m_curstate && !m_prevstate && m_hover);
}

void Button::show() {
    std::cout << "Affichage du bouton " << m_text << std::endl;
    //rect(page, 0, 0, 10, 10, makecol(255, 255, 255));
}
