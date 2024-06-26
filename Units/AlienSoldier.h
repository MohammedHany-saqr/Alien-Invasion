#ifndef _ALIEN_SOLDIER_H_
#define _ALIEN_SOLDIER_H_

#include	"Unit.h"
#include "../Game/Game.h"
class AlienSoldier :public Unit {
public:
	AlienSoldier(int id, int p, int h, int c, int tj);
	virtual void Attack(Game *g);
};
#endif