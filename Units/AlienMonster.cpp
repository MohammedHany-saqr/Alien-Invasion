#include "AlienMonster.h"

AlienMonster::AlienMonster(int id, int p, int h, int c, int tj):Unit(id, p, h, c, tj)
{
}

void AlienMonster::Attack(Game *g)
{
	EarthArmy* EA = g->GetEarthArmy();
	if (EA->GetSolidersCount() == 0 && EA->GetTanksCount() == 0)	return;
	UnitStack TempList;
	UnitLinkedQueue TanksTempList;
	UnitLinkedQueue SoldiersTempList;
	Unit* AttackedUnit = nullptr;

	int NumOfAttackedSoldiers = this->Capacity/2;
	int NumOfAttackedTanks = this->Capacity- NumOfAttackedSoldiers;

	for (int i = 0; i < NumOfAttackedTanks && EA->GetATankTobeAttacked(AttackedUnit); i++)
		TanksTempList.enqueue(AttackedUnit);
	for (int i = 0; i < NumOfAttackedSoldiers && EA->GetASoldierTobeAttacked(AttackedUnit); i++)
		SoldiersTempList.enqueue(AttackedUnit);

	NumOfAttackedTanks = TanksTempList.getCount();
	NumOfAttackedSoldiers = SoldiersTempList.getCount();

	if (g->GetMod())
	{
		TanksTempList.fightingPrint("AM ", ID);
		SoldiersTempList.fightingPrint("AM ", ID);
	}

	double damage = (Power * (Health / 100));
	for (int i = 0; i < NumOfAttackedTanks; i++)
	{
		TanksTempList.dequeue(AttackedUnit);
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
		if (AttackedUnit->getTa() == 0)	//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			TanksTempList.enqueue(AttackedUnit);
	}
	for (int i = 0; i < NumOfAttackedSoldiers; i++)
	{
		SoldiersTempList.dequeue(AttackedUnit);	
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth()));	//Decrease Health
		if (AttackedUnit->getTa() == 0)	//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			SoldiersTempList.enqueue(AttackedUnit);
	}
	// move the attacked units back to their original list in the correct order
	while (TanksTempList.dequeue(AttackedUnit))
		TempList.push(AttackedUnit);
	while (TempList.pop(AttackedUnit))
		EA->AddAUnit(AttackedUnit);
	while (EA->GetASoldierTobeAttacked(AttackedUnit))
		SoldiersTempList.enqueue(AttackedUnit);
	while (SoldiersTempList.dequeue(AttackedUnit))
		EA->AddAUnit(AttackedUnit);
}
