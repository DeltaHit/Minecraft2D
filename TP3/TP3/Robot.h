/* En-t�te du programme
====================
Programme:        Robot.h
Auteure:          Catherine Bronsard
Description:      pile de d�placements qui peut ajouter, enlever et s'initialiser avec un d�placement
                    et peut �tre manipul�e

/ Directives au pr�-processeur
============================ */
#pragma once
#include "pch.h"

#include "stack.h"
#include "Deplacement.h"

class Robot
{
protected:
    stack<Deplacement> _pile;                           // pile des d�placements effectu�s
public:
    Robot() {};                                         // constructeur sans parametres
    Robot(int line, int col);                           // initialiser � la position de d�part
    void init(int line, int col);                       // initialiser � la position de d�part

    void deplacer(int line, int col, DIRECTION dir);    // ajouter un d�placement
    void revenir();                                     // revenir en arri�re (enlever un d�placement)
    void changeDir(DIRECTION newDir);                   // changer la direction
    bool empty();

    Deplacement getLastDeplacement() const;             // Retourne le dernier deplacement
    DIRECTION getDir()const;                            // Retourne la direction
};
