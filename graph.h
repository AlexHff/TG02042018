#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/**************************************************************
    Ici sont proposées 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Arête ou Arc)
            Graph (=Graphe)

    Les arêtes et les sommets et le graphe qu'ils constituent
    "travaillent" étroitement ensemble : pour cette raison les
    Vertex et Edge se déclarent amis (friend) de Graph pour que
    ce dernier puisse librement accéder aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent êtres complétées. Il est également possible
    de les dériver mais il est malheureusement assez difficile
    de dériver le "triplet" des 3 classes en maintenant des relations
    cohérentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute préférable, si possible,
    de "customiser" ces classes de base directement, sans héritage.

    Le modèle proposé permet de représenter un graphe orienté éventuellement
    pondéré, les arcs portent une ou des informations supplémentaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse être assez facilement
    lue et écrite en fichier, et bénéficie d'une bonne lisibilité en cas de bugs...

    Chaque arc possède 2 attributs principaux (en plus de son éventuelle pondération)
        -> m_from (indice du sommet de départ de l'arc )
        -> m_to (indice du sommet d'arrivée de l'arc )

    Chaque sommet possède 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : accès aux prédécesseurs)
        -> m_out (liste des indices des arcs partant du sommet : accès aux successeurs)

    Cependant le problème des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entité (un arc et/ou un sommet sont enlevés du graphe) alors :

    - Soit il faut reprendre toute la numérotation pour "boucher le trou"
      (par exemple on a supprimé le sommet n°4, le sommet n°5 devient le 4, 6 devient 5 etc...)
      ce qui pose des problèmes de stabilité et de cohérence, et une difficulté à ré-introduire
      le(s) même(s) élément supprimé (au même indice)

    - Soit on admet que la numérotation des sommets et arcs n'est pas contigue, càd qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La numérotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet à des indices arbitraires (pas forcément contigus)

    C'est cette 2ème approche qui est proposée ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra être attentif au fait que par rapport à un simple vecteur, le parcours des éléments
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours à itérateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'intérêt se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associée à chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non représentés à l'écran
    Imaginons par exemple qu'on doive générer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas représenter graphiquement ces 1000 graphes, et les
    interfaces pèsent lourd en ressource, avec cette organisation on est libre de réserver ou
    pas une interface de présentation associée aux datas (découplage données/interface)

***********************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <stack>
#include <array>
#include <list>

#include "grman/grman.h"
#include "constants.h"

/***************************************************
                    VERTEX
****************************************************/

class VertexInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        /*** VALUE ***/
        // Un slider de visualisation/modification de la valeur du sommet
        grman::WidgetVSlider m_slider_value;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_value;

        /*** POPULATION ***/
        // Un slider de visualisation/modification de la pop du sommet
        grman::WidgetVSlider m_slider_pop;

        // Un label de visualisation de la valeur du sommet
        grman::WidgetText m_label_pop;

        /*** IMG ***/
        // Une image de "remplissage"
        grman::WidgetImage m_img;

        /*** IDX ***/
        // Un label indiquant l'index du sommet
        grman::WidgetText m_label_idx;

        // Une boite pour le label précédent
        grman::WidgetText m_box_label_idx;

    public :
        void setBgCol(int val) {m_top_box.set_bg_color(val); }
        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};


class Vertex
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

    private :
        /// liste des indices des sommets arrivant au sommet : accès aux prédécesseurs
        std::vector<int> m_in;

        /// liste des indices des sommets partant du sommet : accès aux successeurs
        std::vector<int> m_out;

        /// coef In -> "mange"
        double m_coefIn;
        /// coef Out -> "est mangé"
        double m_coefOut;

        /// population
        int m_population;

        /// compteur incrémentation pop
        double m_cptPop;

        /// booleen pour desactiver les sommets
        bool m_isVertex;


        /// groupe d'appartenance pour la forte connexite
        int m_group;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne précédente est en gros équivalent à la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:
        std::shared_ptr<VertexInterface> getInterface() { return m_interface; }
        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Vertex (double coefIn=0, double coefOut=0, int population=0, VertexInterface *interface=nullptr) :
            m_coefIn(coefIn), m_coefOut(coefOut), m_population(population), m_isVertex(true), m_cptPop(0), m_interface(interface)  {  }

        /// Vertex étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
        int getPopulation() { return m_population; }

};



/***************************************************
                    EDGE
****************************************************/

class EdgeInterface
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Edge;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de réglage associés
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        EdgeInterface(Vertex& from, Vertex& to);
};


class Edge
{
    // Les (methodes des) classes amies pourront accéder
    // directement aux attributs (y compris privés)
    friend class Graph;
    friend class EdgeInterface;

    private :
        /// indice du sommet de départ de l'arc
        int m_from;

        /// indice du sommet d'arrivée de l'arc
        int m_to;

        /// poids de l'arc
        double m_weight;

        /// booleen pour desactiver les arcs
        bool m_isEdge;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<EdgeInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }

        /// Edge étant géré par Graph ce sera la méthode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'implémentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
};




/***************************************************
                    GRAPH
****************************************************/

class GraphInterface
{
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de déclarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le paramétrer ( voir l'implémentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajoutés les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajoutés des boutons de contrôle etc...
        grman::WidgetBox m_tool_box;

        // A compléter éventuellement par des widgets de décoration ou
        // d'édition (boutons ajouter/enlever ...)

    public :

        // Le constructeur met en place les éléments de l'interface
        // voir l'implémentation dans le .cpp
        GraphInterface(int x, int y, int w, int h);

        // wrapper pour les boutons
        grman::WidgetBox m_boite_boutons;

        // bouton pour charger le graphe 1
        grman::WidgetButton m_bouton_g1;
        grman::WidgetText m_bouton_g1_label;

        // bouton pour charger le graphe 2
        grman::WidgetButton m_bouton_g2;
        grman::WidgetText m_bouton_g2_label;

        // bouton pour charger le graphe 3
        grman::WidgetButton m_bouton_g3;
        grman::WidgetText m_bouton_g3_label;

        // bouton pour sauvegarder le graphe actuel
        grman::WidgetButton m_bouton_save;
        grman::WidgetText m_bouton_save_label;

        // bouton pour lancer la simulation temporelle
        grman::WidgetButton m_bouton_simu;
        grman::WidgetText m_bouton_simu_label;

        // bouton pour lancer la simulation differee
        grman::WidgetButton m_bouton_diff;
        grman::WidgetText m_bouton_diff_label;

        // bouton pour afficher la forte connexite
        grman::WidgetButton m_bouton_connex;
        grman::WidgetText m_bouton_connex_label;


};


class Graph
{
    private :

        /// La "liste" des arêtes
        std::map<int, Edge> m_edges;

        /// La liste des sommets
        std::map<int, Vertex> m_vertices;

        /// le POINTEUR sur l'interface associée, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        /// nom du fichier
        std::string m_nomFichier;

        bool m_afficheConnexite = false;
        bool m_simu_temp = false;

    public:
        std::string getNomFichier() {return m_nomFichier; }
        std::shared_ptr<GraphInterface> getInterface() {return m_interface;}
        /// Les constructeurs sont à compléter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface)  {  }

        void add_interfaced_vertex(int idx, double coefIn, double coefOut, int pop, int x, int y, std::string pic_name="", int pic_idx=0 );
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        /// chargement des fichiers
        void read_file(const std::string& nom_fichier);

        /// enregistrement des fichiers
        void write_file();

        /// methode pour la detection des composantes fortement connexes
        void fort_connexe();

        /// implémentation de la liste des indices des arcs arrivant au sommet
        void findIn();

        /// implémentation de la liste des indices des arcs sortant du sommet
        void findOut();

        /// creation d'un stack contenant tous les sommets dans un ordre particulier pour l'algorithme de Kosaraju
        void fillOrder(int i, bool visited[], std::stack<int> &Stack);

        /// inversion de toutes les aretes du graph pour l'algorithme de Kosaraju
        Graph getTranspose();

        /// implémentation dfs
        void dfs(int v, bool visited[], int k, int col);

        void bfs(int v, unsigned int &visitedVertices);

        /// k-sommet-connexite
        void kVertexConnex();

        /// trouver les différentes combinaisons
        void recu(std::vector<std::vector<int>> &allComponents, std::vector<int> &tab, int j, int k, int nb);

        /// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
        void update();

        /// Permet de mettre à jour la population de tous les sommets
        void update_pop();

        /// Calcul de K, capacité de portage de l'environnement
        double calcul_sommeKIn(int to);
        double calcul_sommeKOut(int from);

        /// Permet de chercher le poids de l'arete formé par les 2 sommets (s'il existe, 0 sinon)
        double findWeight(int from, int to);

        bool getAfficheConnexite() { return m_afficheConnexite; }
        void setAfficheConnexite(bool val) { m_afficheConnexite = val; }

        void invertSimu() { m_simu_temp = !m_simu_temp; }
        void resetColors();

        std::map<int, Vertex> getVertices() { return m_vertices; }
};


#endif // GRAPH_H_INCLUDED
