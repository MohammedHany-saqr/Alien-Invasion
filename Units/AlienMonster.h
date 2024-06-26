#ifndef _ALIEN_MONSTER_H_
#define _ALIEN_MONSTER_H_
#include	"Unit.h"
#include	"../Game/Game.h"
class AlienMonster :public Unit {
protected:
public:
	AlienMonster(int id, int p, int h, int c, int tj);
	virtual void Attack(Game *g);
};
#endif