#include "Game/Game.h"
#include<windows.h>
#include <iostream>
using namespace std;

int main() {
	srand(time(0));
	Game* game = new Game;
	game->StartGame();
	delete game;
}
