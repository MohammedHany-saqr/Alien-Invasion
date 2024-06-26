#ifndef _ALIEN_ARMY_H_
#define _ALIEN_ARMY_H_
#include	<iostream>
#include	"../Data Structure/UnitLinkedQueue.h"
#include	"Unit.h"
#include	"../Data Structure/UnitDoubleEndedQueue.h"

class Unit;
class AlienArmy {
private:
	UnitLinkedQueue AlienSoldiers;
	UnitDoubleEndedQueue AlienDrones;
	Unit* AlienMonsters[1000];
	int Mindex;
	bool status;

public:
	AlienArmy();
	bool getStatus();
	void setStatus(bool b);	
	void AddAUnit(Unit*& u,bool head=false,bool tail=false);

	bool GetASoldierToAttack(Unit*& u);	//Peek on AlienSolider
	bool GetAMonsterToAttack(Unit*& u);	//Peek on MonsterSolider
	bool GetFirstDroneToAttack(Unit*& u);	//Peek on First DroneSolider
	bool GetLastDroneToAttack(Unit*& u);	//Peek on Last DroneSolider

	bool GetASoldierTobeAttacked(Unit*& u);	//dequeue AlienSolider
	bool GetAMonsterTobeAttacked(Unit*& u);	//dequeue MonsterSolider
	bool GetFirstDroneTobeAttacked(Unit*& u);	//dequeue First DroneSolider
	bool GetLastDroneTobeAttacked(Unit*& u);	//dequeue Last DroneSolider
	
	int GetSoldiersCount();
	int GetMonstersCount();
	int GetDronesCount();
	
	bool IsEmptyASoldier();		//Check If LinkedQueue AlienSoldier is empty
	bool IsEmptyADrones(); //Check If DoubleEndedQueue AlienDrones is empty
	bool IsEmptyAMonster();	//Check If Array AlienMonster is empty

	void PrintAlianArmyInfo(); //Print the AlienArmy Units ID
	~AlienArmy();
};
#endif // !Alien_Army_H