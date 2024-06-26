#ifndef _EARTH_SOLDIER_H_
#define _EARTH_SOLDIER_H_
#include	"Unit.h"
#include	"../Game/Game.h"
class EarthSoldier :public Unit {
protected:
public:
	EarthSoldier(int id, int p, int h, int c, int tj);
	virtual void Attack(Game*g);
};
#endif