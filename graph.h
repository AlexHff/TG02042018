#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Misc.h"

/**************************************************************
    Ici sont proposees 3 classes fondamentales
            Vertex (=Sommet)
            Edge (=Arête ou Arc)
            Graph (=Graphe)

    Les arêtes et les sommets et le graphe qu'ils constituent
    "travaillent" etroitement ensemble : pour cette raison les
    Vertex et Edge se declarent amis (friend) de Graph pour que
    ce dernier puisse librement acceder aux membres (y compris
    protected ou private) de Vertex et Edge.

    Ces Classes peuvent êtres completees. Il est egalement possible
    de les deriver mais il est malheureusement assez difficile
    de deriver le "triplet" des 3 classes en maintenant des relations
    coherentes ( rechercher "c++ class covariance" et "c++ parallel inheritance"
    pour commencer .. ). Il est donc sans doute preferable, si possible,
    de "customiser" ces classes de base directement, sans heritage.

    Le modele propose permet de representer un graphe oriente eventuellement
    pondere, les arcs portent une ou des informations supplementaire(s).
    Les relations/navigations Arcs -> Sommets et Sommets -> Arcs se font
    dans les 2 sens et utilisent des INDICES et NON PAS DES ADRESSES (pointeurs)
    de telle sorte que la topologie du graphe puisse être assez facilement
    lue et ecrite en fichier, et beneficie d'une bonne lisibilite en cas de bugs...

    Chaque arc possede 2 attributs principaux (en plus de son eventuelle ponderation)
        -> m_from (indice du sommet de depart de l'arc )
        -> m_to (indice du sommet d'arrivee de l'arc )

    Chaque sommet possede 2 liste d'arcs (en plus de ses attributs "internes", marquages...)
        -> m_in (liste des indices des arcs arrivant au sommet : acces aux predecesseurs)
        -> m_out (liste des indices des arcs partant du sommet : acces aux successeurs)

    Cependant le probleme des indices (par rapport aux pointeurs) et qu'en cas
    de destruction d'une entite (un arc et/ou un sommet sont enleves du graphe) alors :

    - Soit il faut reprendre toute la numerotation pour "boucher le trou"
      (par exemple on a supprime le sommet n°4, le sommet n°5 devient le 4, 6 devient 5 etc...)
      ce qui pose des problemes de stabilite et de coherence, et une difficulte a re-introduire
      le(s) même(s) element supprime (au même indice)

    - Soit on admet que la numerotation des sommets et arcs n'est pas contigue, cad qu'il
      peut y avoir des "trous" : sommets 0 1 5 7 8, pas de sommets 2 ni 3 ni 4 ni 6. La numerotation
      est stable mais on ne peut plus utiliser un simple vecteur pour ranger la liste de tous
      les arcs et tous les sommets aux indices correspondants, on peut utiliser une map
      qui associe un objet arc ou sommet a des indices arbitraires (pas forcement contigus)

    C'est cette 2eme approche qui est proposee ici : dans la classe graphe vous trouverez
        -> map<int, Edge>   m_edges
        -> map<int, Vertex> m_vertices    (le pluriel de vertex est vertices)

    Il faudra être attentif au fait que par rapport a un simple vecteur, le parcours des elements
    ne pourra PAS se faire avec un simple for (int i=0; i<m_edges.size(); ++i) ...m_edges[i]...
    et que les parcours a iterateur ne donneront pas directement des Edge ou des Vertex
    mais des pairs, l'objet d'interêt se trouvant dans "second" ("first" contenant l'indice)
                for (auto &it = m_edges.begin(); it!=m_edges.end(); ++it) ...it->second...
    ou bien     for (auto &e : m_edges) ...e.second...

    Il n'est pas obligatoire d'utiliser ces classes pour le projet, vous pouvez faire les votres

    Au niveau de l'interface, on dissocie une classe interface associee a chaque classe fondamentale
    de telle sorte qu'il soit possible de travailler avec des graphes non representes a l'ecran
    Imaginons par exemple qu'on doive generer 1000 permutations de graphes pour tester des
    combinaisons, on ne souhaite pas representer graphiquement ces 1000 graphes, et les
    interfaces pesent lourd en ressource, avec cette organisation on est libre de reserver ou
    pas une interface de presentation associee aux datas (decouplage donnees/interface)

***********************************************************************************************/

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <fstream>
#include <stack>
#include <queue>
#include <array>
#include <list>

#include "grman/grman.h"
#include "constants.h"

/***************************************************
                    VERTEX
****************************************************/

class VertexInterface
{
    // Les (methodes des) classes amies pourront acceder
    // directement aux attributs (y compris prives)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de declarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le parametrer ( voir l'implementation du constructeur dans le .cpp )

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

        // Une boite pour le label precedent
        grman::WidgetText m_box_label_idx;

        /*** Button DELETE ***/
        grman::WidgetButton m_bouton_delete;
        grman::WidgetText m_bouton_label_delete;

        /*** Button ADD EDGE ***/
        grman::WidgetButton m_bouton_addEdge;
        grman::WidgetText m_bouton_label_addEdge;

    public :
        void setBgCol(int val) {m_top_box.set_bg_color(val); }
        // Le constructeur met en place les elements de l'interface
        // voir l'implementation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};

class VertexAddInterface
{
    friend class Vertex;
    friend class Graph;

    private :
        int m_idx;
        bool m_value;

    public :
        // La boite qui contient toute l'interface d'un sommet
        grman::WidgetBox m_top_box;

        // L'image
        grman::WidgetImage m_icon;
        // Label pour l'img
        grman::WidgetText m_label_icon;
        // Une boite pour le label precedent
        grman::WidgetText m_box_label_icon;

        VertexAddInterface(int idx, std::string pic_name="");
        bool get_value(){return m_value;}
        void set_value(bool value){m_value = value;}
};

class Vertex
{
    // Les (methodes des) classes amies pourront acceder
    // directement aux attributs (y compris prives)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

    private :
        /// liste des indices des sommets arrivant au sommet : acces aux predecesseurs
        std::vector<int> m_in;

        /// liste des indices des sommets partant du sommet : acces aux successeurs
        std::vector<int> m_out;

        /// coef In -> "mange"
        double m_coefIn;
        /// coef Out -> "est mange"
        double m_coefOut;

        /// population
        int m_population;

        /// compteur incrementation pop
        double m_cptPop;

        /// booleen pour desactiver les sommets
        bool m_isVertex;


        /// groupe d'appartenance pour la forte connexite
        int m_group;

        /// le POINTEUR sur l'interface associee, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;

        // Docu shared_ptr : https://msdn.microsoft.com/fr-fr/library/hh279669.aspx
        // La ligne precedente est en gros equivalent a la ligne suivante :
        // VertexInterface * m_interface = nullptr;


    public:
        std::shared_ptr<VertexInterface> getInterface() { return m_interface; }
        /// Les constructeurs sont a completer selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Vertex (double coefIn=0, double coefOut=0, int population=0, VertexInterface *interface=nullptr) :
            m_coefIn(coefIn), m_coefOut(coefOut), m_population(population), m_cptPop(0), m_isVertex(true), m_interface(interface)  {  }

        /// Vertex etant gere par Graph ce sera la methode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'implementation Graph::update dans le .cpp
        void pre_update();
        void post_update();
        int getPopulation() { return m_population; }

};



/***************************************************
                    EDGE
****************************************************/

class EdgeInterface
{
    // Les (methodes des) classes amies pourront acceder
    // directement aux attributs (y compris prives)
    friend class Edge;
    friend class Graph;

    private :

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de declarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le parametrer ( voir l'implementation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;

        // Une boite pour englober les widgets de reglage associes
        grman::WidgetBox m_box_edge;

        // Un slider de visualisation/modification du poids valeur de l'arc
        grman::WidgetVSlider m_slider_weight;

        // Un label de visualisation du poids de l'arc
        grman::WidgetText m_label_weight;

        // bouton pour supprimer l'arete
        grman::WidgetButton m_bouton_delete;
        grman::WidgetText m_bouton_label_delete;

    public :

        // Le constructeur met en place les elements de l'interface
        // voir l'implementation dans le .cpp
        EdgeInterface(Vertex& from, Vertex& to);
};


class Edge
{
    // Les (methodes des) classes amies pourront acceder
    // directement aux attributs (y compris prives)
    friend class Graph;
    friend class EdgeInterface;

    private :
        /// indice du sommet de depart de l'arc
        int m_from;

        /// indice du sommet d'arrivee de l'arc
        int m_to;

        /// poids de l'arc
        double m_weight;

        /// booleen pour desactiver les arcs
        bool m_isEdge;

        /// le POINTEUR sur l'interface associee, nullptr -> pas d'interface
        std::shared_ptr<EdgeInterface> m_interface = nullptr;


    public:

        /// Les constructeurs sont a completer selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }

        /// Edge etant gere par Graph ce sera la methode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'implementation Graph::update dans le .cpp
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

        std::vector<VertexAddInterface*> tab;

        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de declarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le parametrer ( voir l'implementation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;

        /// Dans cette boite seront ajoutes les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;

        /// Dans cette boite seront ajoutes des boutons de contrôle etc...
        grman::WidgetBox m_tool_box;

    public :

        /// Le constructeur met en place les elements de l'interface
        ///voir l'implementation dans le .cpp
        GraphInterface(int x, int y, int w, int h);

        /*** TB buttons ***/

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

        // bouton pour afficher les combis de sommets a detacher
        grman::WidgetButton m_bouton_k_connex;
        grman::WidgetText m_bouton_k_connex_label;

        /*** Bottom buttons ***/

        // bouton pour ajouter des aretes
        grman::WidgetButton m_bouton_addEdges;
        grman::WidgetText m_bouton_label_addEdges;

         // bouton pour supprimer les sommets/aretes selectionnes
        grman::WidgetButton m_bouton_delete;
        grman::WidgetText m_bouton_label_delete;

        // bouton pour afficher la barre des sommets a ajouter
        grman::WidgetOnOffButton m_bouton_addVertices;
        grman::WidgetText m_bouton_label_addVertices;

        /*** Add vertices ***/

        /// Dans cette boite seront ajoutes les sommets pouvant être ajoutes au graphe
        grman::WidgetBox m_addVertices_box;


};


class Graph
{
    private :

        /// La "liste" des arêtes
        std::map<int, Edge> m_edges;

        /// La liste des sommets
        std::map<int, Vertex> m_vertices;

        /// La liste des sommets supprilm
        std::map<int, Vertex> m_vertices_del;

        /// le POINTEUR sur l'interface associee, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        /// nom du fichier
        std::string m_nomFichier;

        bool m_afficheConnexite = false;
        bool m_simu_temp = false;

    public:
        std::string getNomFichier() {return m_nomFichier; }
        std::shared_ptr<GraphInterface> getInterface() {return m_interface;}
        /// Les constructeurs sont a completer selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface)  {  }

        void add_interfaced_vertex(int idx, double coefIn, double coefOut, int pop, int x, int y, std::string pic_name="", int pic_idx=0 );
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        /// Ajoute les aretes selon les sommets selectionnes
        void add_edges();
        /// Copie le sommet d'indice idx dans la map de sommets supprimes
        void add_vertex_mapDel(int idx, double coefIn, double coefOut, int pop, int x, int y, std::string pic_name);
        /// Deplace un sommet supprime (m_vertices_del), vers le tableau m_vertices
        void move_vertexDelToVertices(int idx);
        /// Deplace un sommet (m_vertices) vers le tableau des sommets supprimes (m_vertices_del)
        void move_vertexToDel(int idx);

        /// Retourne true si l'arete existe deja
        bool edge_exist(int from, int to);

        /// Supprime le sommet d'indice idx
        void delete_edge(int idx);
        /// Supprime toutes les aretes comportant le sommet d'indice idx
        void delete_vertex_allEdges(int idx);
        /// Supprime le sommet d'indice idx
        void delete_vertex(int idx);
        /// Supprimes tous les sommets selectionnes
        void delete_vertices();

        /// chargement des fichiers
        void read_file(const std::string& nom_fichier);
        void read_file_del(); // fichier des sommets supprimes
        /// enregistrement des fichiers
        void write_file();
        void write_file_del(); // fichier des sommets supprimes
        /// methode pour la detection des composantes fortement connexes
        void fort_connexe();

        /// Retourne l'idx de l'arete la plus grande
        int find_idxMax_edges();

        /// implementation de la liste des indices des arcs arrivant au sommet
        void findIn();

        /// implementation de la liste des indices des arcs sortant du sommet
        void findOut();

        /// creation d'un stack contenant tous les sommets dans un ordre particulier pour l'algorithme de Kosaraju
        void fillOrder(int i, bool visited[], std::stack<int> &Stack);

        /// inversion de toutes les aretes du graph pour l'algorithme de Kosaraju
        Graph getTranspose();

        /// implementation dfs
        void dfs(int v, bool visited[], int k, int col);

        void bfs(int v, unsigned int &visitedVertices);

        /// La methode update a appeler dans la boucle de jeu pour les graphes avec interface
        void update();

        /// Permet d'update les boutons des sommets
        void update_buttons();

        /// Permet d'update la box comportant les sommets a ajouter
        void update_addVertices_box();

        /// Permet de mettre a jour la population de tous les sommets
        void update_pop();

        /// Calcul de K, capacite de portage de l'environnement
        double calcul_sommeKIn(int to);
        double calcul_sommeKOut(int from);

        /// Permet de chercher le poids de l'arete forme par les 2 sommets (s'il existe, 0 sinon)
        double findWeight(int from, int to);

        bool getAfficheConnexite() { return m_afficheConnexite; }
        void setAfficheConnexite(bool val) { m_afficheConnexite = val; }

        void invertSimu() { m_simu_temp = !m_simu_temp; }
        void resetColors();

        std::map<int, Vertex> getVertices() { return m_vertices; }

        /// Verifie si les sommets actives forment un graphe connexe
        bool isConnexe();
        /// Implementation d'un programme permettant de trouver le nombre k minimum de sommets pour deconnecter le graphe
        void kSommetConnex();
        /// Trouve les combi de sommet
        void findCombi(std::vector<std::vector<int>> &allComponents, std::vector<int> &tab, int j, int k, int nb);
        /// Verifie si tous les sommets sont marques
        bool isAllMarqued(std::map<int, bool> &marque);
};


#endif // GRAPH_H_INCLUDED
