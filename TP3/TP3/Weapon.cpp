#pragma once
#include "Weapon.h"

void Weapon::setUzi()
{
	_accuracy = 2;
	_totalDelay = 5;
	_bulletSpeed = 1;
	_damageMultiplier = 1;
}

void Weapon::setAssault()
{
	_accuracy = 1;
	_totalDelay = 3;
	_bulletSpeed = 1.5;
	_damageMultiplier = 2;
}

void Weapon::setSniper()
{
	_accuracy = 1;
	_totalDelay = 10;
	_bulletSpeed = 4;
	_damageMultiplier = 4;
}

void Weapon::setCustom(float accuracy, int rateOfFire, float bulletSpeed, float damageMultiplier)
{
	_accuracy = accuracy;
	_totalDelay = rateOfFire;
	_bulletSpeed = bulletSpeed;
	_damageMultiplier = damageMultiplier;
}

float Weapon::getAccuracy()
{
	return _accuracy;
}

int Weapon::getRateOfFire()
{
	return _totalDelay;
}

float Weapon::getBulletSpeed()
{
	return _bulletSpeed;
}

float Weapon::getDamageMultiplier()
{
	return _damageMultiplier;
}

AngleDegree Weapon::getFireAngle()
{
	return _fireAngle;
}

void Weapon::setAccuracy(float accuracy)
{
	_accuracy = accuracy;
}

void Weapon::setRateOfFire(int rateOfFire)
{
	_totalDelay = rateOfFire;
}

void Weapon::setBulletSpeed(float bulletSpeed)
{
	_bulletSpeed = bulletSpeed;
}

void Weapon::getDamageMultiplier(float damageMultiplier)
{
	_damageMultiplier = damageMultiplier;
}

void Weapon::setFireAngle(AngleDegree fireAngle)
{
	_fireAngle = fireAngle;
}