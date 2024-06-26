#ifndef _GENERATOR_H_
#define	_GENERATOR_H_

#include	<iostream>
#include	<fstream>
#include	<string>
#include	"../Game/Game.h"
#include	"../Units/Unit.h"

using namespace std;
class Game;
class Generator{
private:
	int Data[20];
	/*
	index 0		UnitNum
	index 1:3	percentage for Earth : Solider, Tank, Gunner.
	index 4:6	percentage for Alien : Solider, Monster, Drone.
	index 7		percent to generate new unit(prob)
	index 8:13	Power, Health, AttackCapacity for EarthUnits
	index 14:19	Power, Health, AttackCapacity for AleinUnits
	*/
	int AlienID;
	int EarthID;
	Game* game;
public:
	Generator(Game* g);
	void Execute();
	void SetDate(int data[]);
	~Generator();
};
#endif