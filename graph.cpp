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

    /*** Button DELETE ***/
    m_top_box.add_child(m_bouton_delete);
    m_bouton_delete.set_frame(203, 0, 20, 20);
    m_bouton_delete.set_bg_color(ROUGESOMBRE);

    m_bouton_delete.add_child(m_bouton_label_delete);
    m_bouton_label_delete.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_bouton_label_delete.set_color(BLANC);
    m_bouton_label_delete.set_message("X");

    /*** Button ADD EDGE ***/
    m_top_box.add_child(m_bouton_addEdge);
    m_bouton_addEdge.set_frame(203, 20, 20, 20);
    m_bouton_addEdge.set_bg_color(BLEUCLAIR);

    m_bouton_addEdge.add_child(m_bouton_label_addEdge);
    m_bouton_label_addEdge.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_bouton_label_addEdge.set_color(BLANC);
    m_bouton_label_addEdge.set_message("");
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

    /*** Button DELETE ***/
    m_top_edge.add_child(m_bouton_delete);
    m_bouton_delete.set_frame(10, -32, 12, 12);
    m_bouton_delete.set_bg_color(ROUGESOMBRE);

    m_bouton_delete.add_child(m_bouton_label_delete);
    m_bouton_label_delete.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_bouton_label_delete.set_color(BLANC);
    m_bouton_label_delete.set_message("X");

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

    /// Button ADD EDGE
    m_top_box.add_child(m_bouton_addEdges);
    m_bouton_addEdges.set_frame(450, 710, 30, 30);
    m_bouton_addEdges.set_bg_color(BLEUCLAIR);

    m_bouton_addEdges.add_child(m_bouton_label_addEdges);
    m_bouton_label_addEdges.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_bouton_label_addEdges.set_color(BLANC);
    m_bouton_label_addEdges.set_message("+");

    /// Button DELETE
    m_top_box.add_child(m_bouton_delete);
    m_bouton_delete.set_frame(500, 710, 30, 30);
    m_bouton_delete.set_bg_color(ROUGESOMBRE);

    m_bouton_delete.add_child(m_bouton_label_delete);
    m_bouton_label_delete.set_gravity_xy(grman::GravityX::Center, grman::GravityY::Center);
    m_bouton_label_delete.set_color(BLANC);
    m_bouton_label_delete.set_message("X");

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
            m_vertices[idx].m_coefIn = coefIn;
            m_vertices[idx].m_coefOut = coefOut;
            m_vertices[idx].m_population = pop;
            m_vertices[idx].m_cptPop = 0.0;
        }

        for(unsigned int i(0); i<nbEdges; ++i)
        {
            fic >> idx >> vert1 >> vert2 >> weight;
            add_interfaced_edge(idx, vert1, vert2, weight);
            m_edges[idx].m_from = vert1;
            m_edges[idx].m_to = vert2;
            m_edges[idx].m_weight = weight;
        }
    }
    findIn();
    findOut();
    for(auto &elem : m_vertices)
        elem.second.m_coefOut = 0.00009;
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

    if (m_simu_temp)
        update_pop();

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    update_buttons();

}

void Graph::update_buttons()
{
    /*** BOUTONS SOMMETS***/
    for(auto &elt : m_vertices)
    {
        /// Bouton suppr
        if(elt.second.m_interface->m_bouton_delete.clicked() && m_vertices.size() > 1)
        {
            delete_vertex(elt.first);
            break;
        }
        /// Bouton add edge
        if(elt.second.m_interface->m_bouton_addEdge.clicked())
        {
            if(elt.second.m_interface->m_bouton_label_addEdge.get_message() == "")
            {
                elt.second.m_interface->m_bouton_label_addEdge.set_message("1");
            }
            else if(elt.second.m_interface->m_bouton_label_addEdge.get_message() == "1")
            {
                elt.second.m_interface->m_bouton_label_addEdge.set_message("2");
            }
            else
            {
                elt.second.m_interface->m_bouton_label_addEdge.set_message("");
            }
        }
    }

    /*** BOUTONS ARETES ***/
    for(auto &elt : m_edges)
    {
        /// Bouton suppr
        if(elt.second.m_interface->m_bouton_delete.clicked())
        {
            delete_edge(elt.first);
            break;
        }
    }
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

void Graph::add_edges()
{
    std::vector<int> from;
    std::vector<int> to;
    int idxMax = 0;
    for(auto &e : m_vertices)
    {
        if(e.second.m_interface->m_bouton_label_addEdge.get_message() == "1")
        {
            from.push_back(e.first);
            e.second.m_interface->m_bouton_label_addEdge.set_message("");
        }
        else if(e.second.m_interface->m_bouton_label_addEdge.get_message() == "2")
        {
            to.push_back(e.first);
            e.second.m_interface->m_bouton_label_addEdge.set_message("");
        }
    }

    for(auto &f : from)
    {
        for(auto &t : to)
        {
            idxMax = find_idxMax_edges();
            if(!edge_exist(f, t))
            {
                add_interfaced_edge(idxMax+1, f, t, 0);
                m_edges[idxMax+1].m_from = f;
                m_edges[idxMax+1].m_to = t;
                std::cout << std::endl << "Edge ADDED " << f << " - " << t;
                m_vertices[f].m_out.push_back(t);
                m_vertices[t].m_in.push_back(f);
            }
        }
    }
}

bool Graph::edge_exist(int from, int to)
{
    for(auto &e : m_edges)
    {
        if(e.second.m_from == from && e.second.m_to == to)
        {
            return true;
        }
    }

    return false;
}

void Graph::delete_edge(int idx)
{
    if(m_edges.find(idx)!=m_edges.end())
    {
        Edge &edge = m_edges.at(idx);

        /// référence au tableau m_out
        std::vector<int> &tabFrom = m_vertices[edge.m_from].m_out;
        /// référence au tableau m_out
        std::vector<int> &tabTo = m_vertices[edge.m_to].m_in;


        auto it = find(tabTo.begin(), tabTo.end(), edge.m_from);
        if(it != tabTo.end())
        {
            tabTo.erase(it);
        }

        auto it2 = find(tabFrom.begin(), tabFrom.end(), edge.m_to);
        if(it2 != tabFrom.end())
        {
            tabFrom.erase(it2);
        }

        /// Si les interfaces existent
        if(m_interface && edge.m_interface)
        {
            /// On supprime l'interface de l'arete
            m_interface->m_main_box.remove_child(edge.m_interface->m_top_edge);
        }
        std::cout << std::endl << "Edge[" <<idx << "] deleted";
        m_edges.erase(idx); /// On supprime l'arete de la map
    }

}

void Graph::delete_vertex_allEdges(int idx)
{
    /// Parcourt de toutes les aretes
    for (auto it = m_edges.cbegin(); it != m_edges.cend();)
    {
        /// Si un des sommet de cet arete correspond au sommet d'indice idx
        if (it->second.m_from == idx || it->second.m_to == idx)
        {
            /// Si le sommet est un sommet de départ de l'arete
            if(it->second.m_from == idx)
            {
                /// référence au tableau m_in
                std::vector<int> &tab = m_vertices[it->second.m_to].m_in;

                auto it2 = find(tab.begin(), tab.end(), idx);
                if(it2 != tab.end())
                {
                    tab.erase(it2);
                }
            }
            else if(it->second.m_to == idx) /// Si le sommet est un sommet d'arrivé
            {
                /// référence au tableau m_out
                std::vector<int> &tab = m_vertices[it->second.m_from].m_out;

                auto it2 = find(tab.begin(), tab.end(), idx);
                if(it2 != tab.end())
                {
                    tab.erase(it2);
                }
            }

            /// Si les interfaces existent
            if(m_interface && it->second.m_interface)
            {
                /// On supprime l'interface de l'arete
                m_interface->m_main_box.remove_child(it->second.m_interface->m_top_edge);
            }
            std::cout << std::endl << "Edge[" << it->first << "] deleted";
            m_edges.erase(it++); /// On supprime l'arete de la map
        }
        else
        {
            ++it;
        }
    }
}

void Graph::delete_vertex(int idx)
{
    /// On supprime toutes les aretes comportant le sommet idx
    delete_vertex_allEdges(idx);

    /// Si les interfaces existent
    if(m_interface && m_vertices[idx].m_interface)
    {
        /// On supprime l'interface du sommet
        m_interface->m_main_box.remove_child(m_vertices[idx].m_interface->m_top_box);
    }

    /// On supprime le sommet de la map
    m_vertices.erase(idx);
    std::cout << std::endl << "Vertex[" << idx << "] deleted";

}

void Graph::delete_vertices()
{
    for (auto it = m_vertices.cbegin(); it != m_vertices.cend();)
    {
        if((it->second.m_interface->m_bouton_label_addEdge.get_message() == "1" || it->second.m_interface->m_bouton_label_addEdge.get_message() == "2") && m_vertices.size() > 1)
        {
            it->second.m_interface->m_bouton_label_addEdge.set_message("");
            delete_vertex((it++)->first);
        }
        else
        {
            ++it;
        }
    }/*
    for(auto &e : m_vertices)
    {
        if(e.second.m_interface->m_bouton_label_addEdge.get_message() == "1" || e.second.m_interface->m_bouton_label_addEdge.get_message() == "2")
        {
            e.second.m_interface->m_bouton_label_addEdge.set_message("");
            delete_vertex(e.first);
        }
    }*/
}

int Graph::find_idxMax_edges()
{
    int idxMax = 0;
    for(auto &e : m_edges)
    {
        if(e.first > idxMax)
        {
            idxMax = e.first;
        }
    }

    return idxMax;
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

void Graph::recu(std::vector<std::vector<int>> &allComponents, std::vector<int> &tab, int j, int k, int nb)
{
    if(k < nb)
    {
        std::map< int, Vertex >::iterator id;
        for(id = std::next(m_vertices.begin(),j); id != m_vertices.end(); id++)
        {
            tab.push_back(id->first);
            recu(allComponents, tab, ++j, k+1, nb);
            if(tab.size() == nb)
                allComponents.push_back(tab);
            tab.pop_back();
        }
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
    std::vector<int> colors = {0x00FF00,0x0000FF,0xFF0000,0x01FFFE,0xFFA6FE,0xFFDB66,0x006401,0x010067,0x95003A,0x007DB5,0xFF00F6,0xFFEEE8,0x774D00,0x90FB92,0x0076FF,0xD5FF00,0xFF937E,0x6A826C,0xFF029D,0xFE8900,0x7A4782,0x7E2DD2,0x85A900,0xFF0056,0xA42400,0x00AE7E,0x683D3B,0xBDC6FF,0x263400,0xBDD393,0x00B917,0x9E008E,0x001544,0xC28C9F,0xFF74A3};

    // Marquer toutes les aretes comme non visitées
    bool *visited = new bool[m_vertices.size()];
    for(auto &id : m_vertices)
        visited[id.first] = false;

    // Ajouter tous les sommets dans le stack
    for(auto &id : m_vertices)
        if(!visited[id.first])
            fillOrder(id.first, visited, Stack);

    Graph g = getTranspose();

    for(auto &id : m_vertices)
        visited[id.first] = false;

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
            int col = colors[v % colors.size()];
            g.dfs(v, visited, k, col);
            std::cout << std::endl;
            k++;
        }
    }

    for(auto &id : m_vertices)
        m_vertices[id.first].m_group = g.m_vertices[id.first].m_group;
}

/// Implementation BFS inspiré de https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
void Graph::bfs(int v, unsigned int &visitedVertices)
{
    // Marquer toutes les aretes comme non visitées
    bool *visited = new bool[m_vertices.size()];
    for(unsigned int i = 0; i < m_vertices.size(); ++i)
        visited[i] = false;
    visitedVertices++;

    // Create a queue for BFS
    std::list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[v] = true;
    queue.push_back(v);

    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        v = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it

        for(unsigned int i = 0; i < m_vertices[v].m_out.size(); ++i)
        {
            if(!visited[m_vertices[v].m_out[i]] && m_vertices[m_vertices[v].m_out[i]].m_isVertex)
            {
                visited[m_vertices[v].m_out[i]] = true;
                queue.push_back(m_vertices[v].m_out[i]);
                visitedVertices++;
            }
        }
        for(unsigned int i = 0; i < m_vertices[v].m_in.size(); ++i)
        {
            if(!visited[m_vertices[v].m_in[i]] && m_vertices[m_vertices[v].m_in[i]].m_isVertex)
            {
                visited[m_vertices[v].m_in[i]] = true;
                queue.push_back(m_vertices[v].m_in[i]);
                visitedVertices++;
            }
        }
    }
}

/// Implementation d'un programme permettant de trouver le nombre k minimum de sommets pour deconnecter le graphe
void Graph::kVertexConnex()
{
    unsigned int kmin = m_vertices.size()-1, visitedVertices = 0, visitedVerticesMax = 0, nbVertices;
    std::vector< std::vector<int> > allComponents, critPoints;

    do
    {
        // Trouver toutes les combinaisons entre les sommets
        for(unsigned int j = 0; j < m_vertices.size()-1; ++j)
        {
            std::vector<int> temp;
            recu(allComponents, temp, 0, 0, j);
        }
        for (auto &components : allComponents)
        {
            for (auto &id : components)
                std::cout << id << " ";
            std::cout << std::endl;
        }
        for (auto &components : allComponents)
        {
            for (auto &id : components)
            {
                m_vertices[id].m_isVertex = false;
            }

            // Mise à jour du nombre d'aretes actives
            nbVertices = 0;
            for(auto &id : m_vertices)
                if(id.second.m_isVertex)
                    nbVertices++;

            for(auto &id : m_vertices)
            {
                if(id.second.m_isVertex)
                {
                    bfs(id.first, visitedVertices);
                    break;
                }
            }

            if(visitedVertices < nbVertices)
                critPoints.push_back(components);

            if(visitedVerticesMax < visitedVertices)
                visitedVerticesMax = visitedVertices;
            if((kmin > nbVertices) && (visitedVertices < nbVertices))
                kmin = nbVertices;
            visitedVertices = 0;

            for (auto &id : components)
                m_vertices[id].m_isVertex = true;
        }
        /*for(k = 1; k < m_vertices.size(); ++k)
        {
            for(unsigned int o = 0; o < allComponents.size(); ++o)
            {
                for(unsigned int p = 0; p < allComponents[o].size(); ++p)
                    m_vertices[allComponents[k][p]].m_isVertex=false;

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
        }*/
    }
    while(visitedVerticesMax == m_vertices.size());

    for (auto &components : critPoints)
    {
        for (auto &id : components)
            std::cout << id << " ";
        std::cout << std::endl;
    }
    --kmin;
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

        if (e.second.m_population > 50000) {
            e.second.m_population = 50000;
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
        e.second.getInterface()->setBgCol(BLANCJAUNE);
    }
}
