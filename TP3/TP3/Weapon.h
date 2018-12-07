/*****************************************************************************
File  : Weapon.h
Author: Anthony Cote
Date  : 2018-05-05
Goal  : TODO : Gere des pattern compliquer de bullet
******************************************************************************/
#pragma once

#include "pch.h"

#include "Bullet.h"
#include "Delay.h"
//#include "AngleDegree.hpp"

class Weapon : public Delay
{
protected:

	float _accuracy;			//D�termine une variation dans _angle
	float _bulletSpeed;			//Vitesse des bullets
	float _damageMultiplier;	//Multiplicateur de dommages

	AngleDegree _fireAngle;			//Angle o� les balles sont tir�s

public:

	void setUzi();
	void setAssault();
	void setSniper();
	void setCustom(float, int, float, float);

	float getAccuracy();
	int getRateOfFire();
	float getBulletSpeed();
	float getDamageMultiplier();
	AngleDegree getFireAngle();

	void setAccuracy(float);
	void setRateOfFire(int);
	void setBulletSpeed(float);
	void getDamageMultiplier(float);
	void setFireAngle(AngleDegree);

	//void shootBullets(Entity& shooter, list<Bullet>& goodBullets, int pattern, Entity& target);
	//void shootStraightBullet(Entity& shooter, list<Bullet>& goodBullets, int degree = 0);

	//void shootAimedBullet(Entity & shooter, list<Bullet>& goodBullets, Entity & target);
};

//// Tire des projectiles en fonction du style
//void Weapon::shootBullets(Entity& shooter, list<Bullet>& goodBullets, int pattern, Entity& target)
//{
//
//    switch (pattern)
//    {
//    case 0: // Straight
//        //shootStraightBullet(shooter, goodBullets, 0);
//        break;
//    case 1: // Wide
//        //shootStraightBullet(shooter, goodBullets, -5);
//        //shootStraightBullet(shooter, goodBullets, 0);
//        //shootStraightBullet(shooter, goodBullets, 5);
//        break;
//    case 2: // Aimed
//        //shootAimedBullet(shooter, goodBullets, target);
//        break;
//    default:
//        break;
//    }
//}

//// Lance un projectile en ligne droite
//void Weapon::shootStraightBullet(Entity& shooter, list<Bullet>& goodBullets, int degree)
//{
//    int signe = (degree < 0 ? -1 : 1);
//
//    refreshDelay();
//    Bullet newBullet;               // TODO -5 degree converti en radian, math ignore minus?
//    //newBullet.setDirectionDegree(shooter.getDirectionDegree() + signe * shooter.radianFromDegree(abs(degree)));
//    newBullet.setSpeed(4.f);
//    newBullet.setHitBoxSize(5.f);
//    //newBullet.setCoord(shooter.getX(), shooter.getY() - 5);
//    goodBullets.push_back(newBullet);
//
//}

//// Lance un projectile en ligne droite
//void Weapon::shootAimedBullet(Entity& shooter, list<Bullet>& goodBullets, Entity& target)
//{
//
//
//    refreshDelay();
//    Bullet newBullet;
//    //newBullet.setDirectionDegree(shooter.getDirectionDegree());// + degree);
//    newBullet.setSpeed(4.f);
//    newBullet.setHitBoxSize(5.f);
//    //newBullet.setCoord(shooter.getX(), shooter.getY() - 5);
//
//    goodBullets.push_back(newBullet);
//
//}