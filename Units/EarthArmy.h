#pragma once
#include    "../Data Structure/UnitLinkedQueue.h"
#include    "../Data Structure/UnitStack.h"
#include    "../Data Structure/UnitpriQueue.h"
#include	"../Units/Unit.h"
#include	"../Units/EarthGunnery.h"
#include	"EarthSoldier.h"
#include	"EarthGunnery.h"
#include	"EarthTank.h"
class UnitpriQueue;
class EarthArmy
{
private:
	UnitLinkedQueue EarthSoldiers;
	UnitStack EarthTanks;
	UnitpriQueue EarthGunners;
	bool status;

public:
	EarthArmy();
	bool getStatus();
	void setStatus(bool b);
	void AddAUnit(Unit*& u);

	bool GetASoldierToAttack(Unit*& u); //Peek on EarthSoldier
	bool GetATankToAttack(Unit*& u);	//Peek on EarthTank
	bool GetAGunneryToAttack(Unit*& u);	//Peek on EarthGunnery

	bool GetASoldierTobeAttacked(Unit*& u);	//dequeue EarthSoldier
	bool GetATankTobeAttacked(Unit*& u);	//dequeue EarthTank
	bool GetAGunneryTobeAttacked(Unit*& u);	//dequeue EarthGunnery
	
	
	bool IsEmptySoldiers();//Check If LinkedQueue EarthSoldiers is empty
	bool IsEmptyTanks();//Check If ArrayStack EarthTanks is empty
	bool IsEmptyGunners();//Check If priQueue EarthGunners is empty

	int GetSolidersCount();
	int GetTanksCount();
	int GetGunnersCount();

	void PrintEarthArmyInfo();//Print the AlienArmy Units ID
	~EarthArmy();
};

