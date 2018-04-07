#include "grman/grman.h"
#include <iostream>

#include "graph.h"

int main()
{
    /// A appeler en 1er avant d'instancier des objets graphiques etc...
    grman::init();

    /// Le nom du répertoire où se trouvent les images à charger
    grman::set_pictures_path("pics");

    /// Un exemple de graphe
    Graph g;

    std::string f1;
    std::string f2;

    BITMAP *accueil_retour;
    BITMAP *background_menu;
    BITMAP *titre;
    BITMAP *eco1;
    BITMAP *eco2;
    BITMAP *eco3;
    BITMAP *quitter;
    BITMAP *buffer_menu;

    int choix=0;
    background_menu=load_bitmap("background.bmp",NULL);
    if (!background_menu)
    {
        printf("background se lance pas\n");
        exit(EXIT_FAILURE);

    }

    titre=load_bitmap("titre.bmp",NULL);
    if (!titre)
    {
        printf("titre se lance pas\n");
        exit(EXIT_FAILURE);

    }
    quitter=load_bitmap("quitter.bmp",NULL);
    if (!quitter)
    {
        printf("quitter se lance pas\n");
        exit(EXIT_FAILURE);

    }

    eco1=load_bitmap("eco1.bmp",NULL);
    if (!eco1)
    {
        printf("eco1 se lance pas\n");
        exit(EXIT_FAILURE);

    }

    eco2=load_bitmap("eco2.bmp",NULL);
    if (!eco2)
    {
        printf("eco2 se lance pas\n");
        exit(EXIT_FAILURE);

    }
    eco3=load_bitmap("eco3.bmp",NULL);
    if (!eco3)
    {
        printf("eco3 se lance pas\n");
        exit(EXIT_FAILURE);

    }





    buffer_menu  = create_bitmap(SCREEN_W,SCREEN_H);

    /////

    while (!((mouse_b&1)&&((mouse_x<500)&&(mouse_x>300)&&(mouse_y<310)&&(mouse_y>250))||((mouse_b&1)&&((mouse_x<500)&&(mouse_x>300)&&(mouse_y<410)&&(mouse_y>350))) || ((mouse_b&1)&&((mouse_x<500)&&(mouse_x>300)&&(mouse_y<510)&&(mouse_y>450))) ))
    {

        blit(background_menu,buffer_menu,0,0,0,0,SCREEN_W,SCREEN_H);
        show_mouse(screen);


        if (((mouse_x<465)&&(mouse_x>325)&&(mouse_y<(525+56))&&(mouse_y>525)))///quitter zone
        {
            rectfill(buffer_menu, 325, 525, 465, 525+56, makecol(255,0,0));

        }
        if (((mouse_x<500)&&(mouse_x>300)&&(mouse_y<510)&&(mouse_y>450))) ///eco3
        {
            rectfill(buffer_menu, 300, 450, 500, 510, makecol(255,0,0));
            choix=3;

        }
          if (((mouse_x<500)&&(mouse_x>300)&&(mouse_y<410)&&(mouse_y>350)))///eco2
        {
            rectfill(buffer_menu, 300, 350, 500, 410, makecol(255,0,0));
           choix=2;

        }

        if (((mouse_x<500)&&(mouse_x>300)&&(mouse_y<310)&&(mouse_y>250)))///eco1
        {
            rectfill(buffer_menu, 300, 250, 500, 310, makecol(255,0,0));
            choix=1;
        }

        if ((mouse_b&1)&&((mouse_x<500)&&(mouse_x>300)&&(mouse_y<310)&&(mouse_y>250)))



        if ((mouse_b&1)&&((mouse_x<500)&&(mouse_x>300)&&(mouse_y<410)&&(mouse_y>350)))///eco2



        if ((mouse_b&1)&&((mouse_x<500)&&(mouse_x>300)&&(mouse_y<510)&&(mouse_y>450)))


        if (((mouse_x<600+150)&&(mouse_x>600)&&(mouse_y<(60+27))&&(mouse_y>60)))
        {
            rectfill(buffer_menu, 600, 60, 600+150, 60+27, makecol(0,0,0));
        }

        if ((mouse_b&1)&&((mouse_x<465)&&(mouse_x>325)&&(mouse_y<(525+56))&&(mouse_y>525))) ///quitter
        {
            exit(0);
              // return 0;
        }

        draw_sprite(buffer_menu,eco1,300,250);
        draw_sprite(buffer_menu,eco2,300,350);
        draw_sprite(buffer_menu,eco3,300,450);
        draw_sprite(buffer_menu,quitter,325,525);
        draw_sprite(buffer_menu,titre,230,50);



        blit(buffer_menu,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(10);


    }

     if(choix==1)
    {
        f1 = "coord.txt";
        f2 = "matrice.txt";

    }

    else if(choix==2)
    {


    }

    else if(choix==3)
    {



    }


    g.make_example(f1,f2);



    /// Vous gardez la main sur la "boucle de jeu"
    /// ( contrairement à des frameworks plus avancés )
    while ( !key[KEY_ESC] )
    {
        /// Il faut appeler les méthodes d'update des objets qui comportent des widgets
        g.update();

        /// Mise à jour générale (clavier/souris/buffer etc...)
        grman::mettre_a_jour();

        g.save(f1);
    }



    grman::fermer_allegro();



    return 0;
}
END_OF_MAIN();


