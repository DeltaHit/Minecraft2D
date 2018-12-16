/*****************************************************************************
File  : Killable.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : Permet d'etre tuable avec des hp
******************************************************************************/
#pragma once

#include "pch.h"

class Killable
{
protected:
    int _hp;
    int _hpMax;

public:
    Killable() : _hp(5), _hpMax(5) {};  // Constructeur

    int getHp();                        // Retourne les HP
    int getHpMax();                     // Retourne le nombre de HP Max

    void setHp(int hp);                 // Change les HP
    void setHpMax(int hpMax);           // Change le nombre de HP max

    void loseHp(int hpLost);            // Fait perdre des HP
    void die();                         // Le personnage meurt
    void refillHp();

    bool isAlive();                     // Retourne si est en vie
    bool isDead();                      // Retourne si est mort
};
