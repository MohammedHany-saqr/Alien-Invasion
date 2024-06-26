#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(int id, int p, int h, int c, int tj):Unit(id,p,h,c, tj)
{
}

void AlienSoldier::Attack(Game *g)
{
	EarthArmy* EA = g->GetEarthArmy();
	if (EA->GetSolidersCount() == 0) return;

	UnitLinkedQueue TempList;
	Unit* AttackedUnit = nullptr;

	int NumOfAttackedSoldiers = this->Capacity;
	for (int i = 0; i < NumOfAttackedSoldiers && EA->GetASoldierTobeAttacked(AttackedUnit); i++)
			TempList.enqueue(AttackedUnit);
	NumOfAttackedSoldiers = TempList.getCount();
	if (g->GetMod())
		TempList.fightingPrint("AS ", ID);
	double damage = (Power * (Health / 100));
	for (int i = 0; i < NumOfAttackedSoldiers; i++)
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
	while (EA->GetASoldierTobeAttacked(AttackedUnit))
		TempList.enqueue(AttackedUnit);
	while (TempList.dequeue(AttackedUnit))
		EA->AddAUnit(AttackedUnit);
}
