#include "EarthSoldier.h"
#include "AlienArmy.h"
#include    "../Data Structure/UnitLinkedQueue.h"
EarthSoldier::EarthSoldier(int id, int p, int h, int c, int tj) :Unit(id, p, h, c, tj)
{
}

void EarthSoldier::Attack(Game *g)
{
	AlienArmy* AA = g->GetAlienArmy();
	if (AA->GetSoldiersCount() == 0) return;
	UnitLinkedQueue TempList;
	Unit* AttackedUnit = nullptr;
	for (int i = 0; i < this->Capacity; i++)
	{
		if (AA->GetASoldierTobeAttacked(AttackedUnit))
			TempList.enqueue(AttackedUnit);
		else break;
	}
	if (g->GetMod())
		TempList.fightingPrint("ES ",ID);
	int TempCount = TempList.getCount();
	double damage = (Power * (Health / 100));
	for (int i =0 ;i < TempCount;i++)
	{
		TempList.dequeue(AttackedUnit);
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
		if (AttackedUnit->getTa() == 0)		//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			TempList.enqueue(AttackedUnit);
	}
	// move the attacked units back to their original list in the correct order
	while (AA->GetASoldierTobeAttacked(AttackedUnit))
		TempList.enqueue(AttackedUnit);
	while (TempList.dequeue(AttackedUnit))
		AA->AddAUnit(AttackedUnit);
}
