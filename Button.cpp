#include "Button.h"

void updateMessages(Graph &workg) {
    workg.getInterface()->m_bouton_g1_label.set_message("Graphe 1");
    workg.getInterface()->m_bouton_g2_label.set_message("Graphe 2");
    workg.getInterface()->m_bouton_g3_label.set_message("Graphe 3");

    if (workg.getNomFichier() == "graph1.txt") {
        workg.getInterface()->m_bouton_g1_label.set_message("ACTIF 1");
        workg.getInterface()->m_bouton_g1.set_bg_color(VERTFLUOSOMBRE);
    }

    if (workg.getNomFichier() == "graph2.txt") {
        workg.getInterface()->m_bouton_g2_label.set_message("ACTIF 2");
        workg.getInterface()->m_bouton_g2.set_bg_color(VERTFLUOSOMBRE);
    }

    if (workg.getNomFichier() == "graph3.txt") {
        workg.getInterface()->m_bouton_g3_label.set_message("ACTIF 3");
        workg.getInterface()->m_bouton_g3.set_bg_color(VERTFLUOSOMBRE);
    }
}

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

    if (workg.getInterface()->m_bouton_simu.clicked()) {
        return constants::TB_ACTION_SIMU;
    }

    if (workg.getInterface()->m_bouton_diff.clicked()) {
        return constants::TB_ACTION_DIFF;
    }

    if (workg.getInterface()->m_bouton_connex.clicked()) {
        return constants::TB_ACTION_CONNEX;
    }

    return constants::TB_ACTION_NOTHING;
}

void get_buttons_actions(Graph &workg, Graph &g1, Graph &g2, Graph &g3) {
    int message = getclicks(workg);
    updateMessages(workg);
    /// Chargement du graphe 1
    if (message == constants::TB_ACTION_LOAD_GRAPH_1) {
        if (workg.getNomFichier() != "graph1.txt") {
            if (workg.getNomFichier() == "graph2.txt") {
                g2 = workg;
            } else {
                g3 = workg;
            }
            workg = g1;
        }
    }
    /// Chargement du graphe 2
    else if (message == constants::TB_ACTION_LOAD_GRAPH_2) {
        if (workg.getNomFichier() != "graph2.txt") {
            if (workg.getNomFichier() == "graph1.txt") {
                g1 = workg;
            } else {
                g3 = workg;
            }
            workg = g2;
        }
    }
    /// Chargement du graphe 3
    else if (message == constants::TB_ACTION_LOAD_GRAPH_3) {
        if (workg.getNomFichier() != "graph3.txt") {
            if (workg.getNomFichier() == "graph1.txt") {
                g1 = workg;
            } else {
                g2 = workg;
            }
            workg = g3;
        }
    }
    /// Sauvegarde du graphe actuel dans le fichier texte associe
    else if (message == constants::TB_ACTION_SAVE) {
        workg.write_file();
    }

    /// Lancer la simulation
    else if (message == constants::TB_ACTION_SIMU) {

    }

    /// Simulation differee
    else if (message == constants::TB_ACTION_DIFF) {

    }

    /// Afficher les composantes connexes
    else if (message == constants::TB_ACTION_CONNEX) {

    }
}

