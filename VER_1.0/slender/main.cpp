#include"Game.h"
#include <imm.h>
#pragma comment(lib, "imm32.lib")
using namespace std;

int main(){

	Game game("Slember",1920, 1080, 4, 6, false);
	ImmDisableIME(0);
	//Loop game
	while (!game.getWindowShouldClose()) {
		game.update();
		game.render();
		
	}

	return 0;
}
