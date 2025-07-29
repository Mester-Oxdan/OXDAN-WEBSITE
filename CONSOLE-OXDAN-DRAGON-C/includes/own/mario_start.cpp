#include "includes/mario/SuperMarioGame.h"
#include "all_diclarations.h"

void mario_start()
{
	CMarioGame::instance()->run();
	check_start_start();
}


