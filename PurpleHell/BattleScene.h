#ifndef BATTLESCENE_H
#define BATTLESCENE_H


#include "Scene.h"
#include "Button.h"
#include "GameScene.h"
#include "AI.h"

#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h> 
#include <time.h>
#include <queue>



class BattleScene :
	public Scene
{
protected:

	Player * player;
	AI* ai;

	sf::Font font;
	sf::Text infoText;
	sf::Sprite background;
	sf::Texture textureBackground;
	sf::Texture hudTexture;
	sf::Sprite hudSprite;

	std::vector <Button*> buttons;
	std::vector <sf::Text> battleTexts;
	std::vector <sf::Text> playerTeamTexts;
	std::vector <sf::Text> enemyTeamTexts;

	std::vector <sf::Text> battleInfo;
	std::queue<AI*> ais;

	Button* buttonEnd;

	bool turn = true;
	bool win = false;
	bool winEnemy = false;

	int wave;
	int maxWave;
	int timer = 100;
	int timerToStart = 100;
	int enemyTurnIndex = 0;
	int enemyIndex = 0;
	int timerDamageText = 20;
	int playerIndex = 0;
	void initTextures();
	void initButtons();
	void initFont();
	void initTexts();
	void initPlayer();
	void initAI();
	void battleSystemEnemy(const float& dt);
	void playerReward();
	void enemyAttack();
	void playerAttack();
	void playerSpecial();


public:
	BattleScene();
	BattleScene(sf::RenderWindow * window, std::stack<Scene*>* scenes, int wave);
	virtual ~BattleScene();

	void renderButtons(sf::RenderTarget* target = NULL);
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
	void renderTexts(sf::RenderTarget* target = NULL);
	void updateTexts();
	void enemyTurn();
	void battleText(int key, Entity* entity, std::string text);
	void updateBattleText(const float& dt, int key);
	void useItem();
};

#endif // !BATTLESTATE_H
