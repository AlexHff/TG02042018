#include "Button.h"

int getclicks(Graph &workg) {
    if (workg.getInterface()->m_bouton_g1.clicked()) {
        return constants::TB_ACTION_LOAD_GRAPH_1;
    }

    if (workg.getInterface()->m_bouton_g2.clicked()) {
        return constants::TB_ACTION_LOAD_GRAPH_2;
    }

    if (workg.getInterface()->m_bouton_g3.clicked()) {
        return constants::TB_ACTION_LOAD_GRAPH_3;
    }

    if (workg.getInterface()->m_bouton_save.clicked()) {
        return constants::TB_ACTION_SAVE;
    }

    return constants::TB_ACTION_NOTHING;
}

void get_buttons_actions(Graph &workg, Graph &g1, Graph &g2, Graph &g3) {
    int message = getclicks(workg);

    if (message == constants::TB_ACTION_LOAD_GRAPH_1) {
        if (workg.getNomFichier() != "graph1.txt") {
            if (workg.getNomFichier() == "graph2.txt") {
                g2 = workg;
            } else {
                g3 = workg;
            }
            workg = g1;
        }
    } else if (message == constants::TB_ACTION_LOAD_GRAPH_2) {
        if (workg.getNomFichier() != "graph2.txt") {
            if (workg.getNomFichier() == "graph1.txt") {
                g1 = workg;
            } else {
                g3 = workg;
            }
            workg = g2;
        }
    } else if (message == constants::TB_ACTION_LOAD_GRAPH_3) {
        if (workg.getNomFichier() != "graph3.txt") {
            if (workg.getNomFichier() == "graph1.txt") {
                g1 = workg;
            } else {
                g2 = workg;
            }
            workg = g3;
        }
    } else if (message == constants::TB_ACTION_SAVE) {
        workg.write_file();
    }
}
