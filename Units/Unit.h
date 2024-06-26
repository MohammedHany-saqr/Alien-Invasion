#ifndef _UNIT_H_
#define	_UNIT_H_
#include	<iostream>
class Game;
class Unit {
protected:
	int ID;
	double Power;
	double Health;
	int Capacity;
	bool Status;	//Unit Alive or Dead
	int Tj;  // Unit's join time
	int Td;  // Unit's destruction time
	int Ta;  // Unit's first attacked time
public:
	Unit(int id, double p, double h, int c, int tj);
	bool DecHealth(double);
	double GetHealth();
	double GetPower();
	int GetCapacity();
	int GetID();
	bool GetStatus();
	void setTd(int);
	int getTd();
	void setTa(int);
	int getTj();
	int getTa();
	virtual void Attack(Game*) = 0;
	~Unit();
};
#endif