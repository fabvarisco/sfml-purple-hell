#ifndef PLAYER_H
#define PLAYER_H

#include "Hero.h"
#include "Units.h"
#include "EquipedItems.h"
#include <vector>
class Player
{
private:
	static const int maxUnits = 3;
	Hero* team[maxUnits];
	EquipedItems* equipedItems;
	bool selected;
	bool clear;

	//player info
	int gold = 0;
	int run = 1;
	int level = 1;

	//Init
	void initPlayerInfo();
	void initHeroes();
	void initEquipedItems();
	//Files
	void heroesFile(std::ifstream& ifsHeroes, int i);
	void infoFile(std::ifstream& ifsHeroes, int i);

public:
	Player();
	virtual ~Player();
	void render(sf::RenderTarget* target);
	void renderActions(sf::RenderTarget* target);
	void update(sf::Vector2f mousePos, const float& dt, bool deselect = false);
	void battlePosition();
	void setTeamToTrue();
	void checkDead();
	void setTeam(int i, Hero* hero);
	void setClear(bool value);
	void updateGold(int value);
	void setSpecialToTrue();
	void RemoveHero(Hero* hero);
	void Save();
	void MenuPosition();
	void AddHeroToTeam(Hero* hero);
	void SaveInfoFile();
	void WinBattle();
	void LostBattle();
	void GameOver();

	int UnitNumber(Entity* hero);
	int teamSize();
	int getGold();
	int GetLevel();

	bool checkPlayed();
	bool checkDeads();
	bool getClear();
	bool canEquipHero();
	bool CanBuy(Item* item, Hero* hero);
	bool IsSelectedForViewStatus();

	Hero* getHero();
	Hero* getHero(int i);
	Hero* getRandomHero();
	Hero* GetHeroViewStatus();

	EquipedItems* getEquipedItems();
};
#endif // !PLAYER_H
