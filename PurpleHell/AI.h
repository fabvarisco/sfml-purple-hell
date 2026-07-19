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
	//Arquivos
	void ArquivoEnemies(std::ifstream &, int);

public:
	AI();
	AI(int i);
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
