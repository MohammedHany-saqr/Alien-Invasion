#ifndef _GAME_H_
#define _GAME_H_

#include "../Units/AlienArmy.h"
#include "../Units/EarthArmy.h"
#include "../Generator/Generator.h"
#include "../Data Structure/UnitLinkedQueue.h"
#include "../Units/Unit.h"
#include"windows.h"
class Generator;
class AlienArmy;
class EarthArmy;
class Game {
private:
	AlienArmy *AArmy;
	EarthArmy *EArmy;
	UnitLinkedQueue KilledList;
	Generator *Gen1;
	bool status;
	bool MOD;
	int TimeStep;
public:
	Game();
	void StartGame();
	void DataChecker(int Data[]);
	void LoadFromFile();
	bool GetMod();
	AlienArmy* GetAlienArmy();
	EarthArmy* GetEarthArmy();
	void PushKilledUnit(Unit*&u);
	void PrintKilledUnitsInfo();
	int GetTimeStep();
	void setColor(int color);
	void createOutput();
	~Game();
	
};
#endif // !ARENA_H
