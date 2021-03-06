#pragma once
#include "MagnetPosition.h"

tile_t MagnetPosition::getGridCol()const { return _gridC; }; 
tile_t MagnetPosition::getGridLine()const { return _gridL; };
pixel_t MagnetPosition::getExactX()const { return _exactX; };
pixel_t MagnetPosition::getExactY()const { return _exactY; };

// Copie la position
void MagnetPosition::setPosition(MagnetPosition & mp)
{
    _exactX = mp._exactX;
    _exactY = mp._exactY;
    _gridC = mp._gridC;
    _gridL = mp._gridL;
}

// Teleporte le personnage
void MagnetPosition::setPositionInGrid(tile_t x, tile_t y)
{
    _gridC = x;
    _gridL = y;
    _exactX = x * RATIO + RATIO / 2;
    _exactY = y * RATIO + RATIO / 2;
}

// Teleporte le personnage
void MagnetPosition::setPositionExact(pixel_t x, pixel_t y)
{
    _exactX = x;
    _exactY = y;
    _gridC = x / RATIO;
    _gridL = y / RATIO;
}

// Teleporte le personnage
void MagnetPosition::move(pixel_t x, pixel_t y)
{
    setPositionExact(_exactX + x, _exactY + y);
    //_exactX += x / RATIO;
    //_exactY += y / RATIO;
    //_gridC += x;
    //_gridL += y;
}

// Met a jour la position dans la grille selon la position exacte
void MagnetPosition::updateGridPosition()
{
    _gridC = (pixel_t)_exactX / RATIO;
    _gridL = (pixel_t)_exactY / RATIO;
}

// Evalu si la position exacte est au centre d'une case
bool MagnetPosition::isGridCentered()const
{
    return
        ((int)_exactX == (_gridC * RATIO) + RATIO / 2) &&
        ((int)_exactY == (_gridL * RATIO) + RATIO / 2);
}