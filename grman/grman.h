#ifndef GRMAN_H_INCLUDED
#define GRMAN_H_INCLUDED

/// Graphic Manager is a collection of functions and globals
/// that acts as a glue between your C++ app and Allegro
/// Call grman::init(); once at startup

#include <allegro.h>

#include <string>


#include "grman_couleurs.h"
#include "coords.h"

namespace grman
{



/// Constantes

/// Variables globales : visibles partout où grman.h est inclus

// La couleur de fond effective utilisee
extern int page_color;

// Le buffer sur lequel tout est dessine
extern BITMAP *page;

// La frame associee pour les widgets
extern Frame page_frame;

// Gestion des widget : avec quel widget la souris interagit ?
class Widget;
extern Widget *gui_over;
extern Widget *gui_last_over;
extern Widget *gui_focus;
extern Widget *gui_leave;


/// Les globales suivantes necessitent un appel a rafraichir_clavier_souris
/// en debut de boucle d'interaction pour être mises a jour a chaque tour de boucle

// La key_last appuyee depuis le dernier tour de boucle
// '\0' si aucun bouton appuye au dernier tour de boucle
extern char key_last;

extern Coords mouse_pos;


// Le clic souris depuis le dernier tour de boucle
// s'utilise comme mouse_b mais contrairement a mouse_b
// n'est valable que pendant un tour de boucle (pas de repetition)
// mouse_click&1 pour clic gauche, mouse_click&2 pour clic droit
extern int mouse_click;

// Le relâchement du clic souris depuis le dernier tour de boucle
// detecte le passage de l'etat enfonce a l'etat relâche
// n'est valable que pendant un tour de boucle (pas de repetition)
// mouse_unclick&1 pour clic gauche, mouse_unclick&2 pour clic droit
extern int mouse_unclick;

// Même principe que key mais detecte les transitions (presse<->non presse)
// valable pendant un seul tour de boucle (pas de repetition)
// exemple : if (key_unpress[KEY_RIGHT]) printf("touche droite relachee !\n");
extern int key_press[KEY_MAX];
extern int key_unpress[KEY_MAX];

// Deplacement relatif de la souris depuis le dernier tour de boucle
extern int mouse_click_x;
extern int mouse_click_y;

extern int mouse_move_x;
extern int mouse_move_y;

extern int mouse_click;

/// Gestion des ressources image (fichiers images et BITMAP chargees)
unsigned get_picture_nb(std::string name);
BITMAP *get_picture(std::string pic_name);
void show_picture(BITMAP *dest, std::string file_name, int x, int y, unsigned idx=0);
void set_pictures_path(std::string path_name);

/// A appeler une fois en fin de boucle de jeu
void mettre_a_jour();

/// Lancement et fermeture services Allegro

// A appeler une fois et une seule en debut de main (apres les declarations)
void init();

// Pour liberer le buffer et fermer tous les services
// pas indispensable : la fin du programme ferme et libere tout automatiquement
void fermer_allegro();


/// Buffer et sorties graphiques

// Efface le buffer (utilise page_color)
// A appeler une fois dans la boucle d'interaction
// avant de redessiner le dessin (et eventuellement
// autre chose apres)
void buf_effacer_page();

// Affiche la page effectivement a l'ecran
// A appeler une fois dans la boucle d'interaction
// A LA FIN JUSTE AVANT rest(10);
void buf_afficher_page();


/// Entrees clavier/souris

// un appel a rafraichir_clavier_souris doit être fait
// en debut de boucle d'interaction pour mettre a jour les globales
void rafraichir_clavier_souris();


/// Auxiliaires : complements aux fonctions graphiques allegro

void thick_line(BITMAP *bmp, int x1, int y1, int x2, int y2, int thickness, int color);

}

/************************************************
            A CORRIGER
*************************************************/

/// Cette inclusion en fin de header parce que widget depend de grman
/// Ceci est evitable (et a eviter) en re-factorisant le projet et les dependance...
#include "widget.h"


#endif // GRMAN_H_INCLUDED
