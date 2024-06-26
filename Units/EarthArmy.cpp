#include "EarthArmy.h"

EarthArmy::EarthArmy()
{
	status = false;
}

bool EarthArmy::getStatus()
{
	return status;
}

void EarthArmy::setStatus(bool b)
{
	status = b;
}


bool EarthArmy::GetASoldierTobeAttacked(Unit*& u)
{
	if (EarthSoldiers.dequeue(u))	return true;
	else
	{
		u = NULL;
		return false;
	}
}

bool EarthArmy::IsEmptySoldiers()
{
	if (EarthSoldiers.isEmpty()) return true;
	else return false;
}

bool EarthArmy::IsEmptyTanks()
{
	return EarthTanks.isEmpty();
}

bool EarthArmy::IsEmptyGunners()
{
	return EarthGunners.isEmpty();
}

int EarthArmy::GetSolidersCount()
{
	return EarthSoldiers.getCount();
}

int EarthArmy::GetTanksCount()
{
	return EarthTanks.getCount();
}

int EarthArmy::GetGunnersCount()
{
	return EarthGunners.getCount();
}

void EarthArmy::PrintEarthArmyInfo()
{
	cout << "==========" << " Earth Army Alive Units " << "==========\n";
	//Print Earth Soldiers Info
	EarthSoldiers.print(" ES ");
	//Print Earth Tanks Info
	EarthTanks.print();
	//Print Earth Gunners Info
	EarthGunners.print();
}

bool EarthArmy::GetASoldierToAttack(Unit*& u)
{
	if (EarthSoldiers.peek(u))	return true;
	else
	{
		u = NULL;
		return false;
	}
}

bool EarthArmy::GetATankToAttack(Unit*& u)
{
	if (EarthTanks.peek(u))
		return true;
	else
	{
		u = NULL;
		return false;
	}
}

bool EarthArmy::GetAGunneryToAttack(Unit*& u)
{
	int Pri;            //unit priority
	if (EarthGunners.peek(u, Pri))
		return true;
	else
	{
		u = NULL;
		return false;
	}
}

EarthArmy::~EarthArmy()
{
	Unit* unit;
	int Count;
	Count = EarthSoldiers.getCount();
	for (int i = 0; i < Count; i++)
	{
		EarthSoldiers.dequeue(unit);
		delete unit;
	}
	Count = EarthTanks.getCount();
	for (int i = 0; i < Count; i++)
	{
		EarthTanks.pop(unit);
		delete unit;
	}
	int Pri;
	Count = EarthGunners.getCount();
	for (int i = 0; i < Count; i++)
	{
		EarthGunners.dequeue(unit,Pri);
		delete unit;
	}
}



bool EarthArmy::GetATankTobeAttacked(Unit*& u)
{
	if (EarthTanks.pop(u))
		return true;
	else
	{
		u = NULL;
		return false;
	}
}

void EarthArmy::AddAUnit(Unit*& u)
{
	if (dynamic_cast <EarthSoldier*> (u) != NULL) EarthSoldiers.enqueue(u);
	else if (dynamic_cast <EarthTank*> (u) != NULL)EarthTanks.push(u);
	else if (dynamic_cast <EarthGunnery*> (u) != NULL)EarthGunners.enqueue(u,u->GetHealth()+u->GetPower());
}


bool EarthArmy::GetAGunneryTobeAttacked(Unit*& u)
{
	int Pri;            //unit priority
	if (EarthGunners.dequeue(u,Pri))
		return true;
	else
	{
		u = NULL;
		return false;
	}
}



