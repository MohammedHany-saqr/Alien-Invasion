#include "Generator.h"
#include "../Game/Game.h"
#include "../Units/AlienSoldier.h"
#include "../Units/AlienSoldier.h"
#include "../Units/AlienMonster.h"
#include "../Units/AlienDrone.h"
#include "../Units/EarthSoldier.h"
#include "../Units/EarthTank.h"
#include "../Units/EarthGunnery.h"
#include<time.h>
Generator::Generator(Game* g){
	AlienID = 1999;
	EarthID = 0;
	game = g;
}

void Generator::Execute() {
			int n = rand() % 101;
			Unit* unit;
			int TimeStep = game->GetTimeStep();
			if (n <= Data[7])           //if the random number <= prob --> generate units
			{    
				//EarthArmy IMPELEMTION
				for (int i = 0; i < Data[0]; i++) {
					n = rand() % 101;
					int UPower = Data[8] + (rand() % (Data[9] - Data[8]));		//EarthUnitPower Rand;
					int UHealth = Data[10] + (rand() % (Data[11] - Data[10]));	//EarthUnitHealth Rand;
					int UCapacity = Data[12] + (rand() % (Data[13] - Data[12]));//EarthUnitCapacity Rand;
					if (n < Data[1]) {// Generates Earth Soldier
						 unit = new EarthSoldier(++EarthID, UPower, UHealth, UCapacity,TimeStep);
						 game->GetEarthArmy()->AddAUnit(unit);
					}
					else if (n < Data[1] + Data[2]) {// Generates Earth Tank
						Unit* unit = new EarthTank(++EarthID, UPower, UHealth, UCapacity, TimeStep);
						game->GetEarthArmy()->AddAUnit(unit);
					}
					else {// Generates Earth 
						 unit = new EarthGunnery(++EarthID, UPower, UHealth, UCapacity, TimeStep);
						 game->GetEarthArmy()->AddAUnit(unit); // The problem
					}
					unit = nullptr;
				}
				//AlianArmy IMPELEMTION
				for (int i = 0; i < Data[0]; i++) {
					n = rand() % 101;
					int UPower = Data[14] + (rand() % (Data[15] - Data[14]));//AlienUnitPower Rand;
					int UHealth = Data[16] + (rand() % (Data[17] - Data[16]));//AlienUnitHealth Rand;
					int UCapacity = Data[18] + (rand() % (Data[19] - Data[18]));//AlineUnitCapacity Rand;
					if (n < Data[4]) {
						//Generate Alien Solider
						unit = new AlienSoldier(++AlienID, UPower, UHealth, UCapacity, TimeStep);
						game->GetAlienArmy()->AddAUnit(unit);
					}
					else if (n < Data[4] + Data[5]) {
						//Generate AlienMonster
						unit = new AlienMonster(++AlienID, UPower, UHealth, UCapacity, TimeStep);
						game->GetAlienArmy()->AddAUnit(unit);
					}
					else {
						//Generate AlienDrone
						unit = new AlienDrone(++AlienID, UPower, UHealth, UCapacity, TimeStep);
						game->GetAlienArmy()->AddAUnit(unit);
					}
					unit = nullptr;
				}
			}
			else return;
}

void Generator::SetDate(int data[])
{
	for (int i = 0; i < 20; i++) Data[i] = data[i];
}

Generator::~Generator()
{
}
