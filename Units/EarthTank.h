# ifndef _EARTH_TANK_H_
#define _EARTH_TANK_H_
#include "Unit.h"
#include "../Game/Game.h"
class EarthTank :public Unit
{
protected:
	bool AttackSoldiers;
public:
	EarthTank(int id, int p, int h, int c, int tj);
	virtual void Attack(Game *g);
	void CheckAttackSoldiers(Game* g);
};
#endif