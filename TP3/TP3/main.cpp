/**********************************************************
File  : main.cpp
Author: Anthony Cote
Date  : 2018-10-20
Goal  : Lance le jeu
**********************************************************/

#include "Game.h"

int main(int argc, const char **argv)
{
    srand(time(NULL));

    Game g;
    g.mainLoop();

    return 0;
}

/*

Aller voir ClassDiagram.cd
    Vous allez p-e avoir besoin d'installer ClassDesigner
    a partir du Menu Tools/GetToolsAndFeatures

Certaines classes sont plutot vieilles et mal codées
    on n'aura pas besoin de toutes les utiliser

N'hésitez pas a mettre en doute mes competences et a me poser des questions :

#typedef
#define
enum
pre-compiled header
...

*/