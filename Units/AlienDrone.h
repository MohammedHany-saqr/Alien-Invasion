#ifndef _ALIEN_DRONES_H_
#define _ALIEN_DRONES_H_
#include	"Unit.h"
#include	"../Game/Game.h"
class AlienDrone :public Unit {
public:
	AlienDrone(int id, int p, int h, int c, int tj);
	virtual void Attack(Game *g);
};
#endif