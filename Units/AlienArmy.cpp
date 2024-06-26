#include "AlienArmy.h"
#include "Unit.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"

AlienArmy::AlienArmy()
{
	Mindex = -1;
	
}

bool AlienArmy::getStatus()
{
	return status;
}

void AlienArmy::setStatus(bool b)
{
	status = b;
}

bool AlienArmy::GetASoldierToAttack(Unit*& u)
{
	if (AlienSoldiers.peek(u))	return true;
	return false;
}

void AlienArmy::AddAUnit(Unit * &u,bool head,bool tail)
	{
	if (dynamic_cast <AlienDrone*> (u) != NULL)
		if(head && !tail) AlienDrones.enqueueFirst(u);
		else if (head && tail) AlienDrones.enqueue(u);
		else if (AlienDrones.getCount() % 2 == 0)
			AlienDrones.enqueueFirst(u);
		else
			AlienDrones.enqueue(u);
		else if (dynamic_cast <AlienMonster*> (u) != NULL) {
			if (Mindex == 999) return;
			AlienMonsters[++Mindex] = u;
		}
		else if (dynamic_cast <AlienSoldier*> (u) != NULL)AlienSoldiers.enqueue(u);
}

int AlienArmy::GetMonstersCount()
{
	return Mindex+1;
}

int AlienArmy::GetDronesCount()
{
	return AlienDrones.getCount();
}


bool AlienArmy::GetAMonsterTobeAttacked(Unit*& u)
{
	srand(time(nullptr));
	if (Mindex == -1) return false;
	if (Mindex == 0){
		u = AlienMonsters[Mindex];
		AlienMonsters[Mindex--] = nullptr;
		return true;
	}
	int x = rand() % (Mindex + 1);
	if (x == Mindex) {
		u = AlienMonsters[Mindex];
		AlienMonsters[Mindex--] = nullptr;
		return true;
	}
	else {
		u = AlienMonsters[x];
		AlienMonsters[x] = nullptr;
		for (int i = x; i < Mindex; i++) {
			AlienMonsters[i] = AlienMonsters[i + 1];
			AlienMonsters[i + 1] = nullptr;
		}
		Mindex--;
		return true;
	}
	
}
bool AlienArmy::GetASoldierTobeAttacked(Unit*& u)
{
	if(AlienSoldiers.dequeue(u))	return true;
	return false;
}
bool AlienArmy::GetAMonsterToAttack(Unit*& u)
{
	if (Mindex == -1) return false;
	if (Mindex == 0) {
		u = AlienMonsters[Mindex];
		return true;
	}
	int x = rand() % (Mindex + 1);
		u = AlienMonsters[Mindex];
		return true;
}
bool AlienArmy::GetFirstDroneTobeAttacked(Unit*& u)
{
	if (AlienDrones.dequeue(u)) return true;
	return false;
}
bool AlienArmy::GetLastDroneTobeAttacked(Unit*& u)
{
	if (AlienDrones.dequeueLast(u)) return true;
	return false;

}
bool AlienArmy::GetFirstDroneToAttack(Unit*& u)
{

	if (AlienDrones.peek(u)) return true;
	return false;
}
bool AlienArmy::GetLastDroneToAttack(Unit*& u)
{
	if (AlienDrones.peekLast(u)) return true;
	return false;
}
int AlienArmy::GetSoldiersCount()
{
	return AlienSoldiers.getCount();
}
bool AlienArmy::IsEmptyASoldier()
{
	if (AlienSoldiers.isEmpty()) return true;
	else return false;
}
bool AlienArmy::IsEmptyADrones()
{
	if (AlienDrones.isEmpty()) return true;
	else return false;
}
bool AlienArmy::IsEmptyAMonster()
{
	if (Mindex == -1) return true;
	else return false;
}

void AlienArmy::PrintAlianArmyInfo()
{
	UnitLinkedQueue MonstersTempList;
	Unit* unit;
	int Count;
	cout << "==========" << " Alian Army Alive Units " << "==========\n";
	AlienSoldiers.print(" AS ");
	Count = Mindex + 1;
	cout << Count << " AM " << "[";
	/*for (int i = 0; i < Count; i++)
	{                  /// need to be modified
		GetAMonster(unit);
		cout << unit->GetID();
		AddAUnit(unit);
		if (i < Count - 1)	cout << ", ";
	}*/
	for (int i = 0; i < Count; i++)
	{
		GetAMonsterTobeAttacked(unit);
		cout << unit->GetID();
		MonstersTempList.enqueue(unit);
		if (i < Count - 1)	cout << ", ";
	}
	cout << "]" << endl;
	// move the monsters back to their list
	while (MonstersTempList.dequeue(unit))
		AddAUnit(unit);
	AlienDrones.print();
}

AlienArmy::~AlienArmy()
{
	//free reserved memory//
	Unit* unit;
	int Count;
	Count = AlienSoldiers.getCount();
	for (int i = 0; i < Count; i++)
	{
		AlienSoldiers.dequeue(unit);
		delete unit;
	}
	Count = Mindex + 1;
	for (int i = 0; i < Count; i++)
	{
		delete AlienMonsters[i];
	}
	Count = AlienDrones.getCount();
	for (int i = 0; i < Count; i++)
	{
		AlienDrones.dequeue(unit);
		delete unit;
	}
}
