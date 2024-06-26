#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int id, int p, int h, int c, int tj) :Unit(id, p, h, c, tj)
{
}

void EarthGunnery::Attack(Game* g)
{
  AlienArmy* AA = g->GetAlienArmy();
  if (AA->GetMonstersCount() == 0 && AA->GetDronesCount() == 0) return;

  UnitLinkedQueue MonstersTempList;
  UnitLinkedQueue DronesTempList;
  Unit* AttackedUnit = nullptr;
  int NumOfAttackedMonsters = Capacity / 2;
  int NumOfAttackedDrones = Capacity - NumOfAttackedMonsters;

  for (int i = 0; i < NumOfAttackedDrones; i++)
  {
	  if (AA->GetFirstDroneTobeAttacked(AttackedUnit)) {
		  DronesTempList.enqueue(AttackedUnit);
		  i++;
		  if (i >= NumOfAttackedDrones) break;
	  }
	  if (AA->GetLastDroneTobeAttacked(AttackedUnit))
		  DronesTempList.enqueue(AttackedUnit);
		  
  }
  for (int i = 0; i < NumOfAttackedMonsters && AA->GetAMonsterTobeAttacked(AttackedUnit); i++)
		  MonstersTempList.enqueue(AttackedUnit);

  NumOfAttackedDrones = DronesTempList.getCount();
  NumOfAttackedMonsters = MonstersTempList.getCount();

  if (g->GetMod())
  {
	  MonstersTempList.fightingPrint("EG ", ID);
	  DronesTempList.fightingPrint("EG ", ID);
  }

  double damage = (Power * (Health / 100));
  //Attacking Drones
  for (int i = 0; i < NumOfAttackedDrones; i++)
  {
	  DronesTempList.dequeue(AttackedUnit);
	  AttackedUnit->DecHealth(damage / sqrt(AttackedUnit->GetHealth())); //Decrease Health
	  if (AttackedUnit->getTa() == 0)		//Set Ta if it's not her first time to be attacked
		  AttackedUnit->setTa(g->GetTimeStep());
	  if (!AttackedUnit->GetStatus())	//set status to flase (dead) and push it to killed list;
		  g->PushKilledUnit(AttackedUnit);
	  else
		  DronesTempList.enqueue(AttackedUnit);
  }
  //Attacking Monsters
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
  // move the attacked units back to their original list in the correct order
  while (MonstersTempList.dequeue(AttackedUnit))
	  AA->AddAUnit(AttackedUnit);

  while (AA->GetASoldierTobeAttacked(AttackedUnit))
	  DronesTempList.enqueue(AttackedUnit);
  while (DronesTempList.dequeue(AttackedUnit))
  {
	  AA->AddAUnit(AttackedUnit,true,false);
	  if(DronesTempList.dequeue(AttackedUnit))
		  AA->AddAUnit(AttackedUnit, true, true);
  }
}
