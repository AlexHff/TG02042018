#include "grman/grman.h"
#include <iostream>

#include "graph.h"
#include "Button.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// 3 graphes au total et un graphe "actif"
    Graph g1, g2, g3, workg;
    g1.read_file("graph1.txt");
    g2.read_file("graph2.txt");
    g3.read_file("graph3.txt");

    workg=g3;
    workg.kVertexConnex();
    //workg.test();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        workg.update();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        get_buttons_actions(workg, g1, g2, g3);
    }

    /// enregistrement du graphe
   // workg.write_file();

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN()

