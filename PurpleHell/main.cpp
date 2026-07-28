#include "GameManager.h"
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));

	GameManager gameManager;
	gameManager.run();

	return 0;
}
