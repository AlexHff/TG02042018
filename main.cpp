#include "grman/grman.h"
#include <iostream>

#include "graph.h"

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

    workg=g1;
    workg.fort_connexe();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        workg.update();

        if(key[KEY_SPACE])
            workg.fort_connexe();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    /// enregistrement du graphe
    workg.write_file();

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN()

