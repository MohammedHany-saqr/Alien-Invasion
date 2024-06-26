#include "AlienDrone.h"

AlienDrone::AlienDrone(int id, int p, int h, int c, int tj):Unit(id, p, h, c, tj)
{
}

void AlienDrone::Attack(Game *g)
{
	EarthArmy* EA = g->GetEarthArmy();
	if (g->GetAlienArmy()->GetDronesCount()==1)	return;
	if (EA->GetGunnersCount() == 0 && EA->GetTanksCount() == 0) return;
	Unit* AD2;
	g->GetAlienArmy()->GetLastDroneToAttack(AD2);
	UnitLinkedQueue TanksTempList;
	UnitLinkedQueue GunnersTempList;
	UnitStack TempList;
	Unit* AttackedUnit = nullptr;
	int Cap;
	if (AD2->GetCapacity() >= this->Capacity) Cap = this->Capacity;
	else Cap = AD2->GetCapacity();

	int NumOfAttackedTanks = Cap /2;
	int NumOfAttackedGunners = Cap -NumOfAttackedTanks ;
	for (int i = 0; i < NumOfAttackedTanks && EA->GetATankTobeAttacked(AttackedUnit); i++)
			TanksTempList.enqueue(AttackedUnit);
	for (int i = 0; i < NumOfAttackedGunners && EA->GetAGunneryTobeAttacked(AttackedUnit); i++)
			GunnersTempList.enqueue(AttackedUnit);

	NumOfAttackedTanks = TanksTempList.getCount();
	NumOfAttackedGunners = GunnersTempList.getCount();
	if (g->GetMod())
	{
		TanksTempList.fightingPrint("AD ", ID);
		GunnersTempList.fightingPrint("AD ", ID);
		TanksTempList.fightingPrint("AD ", AD2->GetID());
		GunnersTempList.fightingPrint("AD ", AD2->GetID());
	}
	double damage = (this->Power * (this->Health / 100)) + (AD2->GetPower() * (AD2->GetHealth() / 100));
	for (int i = 0; i < NumOfAttackedTanks; i++)
	{
		TanksTempList.dequeue(AttackedUnit);
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
		if (AttackedUnit->getTa() == 0)		//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			TanksTempList.enqueue(AttackedUnit);
	}
	for (int i = 0; i < NumOfAttackedGunners; i++)
	{
		GunnersTempList.dequeue(AttackedUnit);
		AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
		if (AttackedUnit->getTa() == 0)		//Set Ta if it's not her first time to be attacked
			AttackedUnit->setTa(g->GetTimeStep());
		if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
			g->PushKilledUnit(AttackedUnit);
		else
			GunnersTempList.enqueue(AttackedUnit);
	}

	// move the attacked units back to their original list in the correct order
	while (TanksTempList.dequeue(AttackedUnit))
		TempList.push(AttackedUnit);
	while (TempList.pop(AttackedUnit))
		EA->AddAUnit(AttackedUnit);
	while (GunnersTempList.dequeue(AttackedUnit))
		EA->AddAUnit(AttackedUnit);
}