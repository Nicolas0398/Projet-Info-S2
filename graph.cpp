#include "graph.h"
#include <fstream>
#include <iostream>


/***************************************************
                    VERTEX
****************************************************/
using namespace std;
/// Le constructeur met en place les éléments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int pic_idx)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de réglage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_pic_idx(pic_idx);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
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

    /// Copier la valeur locale de la donnée m_value vers le slider associé
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donnée m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex après l'appel à l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donnée m_value locale
    m_value = m_interface->m_slider_value.get_value();
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
    m_slider_weight.set_range(0.0 , 100.0); // Valeurs arbitraires, à adapter...
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

    /*m_tool_box.add_child( m_boite_boutons );
    m_boite_boutons.set_dim(80,60);
    m_boite_boutons.set_gravity_y(grman::GravityY::Up );
    m_boite_boutons.set_bg_color(FUCHSIACLAIR);*/


     m_tool_box.add_child( m_bouton2 );
    m_bouton2.set_dim(84,70);
    m_bouton2.set_frame(0,0,168,140);
    m_bouton2.set_bg_color(JAUNESOMBRE);
    m_bouton2.add_child(m_bouton2_label);
    m_bouton2_label.set_message("AJOUTER");
    m_bouton2_label.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    m_tool_box.add_child( m_bouton1 );
    m_bouton1.set_dim(84,70);
    m_bouton1.set_gravity_y(grman::GravityY::Up );
    m_bouton1.set_frame(0,0,84,70);
    m_bouton1.set_bg_color(ROUGE);
    m_bouton1.add_child(m_bouton1_label);
    m_bouton1_label.set_message("SUPP");

    m_tool_box.add_child(m_titre);
    m_titre.set_message("E C O S Y S T E M E");
    m_titre.set_vertical();
     m_titre.set_gravity_y(grman::GravityY::Center );



}

/// Méthode spéciale qui construit un graphe arbitraire (démo)
/// Cette méthode est à enlever et remplacer par un système
/// de chargement de fichiers par exemple.
/// Bien sûr on ne veut pas que vos graphes soient construits
/// "à la main" dans le code comme ça.
void Graph::make_example(std::string f1, std::string f2)
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne précédente est en gros équivalente à :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    ifstream fichier(f1, ios::in);  // on ouvre le fichier en lecture

        if(fichier)  // si l'ouverture a réussi
        {
            int indice, coord_x, coord_y;
            double poids;
            string vignette;

            fichier>>m_ordre;

            for (int i=0;i<m_ordre;i++)
            {
                fichier>>indice;
                fichier>>poids;
                fichier>>coord_x;
                fichier>>coord_y;
                fichier>>vignette;

                add_interfaced_vertex(indice,poids,coord_x,coord_y,vignette);
            }

                fichier.close();  // on ferme le fichier
        }
        else  // sinon
        {


                cerr << "Impossible d'ouvrir le fichier !" << endl;
        }


        ifstream fichier2 (f2,ios::in);

        if (fichier2)
        {
            double poids;
            int num_arc=0;

            for (int j=0; j<m_ordre;j++)
            {
                for (int k=0;k<m_ordre;k++)
                {
                    fichier2>>poids;

                    if (poids !=0)
                    {
                        add_interfaced_edge(num_arc,j,k,poids);
                        num_arc++;
                    }
                }
            }

            fichier2.close();
        }
      else

        {
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
}

void Graph::save(std::string f1)

{
    ofstream fichier (f1,ios::trunc);

    string nom_image;

    if (fichier)
    {
        fichier<< m_ordre<<endl;

        for (auto &it : m_vertices)
        {

            fichier << it.first<<" ";
            fichier << it.second.m_value<<" ";
            fichier<<it.second.m_interface->m_top_box.get_frame_pos() .x<< " ";
            fichier<<it.second.m_interface->m_top_box.get_frame_pos() .y<< " ";
            nom_image=it.second.m_interface->m_img.get_pic_name();
            nom_image.erase(nom_image.size()-4,4);
            fichier<<nom_image + ".jpg" << endl;
        }

        fichier.close();
    }

    else { cerr <<" cant open the file"<<endl; }

}

void Graph::simulation()
{

    for (auto &sommet : m_vertices)
    {
        double coeff=0;

        ///sommet.second.m_value++;

        for (int i=0; i<sommet.second.m_in.size(); i++)
        {

            cout <<"ok0"<<endl;
            for (auto &arrete : m_edges)
            {
                if(arrete.second.m_from==sommet.second.m_in[i] && arrete.second.m_to==sommet.first)
                {
                    coeff = coeff + arrete.second.m_weight*(m_vertices[i].m_value/10);
                    cout<<" ok1"<<endl;
                }
            }

            if (coeff==0)
            {
                coeff=1;
                cout<<"ok2"<<endl;
            }

            sommet.second.m_value = sommet.second.m_value + ( 0.0005*(sommet.second.m_value*(1-(sommet.second.m_value/coeff))));

            cout<< coeff<<" "<< sommet.second.m_value<<endl;
        }
    }
}

void Graph::effaSommet(int index, string f3)
{

    m_vertexeffacer.insert(pair<int,Vertex>(index,m_vertices[index]));

    for(auto &elem: m_edges)
    {
        if(elem.second.m_from==index || elem.second.m_to==index)
        {
            m_edgeseffacer.insert(pair<int,Edge>(index,m_edges[index]));
            effaceArrete(elem.first);
        }
    }
    Vertex &remver=m_vertices.at(index);

    if (m_interface && remver.m_interface)
    {
        m_interface->m_main_box.remove_child(remver.m_interface->m_top_box);
    }

    m_vertices.erase(index);


        ofstream fp(f3, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

            string nom_image;

        if(fp)  // si l'ouverture a réussi
        {
             m_ordre2++;
            fp<<m_ordre2<<endl;

            for (auto &it : m_vertexeffacer)
        {

                fp << it.first<<" ";
                fp << it.second.m_value<<" ";
                fp<<it.second.m_interface->m_top_box.get_frame_pos() .x<< " ";
                fp<<it.second.m_interface->m_top_box.get_frame_pos() .y<< " ";
                nom_image=it.second.m_interface->m_img.get_pic_name();
                nom_image.erase(nom_image.size()-4,4);
                fp<<nom_image + ".jpg" << endl;
        }
                 m_vertexeffacer.erase(index);

                fp.close();  // on referme le fichier
        }

        else  // sinon
        {

                cerr << "Erreur à l'ouverture !" << endl;
        }

               // m_vertexeffacer.erase(index);


}

void Graph::effaceArrete(int index)
{
    Edge &remed=m_edges.at(index);

    if (m_interface && remed.m_interface)
    {
        /// Ne pas oublier qu'on a fait ça à l'ajout de l'arc :
        /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
        /* m_interface->m_main_box.add_child(ei->m_top_edge);  */
        /* m_edges[idx] = Edge(weight, ei); */
        /// Le new EdgeInterface ne nécessite pas de delete car on a un shared_ptr
        /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
        /// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
        m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
    }


    std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
    std::vector<int> &veto = m_vertices[remed.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), index ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), index ), veto.end() );

    std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
    std::cout << m_edges.size() << std::endl;

    m_edges.erase(index);

}

void Graph::ajouter(int index, string f3)
{
    ifstream fp(f3, ios::in);  // on ouvre le fichier en lecture


    if(fp)  // si l'ouverture a réussi

    {
         int indice, coord_x, coord_y;
        double poids;
        string vignette;


        fp>>m_ordre2;

        for (int i=0; i<m_ordre2; i++)
        {
            fp>>indice;
            fp>>poids;
            fp>>coord_x;
            fp>>coord_y;
            fp>>vignette;

            if(indice==index && m_ordre2!=0)
            {
            add_interfaced_vertex2(index,poids,coord_x,coord_y,vignette);

            }
        }
        fp.close();  // on ferme le fichier
    }
    else  // sinon
    {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
    }
    cout <<"bien ajoutee";

    m_vertices.insert(pair<int,Vertex>(index,m_vertexeffacer[index]));

    for(auto &elem: m_edgeseffacer)
    {
        if(elem.second.m_from==index || elem.second.m_to==index)
        {
            m_edges.insert(pair<int,Edge>(index,m_edgeseffacer[index]));
            ajoutearrete(elem.first);
        }
    }

    Vertex &remver=m_vertexeffacer.at(index);

    if (m_interface && remver.m_interface)
    {
        m_interface->m_main_box.add_child(remver.m_interface->m_top_box);
    }

    m_vertexeffacer.erase(index);



 ofstream fichier(f3, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

        string nom_image;

        if(fichier)  // si l'ouverture a réussi
        {
            m_ordre2--;
            fichier<<m_ordre2;
                    for (auto &it : m_vertexeffacer)
        {
                fichier << it.first<<" ";
                fichier << it.second.m_value<<" ";
                fichier<<it.second.m_interface->m_top_box.get_frame_pos() .x<< " ";
                fichier<<it.second.m_interface->m_top_box.get_frame_pos() .y<< " ";
                nom_image=it.second.m_interface->m_img.get_pic_name();
                nom_image.erase(nom_image.size()-4,4);
                fichier<<nom_image + ".jpg" << endl;
        }
                fichier.close();  // on referme le fichier
        }

        else  // sinon
               {

                cerr << "Erreur à l'ouverture !" << endl;
               }


                 cout <<"bien ajoutee";
}
void Graph::ajoutearrete(int index)
{
    Edge &remver=m_edgeseffacer.at(index);

        if (m_interface && remver.m_interface)
    {
           m_interface->m_main_box.add_child( remver.m_interface->m_top_edge );
    }

    /// Il reste encore à virer l'arc supprimé de la liste des entrants et sortants des 2 sommets to et from !
    /// References sur les listes de edges des sommets from et to
   std::vector<int> &vefrom = m_vertexeffacer[remver.m_from].m_out;
    std::vector<int> &veto = m_vertexeffacer[remver.m_to].m_in;
    vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), index ), vefrom.end() );
    veto.erase( std::remove( veto.begin(), veto.end(), index ), veto.end() );

    /// Le Edge ne nécessite pas non plus de delete car on n'a pas fait de new (sémantique par valeur)
    /// Il suffit donc de supprimer l'entrée de la map pour supprimer à la fois l'Edge et le EdgeInterface
    /// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
   // m_edges.erase(eidx);  m_edges.erase(eidx);
    /// Tester la cohérence : nombre d'arc entrants et sortants des sommets 1 et 2
    std::cout << m_vertices[remver.m_from].m_in.size() << " " << m_vertexeffacer[remver.m_from].m_out.size() << std::endl;
    std::cout << m_vertices[remver.m_to].m_in.size() << " " << m_vertexeffacer[remver.m_to].m_out.size() << std::endl;
    std::cout << m_edgeseffacer.size() << std::endl;

     m_edgeseffacer.erase(index);
}


/// La méthode update à appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update(string f3)
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    if(m_interface->m_bouton1.clicked())
    {
        menuefface(f3);
    }

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();

    m_ordre=m_vertices.size();
    m_ordre2=m_vertexeffacer.size();

}

void Graph::menuefface(string f3)
{

    int j;
    cin >> j;

    effaSommet(j,f3);
}

void Graph::menuajoute(string f3)
{
    int i;
    cout << "ajoute : ";
    cin >> i;

    ajouter(i,f3);
}

/// Aide à l'ajout de sommets interfacés
void Graph::add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name, int pic_idx )
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
    m_vertices[idx] = Vertex(value, vi);
}

void Graph::add_interfaced_vertex2(int idx, double value, int x, int y, std::string pic_name, int pic_idx)
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
    m_vertexeffacer[idx] = Vertex(value, vi);
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
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);
}
