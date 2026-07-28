#ifndef AI_H
#define AI_H

#include "Enemy.h"
#include <fstream>
#include <sstream>

class AI
{
private:
	static const int maxUnits = 5;
	//sf::Texture* t;

	Enemy* team[maxUnits] = {};
	//Files
	void ArquivoEnemies(std::ifstream &, int, int level);

public:
	AI();
	AI(int i, int level = 1);
	virtual ~AI();
	void renderEnemies(sf::RenderTarget* target);
	void updateEnemies(sf::Vector2f mousePos, const float &dt);
	void battlePosition();
	void setTeamToPlay();
	void renderActions(sf::RenderTarget* target);

	bool selectedEnemy();
	bool enemyPlayed();
	bool checkDeads();
	bool checkPlayed();
	
	int NumberOfEnemies();
	
	Enemy* getEnemy();	
	Enemy* getTeam(int i);

};
#endif // !AI_H
