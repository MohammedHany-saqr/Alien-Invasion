#include "Unit.h"
Unit::Unit(int id, double p, double h, int c,int tj)
{
	ID = id;
	Power = p;
	Health = h;
	Capacity = c;
	Tj = tj;
	Status = true;
	Ta = 0;

}

bool Unit::DecHealth(double Damage)
{
	Health -= Damage;
	if (Health <= 0)	Status = false;
	return true;
}

double Unit::GetHealth() {
	return Health;
}
double Unit::GetPower() {
	return Power;
}
int Unit::GetCapacity() {
	return Capacity;
}
int Unit::GetID() {
	return ID;
}

bool Unit::GetStatus()
{
	return Status;
}
void Unit::setTd(int DestructionTimeStep)
{
	Td = DestructionTimeStep;
}
int Unit::getTd()
{
	return Td;
}
void Unit::setTa(int FirstAttackedTimeStep)
{
	Ta = FirstAttackedTimeStep;
}
int Unit::getTj()
{
	return Tj;
}
int Unit::getTa()
{
	return Ta;
}
Unit::~Unit()
{
}
