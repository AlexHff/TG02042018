/*! \file Regroupe les declarations des fonctions relatives au fonctionnement des boutons sur le côté de la fenêtre */

#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>
#include "grman/grman.h"
#include "graph.h"
#include "constants.h"
#include "Differe.h"


//! Met a jour le texte et la couleur d'un bouton lie a un graphe quand celui-ci est actif
/*!
    \param une reference au graphe actuel
*/
void updateMessages(Graph &workg);

//! Recupere l'etat des boutons dans la marge
/*!
    \param une reference au graphe actuel
    \return une constante correspondant au bouton clique
*/
int getclicks(Graph &workg);

//! gere les boutons dans la marge et leurs actions
/*!
    \param une reference au graphe actuel
    \param une reference au premier graphe
    \param une reference au deuxieme graphe
    \param une reference au troisieme graphe
*/
void get_buttons_actions(Graph &workg, Graph &g1, Graph &g2, Graph &g3);

#endif // BUTTON_H

