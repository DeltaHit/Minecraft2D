/*****************************************************************************
File  : TopDownCharacter.h
Author: Anthony Cote
Date  : 2018-04-23
Goal  : Defini un personnage vu de dessus qui peux se deplacer selon x et y
******************************************************************************/

#pragma once
#include "pch.h"

#include "Character.h"

class TopDownCharacter : public Character
{
protected:
    DIR8 _direction;        // Direction ou il regarde
    bool _isWalking;        // Si en train de marcher
    float _length;          // Vitesse de déplacement
public:
    TopDownCharacter() : _direction(DOWN), _isWalking(false), _length(0) {};
    void init();                            //

    // Get
    DIR8 getDirection();                    //
    float getLength();                      //
    bool isWalking();                       //

    // Set
    void setDirection(DIR8 dir);            // Change la direction du personnage
    void isWalking(bool isWalking);         //

    // Move
    void move();                            // Micro déplacement du personnage
    void move(DIR8 dir);                    // Deplace dans une direction
    void move(pixel_t plusX, pixel_t plusY);// Micro déplacement du personnage

    void stayThere();// Theoriquement ca fait rien mais pratiquement ca empeche un bug qu'il restait pris
};
