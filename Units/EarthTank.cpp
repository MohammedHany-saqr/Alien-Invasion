#include "EarthTank.h"

EarthTank::EarthTank(int id, int p, int h, int c, int tj):Unit(id,p,h,c, tj)
{
	AttackSoldiers = false;
}

void EarthTank::Attack(Game* g)
{
	AlienArmy* AA = g->GetAlienArmy();
	if (AA->GetMonstersCount() == 0) return;

	UnitLinkedQueue MonstersTempList;
	UnitLinkedQueue SoldiersTempList;
	Unit* AttackedUnit = nullptr;

	int NumOfAttackedMonsters;
	int NumOfAttackedSoldiers;
	CheckAttackSoldiers(g);
	if (AttackSoldiers)
	{
	    NumOfAttackedSoldiers = Capacity / 2;
		NumOfAttackedMonsters = Capacity - NumOfAttackedSoldiers;       
	}
	else
	{
		NumOfAttackedSoldiers = 0;
		NumOfAttackedMonsters = Capacity;
	}
	for (int i = 0; i < NumOfAttackedMonsters && AA->GetAMonsterTobeAttacked(AttackedUnit); i++)
			MonstersTempList.enqueue(AttackedUnit);

	for (int i = 0; i < NumOfAttackedSoldiers && AA->GetASoldierTobeAttacked(AttackedUnit); i++)
			SoldiersTempList.enqueue(AttackedUnit);

	NumOfAttackedMonsters = MonstersTempList.getCount();
	NumOfAttackedSoldiers = SoldiersTempList.getCount();
	if (g->GetMod())
	{
		MonstersTempList.fightingPrint("ET ", ID);
		if(AttackSoldiers)
			SoldiersTempList.fightingPrint("ET ", ID);
	}
	double damage = (Power * (Health / 100));
	// Attack monsters
	for (int i = 0; i < NumOfAttackedMonsters; i++)
	{
		MonstersTempList.dequeue(AttackedUnit);
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
		if (AttackedUnit->getTa() == 0)		//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			MonstersTempList.enqueue(AttackedUnit);
	}
	//attack soldiers
	for (int i = 0; i < NumOfAttackedSoldiers; i++)
	{
		SoldiersTempList.dequeue(AttackedUnit);
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
		if (AttackedUnit->getTa() == 0)		//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			SoldiersTempList.enqueue(AttackedUnit);
	}
	// move the attacked units back to their original list in the correct order
	while (MonstersTempList.dequeue(AttackedUnit))
		AA->AddAUnit(AttackedUnit);

	if (!SoldiersTempList.isEmpty()) {
		while (AA->GetASoldierTobeAttacked(AttackedUnit))
			SoldiersTempList.enqueue(AttackedUnit);
		while (SoldiersTempList.dequeue(AttackedUnit))
			AA->AddAUnit(AttackedUnit);
	}

}

void EarthTank::CheckAttackSoldiers(Game* g)
{
	AlienArmy* AA = g->GetAlienArmy();
	EarthArmy* Ea = g->GetEarthArmy();
	double ASoldierNum = AA->GetSoldiersCount();
	double ESoldierNum = Ea->GetSolidersCount();
	double EASoldiersPercentage = ESoldierNum / ASoldierNum;
	if (EASoldiersPercentage < 0.3)
		AttackSoldiers = true;
	if (EASoldiersPercentage >= 0.8)
		AttackSoldiers = false;
}
