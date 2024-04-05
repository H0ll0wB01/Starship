#include "Game.h"
#include <time.h>

int main()
{
	// initializing the seed from the time
	srand(time(static_cast<unsigned>(0)));

	Game newGame;
	
	newGame.Run();
	
	return 0;
}