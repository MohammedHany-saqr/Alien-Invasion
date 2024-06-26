#ifndef _EARTH_GUNNERY_H_
#define _EARTH_GUNNERY_H_

#include	"Unit.h"
#include	"../Game/Game.h"
class EarthGunnery :public Unit {
protected:
public:
	EarthGunnery(int id, int p, int h, int c, int tj);
	virtual void Attack(Game* g);
};
#endif