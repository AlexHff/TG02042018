#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du r�pertoire o� se trouvent les images � charger
    grman::set_pictures_path("pics");

    /// 3 graphes au total et un graphe "actif"
    Graph g1, g2, g3, workg;
    g1.read_file("graph1.txt");
    g2.read_file("graph2.txt");
    g3.read_file("graph3.txt");

    workg=g1;
    workg.fort_connexe();

    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement � des frameworks plus avanc�s )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les m�thodes d'update des objets qui comportent des widgets
        workg.update();

        if(key[KEY_SPACE])
            workg.fort_connexe();

        /// Mise � jour g�n�rale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();
    }

    /// enregistrement du graphe
    workg.write_file();

    grman::fermer_allegro();

    return 0;
}
END_OF_MAIN()

