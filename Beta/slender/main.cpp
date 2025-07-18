#include"Game.h"

using namespace std;

int main(){

	Game game("game", 1920, 1080, 4, 6, false);

	//Loop game
	while (!game.getWindowShouldClose()) {
		game.update();
		game.render();
		
	}

	return 0;
}
