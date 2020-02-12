#include "precomH.h"


int main()
{
	std::thread th(&game::playmusic);
	try
	{
		game& play = game::getInstance();
		play.GameLoop();
	}
	catch (...)
	{
		std::cout << "Couldn't start a new game\n";
	}
	th.join();
	_CrtDumpMemoryLeaks();
	return 0;
}