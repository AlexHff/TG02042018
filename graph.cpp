#include "graph.h"

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(200, 100);
    m_top_box.set_moveable();


    /*** VALUE ***/
    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 0.02);  // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    //m_top_box.add_child( m_label_value );
    //m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    /*** POPULATION ***/
    // Le slider de réglage de la pop
    m_top_box.add_child( m_slider_pop );
    m_slider_pop.set_range(0.0, 10000.0);  // Valeurs arbitraires, à adapter...
    m_slider_pop.set_dim(20,80);
    m_slider_pop.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    // Label de visualisation de la pop
    m_top_box.add_child( m_label_pop );
    m_label_pop.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);

    /*** IMG ***/
    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Center);
    }

    /*** IDX ***/
    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel à l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    // Value
    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_coefIn);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_coefIn) );

    // Pop
    /// Copier la valeur locale de la donnée m_population vers le slider associé
    m_interface->m_slider_pop.set_value(m_population);

    /// Copier la valeur locale de la donnée m_population vers le label sous le slider
    m_interface->m_label_pop.set_message( std::to_string( (int)m_population) );
}

/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_coefIn = m_interface->m_slider_value.get_value();

    m_population = m_interface->m_slider_pop.get_value();
}

/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les éléments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de réglage associés
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de réglage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, à adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel à l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donnée m_weight vers le slider associé
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donnée m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge après l'appel à l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de préparer un cadre d'accueil des
/// éléments qui seront ensuite ajoutés lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);

    m_tool_box.add_child(m_boite_boutons);
    m_boite_boutons.set_dim(80,700);
    m_boite_boutons.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);
    m_boite_boutons.set_bg_color(BLANC);

    /// bouton g1
    m_boite_boutons.add_child(m_bouton_g1);
    m_bouton_g1.set_frame(5, 0, 70, 40);
    m_bouton_g1.set_bg_color(VERTCLAIR);

    m_bouton_g1.add_child(m_bouton_g1_label);
    m_bouton_g1_label.set_message("Graphe 1");

    /// bouton g2
    m_boite_boutons.add_child(m_bouton_g2);
    m_bouton_g2.set_frame(5, 100, 70, 40);
    m_bouton_g2.set_bg_color(VERTCLAIR);

    m_bouton_g2.add_child(m_bouton_g2_label);
    m_bouton_g2_label.set_message("Graphe 2");

    /// bouton g3
    m_boite_boutons.add_child(m_bouton_g3);
    m_bouton_g3.set_frame(5, 200, 70, 40);
    m_bouton_g3.set_bg_color(VERTCLAIR);

    m_bouton_g3.add_child(m_bouton_g3_label);
    m_bouton_g3_label.set_message("Graphe 3");

    /// bouton save
    m_boite_boutons.add_child(m_bouton_save);
    m_bouton_save.set_frame(5, 300, 70, 40);
    m_bouton_save.set_bg_color(BLEUCLAIR);

    m_bouton_save.add_child(m_bouton_save_label);
    m_bouton_save_label.set_message("Sauvegarde");

    /// bouton simulation
    m_boite_boutons.add_child(m_bouton_simu);
    m_bouton_simu.set_frame(5, 400, 70, 40);
    m_bouton_simu.set_bg_color(JAUNECLAIR);

    m_bouton_simu.add_child(m_bouton_simu_label);
    m_bouton_simu_label.set_message("Temps reel");

    /// bouton diff
    m_boite_boutons.add_child(m_bouton_diff);
    m_bouton_diff.set_frame(5, 500, 70, 40);
    m_bouton_diff.set_bg_color(ROSECLAIR);

    m_bouton_diff.add_child(m_bouton_diff_label);
    m_bouton_diff_label.set_message("Differee");

    /// bouton afficher connexite
    m_boite_boutons.add_child(m_bouton_connex);
    m_bouton_connex.set_frame(5, 600, 70, 40);
    m_bouton_connex.set_bg_color(ORANGECLAIR);

    m_bouton_connex.add_child(m_bouton_connex_label);
    m_bouton_connex_label.set_message("Connexite");

}

void Graph::read_file(const std::string& nom_fichier)
{
    m_nomFichier=nom_fichier;
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);

    /// Tentative d'ouverture du fichier
    std::fstream fic(m_nomFichier, std::ios_base::in);
    if ( !fic.is_open() )
        throw "Probleme ouverture fichier !";
    /// Traitement du fichier
    else
    {
        unsigned int idx, x, y, vert1, vert2, nbVertices, nbEdges;
        double coefIn, coefOut, weight;
        int pop;
        std::string pic_name;

        fic >> nbVertices;
        fic >> nbEdges;
        for(unsigned int i(0); i<nbVertices; ++i)
        {
            fic >> idx >> coefIn >> coefOut >> pop >> x >> y >> pic_name;
            add_interfaced_vertex(idx, coefIn, coefOut, pop, x, y, pic_name);
            m_vertices[i].m_coefIn = coefIn;
            m_vertices[i].m_coefOut = coefOut;
            m_vertices[i].m_population = pop;

            m_vertices[i].m_cptPop = 0.0;

        }

        for(unsigned int i(0); i<nbEdges; ++i)
        {
            fic >> idx >> vert1 >> vert2 >> weight;
            add_interfaced_edge(idx, vert1, vert2, weight);
            m_edges[i].m_from = vert1;
            m_edges[i].m_to = vert2;
            m_edges[i].m_weight = weight;
        }
    }
    findIn();
    findOut();
    for(auto &elem : m_vertices)
    {
        elem.second.m_coefOut = 0.00009;
    }
}

void Graph::write_file()
{
    /// test d'ouverture du fichier
    std::fstream fic(m_nomFichier, std::ios_base::out);
    if ( !fic.is_open() )
        throw "Probleme ouverture fichier !";
    /// ecriture dans le fichier

    else
    {
        std::cout << "Sauvegarde dans \"" << m_nomFichier << "\"." << std::endl;
        fic << m_vertices.size() << std::endl;
        fic << m_edges.size() << std::endl;
        for(auto &e : m_vertices)
        {
            fic << e.first << " " << e.second.m_coefIn << " " << e.second.m_coefOut << " " << e.second.m_population << " " << e.second.m_interface->m_top_box.get_posx()+2 << " " << e.second.m_interface->m_top_box.get_posy()+2 << " " << e.second.m_interface->m_img.get_pic_name() << std::endl;
        }

        for(auto &e : m_edges)
        {
            fic << e.first << " " << e.second.m_from << " " << e.second.m_to << " " << e.second.m_weight << std::endl;
        }
    }
}

/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    if (m_simu_temp) {
        update_pop();
    }

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double coefIn, double coefOut, int pop, int x, int y, std::string pic_name, int pic_idx )
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Création d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, pic_idx);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(coefIn, coefOut, pop, vi);
}

/// Aide à l'ajout d'arcs interfacés
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, double weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
}

void Graph::findOut()
{
    for(auto &e : m_vertices)
    {
        for(auto &f : m_edges)
            if(e.first==f.second.m_from)
                e.second.m_out.push_back(f.second.m_to);
    }

    /*for(auto &e : m_vertices)
    {
        std::cout << e.first << " est succede par ";
        if(e.second.m_out.size()==0)
            std::cout << "aucun autre sommet." << std::endl;
        else
        {
            for(unsigned int j(0); j < e.second.m_out.size(); ++j)
                std::cout << e.second.m_out[j] << " ";
            std::cout << std::endl;
        }
    }*/
}

void Graph::findIn()
{
    for(auto &e : m_vertices)
    {
        for(auto &f : m_edges)
            if(e.first==f.second.m_to)
                e.second.m_in.push_back(f.second.m_from);
    }

    /*for(auto &e : m_vertices)
    {
        std::cout << e.first << " est precede par ";
        if(e.second.m_in.size()==0)
            std::cout << "aucun autre sommet." << std::endl;
        else
        {
            for(unsigned int j(0); j < e.second.m_in.size(); ++j)
                std::cout << e.second.m_in[j] << " ";
            std::cout << std::endl;
        }
    }*/
}

void Graph::dfs(int v, bool visited[],int k, int col)
{
    visited[v] = true;
    m_vertices[v].m_group = k;
    std::cout << v << " ";

    m_vertices[v].getInterface()->setBgCol(col);

    for(unsigned int i(0); i < m_vertices[v].m_out.size(); ++i)
        if(!visited[m_vertices[v].m_out[i]])
            dfs(m_vertices[v].m_out[i], visited, k, col);
}

void Graph::kdfs(int v, bool visited[],int k)
{
    k--;
    visited[v] = true;
    std::cout << v << " ";
    unsigned int i = 0;

    for(unsigned j = 0; j < k; ++j)
    {
        for(i; i < m_vertices[v].m_out.size(); ++i)
            if(!visited[m_vertices[v].m_out[i]])
                kdfs(m_vertices[v].m_out[i], visited, k);

        for(i; i < m_vertices[v].m_in.size(); ++i)
            if(!visited[m_vertices[v].m_in[i]])
                kdfs(m_vertices[v].m_in[i], visited, k);
    }
}

Graph Graph::getTranspose()
{
    Graph g = *this;

    for(auto &e : g.m_vertices)
        std::swap(e.second.m_out,e.second.m_in);
    for(auto &e : g.m_edges)
        std::swap(e.second.m_from,e.second.m_to);

    return g;
}

void Graph::fillOrder(int v, bool visited[], std::stack<int> &Stack)
{
    visited[v] = true;

    for(unsigned int i(0); i < m_vertices[v].m_out.size(); ++i)
        if(!visited[m_vertices[v].m_out[i]])
            fillOrder(m_vertices[v].m_out[i], visited, Stack);

    Stack.push(v);
}

/// Implementation de l'algorithme de Kosaraju pour trouver les composantes fortement connexes, inspiré de https://www.geeksforgeeks.org/strongly-connected-components/
void Graph::fort_connexe()
{
    // On utilise un stack étant donné son principe LIFO
    std::stack<int> Stack;

    // Marquer toutes les aretes comme non visitées
    bool *visited = new bool[m_vertices.size()];
    for(unsigned int i(0); i < m_vertices.size(); ++i)
        visited[i] = false;

    // Ajouter tous les sommets dans le stack
    for(unsigned int i(0); i < m_vertices.size(); ++i)
        if(!visited[i])
            fillOrder(i, visited, Stack);

    Graph g = getTranspose();

    for(unsigned int i(0); i < m_vertices.size(); ++i)
        visited[i] = false;

    int k = 0;
    std::cout << "Les composantes fortement connexes :" << std::endl;
    while (!Stack.empty())
    {
        // Pop a vertex from stac->setBgCol(col)k
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (!visited[v])
        {
            int col = 0xCCCCCC + rand() % 0xCCCCCC;
            g.dfs(v, visited, k, col);
            std::cout << std::endl;
            k++;
        }
    }

    for(unsigned int i(0); i < m_vertices.size(); ++i)
        m_vertices[i].m_group = g.m_vertices[i].m_group;
}

void Graph::kVertexConnexRecur(int v, bool visited[], unsigned int &visitedVertices)
{
    visitedVertices++;
    visited[v] = true;

    for(unsigned int i(0); i < m_vertices[v].m_out.size(); ++i)
        if(!visited[m_vertices[v].m_out[i]] && m_vertices[m_vertices[v].m_out[i]].m_isVertex)
            kVertexConnexRecur(m_vertices[v].m_out[i], visited, visitedVertices);

    for(unsigned int i(0); i < m_vertices[v].m_in.size(); ++i)
        if(!visited[m_vertices[v].m_in[i]] && m_vertices[m_vertices[v].m_in[i]].m_isVertex)
            kVertexConnexRecur(m_vertices[v].m_in[i], visited, visitedVertices);
}

/// Implementation d'un programme permettant de trouver le nombre k minimum de sommets pour deconnecter le graphe
void Graph::kVertexConnex()
{
    // Marquer toutes les aretes comme non visitées
    bool *visited = new bool[m_vertices.size()];
    for(unsigned int i(0); i < m_vertices.size(); ++i)
        visited[i] = false;

    unsigned int k = 0, kmin = m_vertices.size()-1, visitedVertices = 0, visitedVerticesMax = 0, nbVertices;
    std::vector<int>allComponents;

    do
    {
        for(k = 1; k < m_vertices.size(); ++k)
        {
            for(unsigned int j = 0; j < m_vertices.size(); ++j)
            {
                std::cout << "k = " << k << std::endl;
                kdfs(j, visited, k);
                std::cout << std::endl;
                for(unsigned int t(0); t < m_vertices.size(); ++t)
                    visited[t] = false;
            }
            for(unsigned int j(0); j < m_vertices.size() ; ++j)
            {
                m_vertices[j].m_isVertex=false;

                // Mise à jour du nombre d'aretes actives
                nbVertices = 0;
                for(unsigned int i(0); i < m_vertices.size(); ++i)
                    if(!m_vertices[i].m_isVertex)
                        nbVertices++;

                for(unsigned int i(0); i < m_vertices.size(); ++i)
                {
                    if(!visited[i] && m_vertices[i].m_isVertex)
                    {
                        kVertexConnexRecur(i, visited, visitedVertices);
                        if(visitedVerticesMax < visitedVertices)
                            visitedVerticesMax = visitedVertices;
                        if((kmin > nbVertices) && (visitedVertices < nbVertices))
                            kmin = nbVertices;
                        visitedVertices = 0;
                    }
                    for(unsigned int t(0); t < m_vertices.size(); ++t)
                        visited[t] = false;
                }

                for(unsigned int i(0); i < m_vertices.size(); ++i)
                    m_vertices[i].m_isVertex=true;
            }
        }
    }
    while(visitedVerticesMax == m_vertices.size());
    std::cout << "Nombre minimal de sommet a desactiver pour deconnecter le graphe :" << std::endl << "kmin = " << kmin << std::endl;
}

double Graph::calcul_sommeKIn(int to)
{
    double k = 0;
    double weight;

    // Sommet des K des aretes pointant vers le sommet
    for(auto &e : m_vertices[to].m_in)
    {
        weight = findWeight(e, to);
        k += weight * m_vertices[e].m_population;
    }

    return k;
}

double Graph::calcul_sommeKOut(int from)
{
    double k = 0;
    double weight;

    // Somme des K des aretes sortant du sommet
    for(auto &e : m_vertices[from].m_out)
    {
        weight = findWeight(from, e);
        k += m_vertices[e].m_coefIn * weight * m_vertices[e].m_population;
    }
/// A FAIRE : plusieurs cas particuliers ( + quand le poids des aretes est nul, plus de nouriture, pas de sommet pointant vers)
    return k;
}

void Graph::update_pop()
{
    double Kin;
    double quotient;

    for(auto &e : m_vertices)
    {
        Kin = calcul_sommeKIn(e.first);

        if(e.second.m_in.size() == 0) /// Si pas d'aretes pointant vers le sommet => ne mange personne
        {
            quotient = 1.0;

        }
        else if(Kin == 0) /// => plus de nourriture
        {
            quotient = 2.0;

        }
        else
        {
            quotient = e.second.m_population/Kin;
        }

        /// calcul de la nouvelle population

        e.second.m_cptPop += e.second.m_coefIn * e.second.m_population * (1 - quotient) - e.second.m_coefOut * calcul_sommeKOut(e.first);

        if(e.second.m_cptPop >= 1.0)
        {
            e.second.m_population += e.second.m_cptPop;
            //e.second.m_population++;
            e.second.m_cptPop = 0.0;
        }
        else if(e.second.m_cptPop <= -1.0)
        {
            e.second.m_population += e.second.m_cptPop;
            //e.second.m_population--;
            e.second.m_cptPop = 0.0;
        }

        if(e.second.m_population < 0) /// Pas de pop négative
        {
            e.second.m_population = 0;
        }
    }

}

double Graph::findWeight(int from, int to)
{
    for(auto &e : m_edges)
    {
        if(e.second.m_from == from && e.second.m_to == to)
        {
            return e.second.m_weight;
        }
    }

    /// Si a pas trouvé, on retourne 0
    return 0;
}

void Graph::resetColors()
{
    for(auto &e : m_vertices)
    {
        e.second.getInterface()->setBgCol(BLANC);
    }
}
