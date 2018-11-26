/* En-t�te du programme
====================
Programme:        Deplacement.h
Auteure:          Catherine Bronsard
Description:      D�placement (compos� de la ligne, de la colonne et de la direction)
                    peut �tre initialis� et manipul�

/ Directives au pr�-processeur
============================ */
#pragma once
#include "pch.h"

// Direction
enum DIRECTION { NORD = 0, EST = 1, SUD = 2, OUEST = 3, AUCUNE_DIRECTION = 4 }; // Directions numeriques
constexpr int ch_dir[5] = { 'N', 'E', 'S', 'O', 'A' };      // Lettre a utiliser selon direction
constexpr int xMove[5] = { 0, 1, 0, -1, 0 };                // Deplacement horizontal selon direction
constexpr int yMove[5] = { -1, 0, 1, 0, 0 };                // Deplacement vertical selon direction

class Deplacement
{
protected:
    DIRECTION _direction;   // direction vers laquelle le robot-pile va
    int _ligne;             // ligne dans la matrice
    int _col;               // colonne dans la matrice

public:
    /* Constructeurs */
    Deplacement() : _direction(NORD), _ligne(0), _col(0) {};
    Deplacement(int line, int col, DIRECTION dir);
    Deplacement(const Deplacement & d);

    /* Setteurs */
    void setDirection(DIRECTION dir);
    void setLigne(int line);
    void setCol(int col);

    /* Getteurs */
    DIRECTION getDirection() const;
    int getLigne() const;
    int getCol() const;

    /* Afficher/lire un d�placement */      // D�sactiv� depuis l'utilisation d'un enum au lieu de char
    //void print(std::ostream& out) const;
    //void read(std::istream& in);
};

// Op�rateurs pour afficher/lire
//std::ostream& operator<<(std::ostream& out, const Deplacement & d);
//std::istream& operator >> (std::istream & in, Deplacement& d);