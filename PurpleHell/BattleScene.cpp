#include "BattleScene.h"
#include <thread>


void BattleScene::initTextures()
{
	this->textureBackground.loadFromFile("res/backgrounds/battle.png");
	this->background.setTexture(textureBackground);
}
void BattleScene::initButtons()
{
	sf::Texture texture;
	texture.loadFromFile("res/hud/button2.png");
	this->buttons.push_back(new Button(280, 70, 75, 40, &this->font, "RUN", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture));
	this->buttons.push_back(new Button(100, 170, 75, 40, &this->font, "ATTACK", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture));
	this->buttons.push_back(new Button(150, 170, 75, 40, &this->font, "MAGIC", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture));
	this->buttons.push_back(new Button(200, 170, 75, 40, &this->font, "ITEM", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture));
	this->buttonEnd = new Button(150, 5, 75, 40, &this->font, "Exit", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture);
}

void BattleScene::initFont()
{
	if (!this->font.loadFromFile(this->fontFile)) {
		throw("COULD NOT LOAD FONT");
	}
}

void BattleScene::initTexts()
{
	sf::Text turnText;

	turnText.setFont(this->font);
	turnText.setString(" - TURN - \n- PLAYER -");
	turnText.setString(" - TURN - \n- PLAYER -");
	turnText.setCharacterSize(18);
	turnText.setPosition(143, 60);

	this->infoText = turnText;

	//Player/Enemy
	sf::Text playerTeamSetting;
	sf::Text enemyTeamSetting;



	//Player Team
	playerTeamSetting.setFont(this->font);
	playerTeamSetting.setCharacterSize(14);
	playerTeamSetting.setPosition(212, 12);

	this->playerTeamTexts.push_back(playerTeamSetting);
	playerTeamSetting.setPosition(212, 22);
	this->playerTeamTexts.push_back(playerTeamSetting);
	playerTeamSetting.setPosition(212, 32);
	this->playerTeamTexts.push_back(playerTeamSetting);

	//Enemy Team
	enemyTeamSetting.setFont(this->font);
	enemyTeamSetting.setCharacterSize(14);
	enemyTeamSetting.setPosition(10, 10);

	this->enemyTeamTexts.push_back(enemyTeamSetting);
	enemyTeamSetting.setPosition(10, 20);
	this->enemyTeamTexts.push_back(enemyTeamSetting);
	enemyTeamSetting.setPosition(10, 30);
	this->enemyTeamTexts.push_back(enemyTeamSetting);

	//BattleInfo
	sf::Text genericBattleTextSetting;
	genericBattleTextSetting.setFont(this->font);
	genericBattleTextSetting.setCharacterSize(16);

	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
	this->battleInfo.push_back(genericBattleTextSetting);
}

void BattleScene::initPlayer()
{
	this->player = new Player();
	this->player->battlePosition();
}

void BattleScene::initAI() {

	ais.push(new AI(0));
	ais.push(new AI(1));
	ais.push(new AI(2));
	ais.push(new AI(3));
	ais.front()->battlePosition();
}

//Constructors
BattleScene::BattleScene()
{
}
BattleScene::BattleScene(sf::RenderWindow* window, std::stack<Scene*>* scenes, int wave) : Scene(window, scenes)
{
	this->wave = wave;
	this->maxWave = wave * 2;
	this->initPlayer();
	this->initAI();
	this->initFont();
	this->initTextures();
	this->initButtons();
	this->initTexts();
	this->turn = true;
	this->win = false;
	this->winEnemy = false;
}
BattleScene::~BattleScene()
{
	//delete this->player;
	delete this->ai;
	for (auto& it : this->buttons) {
		delete it;
	}
}

//Updates
void BattleScene::updateButtons()
{
	for (auto& it : this->buttons) {
		it->update(this->mousePosView);
	}

	if (this->buttons[0]->isPressed() && !this->player->checkDeads()) {
		this->endScene();
	}

	if (this->win || this->winEnemy) {
		this->buttonEnd->update(this->mousePosView);

		if (this->buttonEnd->isPressed() && this->win) {
			if (!this->buttonPressed) {
				this->buttonPressed = true;
				this->player->WinBattle();
				this->endScene();
			}
		}
		if (this->buttonEnd->isPressed() && this->winEnemy) {
			if (!this->buttonPressed) {
				this->buttonPressed = true;
				this->player->LostBattle();
				this->endScene();
			}
		}
	}

	if (!this->ais.empty()) {
		if (turn && this->player->getHero() && this->ais.front()->selectedEnemy()) {
			if (this->player->getHero()->getSelected()) {
				if (this->buttons[1]->isPressed()) {
					if (!this->buttonPressed) {
						this->buttonPressed = true;
						this->timer = 100;
						this->playerAttack();
					}
				}
			}
		}


		if (turn && this->player->getHero() && this->ais.front()->selectedEnemy() && this->player->getHero()->CanUseEspecial()) {
			if (this->player->getHero()->getSelected()) {
				if (this->buttons[2]->isPressed()) {
					if (!this->buttonPressed) {
						this->playerSpecial();
						this->buttonPressed = true;
					}
				}
			}
		}


		if (turn && this->player->getEquipedItems()->getItem() && this->player->getHero(playerIndex)) {
			if (this->buttons[3]->isPressed()) {
				if (!this->buttonPressed) {
					this->buttonPressed = true;
					std::thread m_thread = std::thread([this]() {
						std::cout << "Hello from thread function!" << std::endl;
						this->useItem();
						});
					m_thread.join();
				}
			}
		}
	}

}

void BattleScene::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		//this->scenes->push(new BattleScene(this->window, this->scenes));
	}
}

void BattleScene::update(const float& dt)
{
	this->updateFade(dt);
	this->updateMousePosition();
	this->player->getEquipedItems()->updateEquipedItems(mousePosView, dt);
	this->updateTexts();
	this->updateButtons();

	this->player->update(mousePosView, dt);

	if (!this->ais.empty()) {
		this->ais.front()->updateEnemies(mousePosView, dt);
		this->ais.front()->battlePosition();
		
		if (this->ais.front()->checkDeads()) {
			this->player->setTeamToTrue();
			this->player->setSpecialToTrue();
			this->playerIndex = 0;
			this->ais.pop();
		}
		if (this->player->checkDeads()) {
			this->winEnemy = true;
		}

		if (turn && !this->winEnemy) {
			if (this->player->checkPlayed()) {
				if (this->playerIndex < this->player->teamSize()) {
					if (this->player->getHero(this->playerIndex)->getHp() > 0) {
						this->player->getHero(this->playerIndex)->setSelected(true);
					}
					else {
						playerIndex++;
					}
				}
			}
			else {
				turn = false;
				this->timer = 100;
			}
		}
		else {
			battleSystemEnemy(dt);
		}
	}
	else {
		this->win = true;
	}

	for (int key = 0; key < 7; key++) {
		this->updateBattleText(dt, key);
	}
	this->timer -= dt;
}

//Renders
void BattleScene::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	target->draw(this->hudSprite);
	this->player->getEquipedItems()->renderEquipedItems(target);

	this->renderTexts(target);
	this->player->render(target);
	if (!this->ais.empty()) {
		this->renderButtons(target);
		this->ais.front()->renderActions(target);
		this->ais.front()->renderEnemies(target);
	}
	if (this->win || this->winEnemy) {
		this->buttonEnd->render(target);
	}
	this->player->renderActions(target);

	this->player->getEquipedItems()->renderActions(target);

	this->renderFade(target);
}

void BattleScene::renderTexts(sf::RenderTarget* target)
{
	target->draw(infoText);
	for (auto& it : this->battleTexts) {
		target->draw(it);
	}
	for (auto& it : this->battleInfo) {
		target->draw(it);
	}
	for (auto& it : this->playerTeamTexts) {
		target->draw(it);
	}
	for (auto& it : this->enemyTeamTexts) {
		target->draw(it);
	}

}

void BattleScene::updateTexts()
{
	for (int i = 0; i < 3; i++)
	{
		if (this->player->getHero(i)->getName() != "slot") {
			Hero* hero = this->player->getHero(i);
			this->playerTeamTexts[i].setString(hero->getName()
				+ "/"
				+ "HP:"
				+ std::to_string(hero->getHp())
				+ "/PW:"
				+ std::to_string(hero->getPower())
				+ "/MP:" + std::to_string(hero->CanUseEspecial()));
		}
	}
	if (!this->ais.empty()) {

		for (int i = 0; i < 5; i++)
		{
			if (this->ais.front()->getTeam(i)->getName() != "slot") {
				Enemy* enemy = this->ais.front()->getTeam(i);
				this->enemyTeamTexts[i].setString(enemy->getName() + " / " + " HP:" + std::to_string(enemy->getHp()) + " / MP:" + std::to_string(enemy->CanUseEspecial()));
			}
		}
	}

	if (turn && !win && !winEnemy) {
		this->infoText.setString(" - TURN - \n- PLAYER -");
	}
	else {
		this->infoText.setString(" - TURN - \n- ENEMY -");
	}


	if (win && !winEnemy) {
		this->infoText.setString("PLAYER WINS!");
	}

	if (!win && winEnemy) {
		this->infoText.setString("ENEMY WINS!");
	}

}

void BattleScene::enemyTurn()
{

	if (this->ais.front()->getTeam(this->enemyIndex)->getHp() <= 0) {
		this->enemyIndex++;
	}
	else {
		if (this->enemyTurnIndex == 0) {
			//enemy Turn start
			this->infoText.setString(" - TURN - \n- ENEMY -");
			this->enemyTurnIndex++;
		}
		else if (this->enemyTurnIndex == 1) {
			this->infoText.setString(" - TURN - \n- ENEMY -");
			this->enemyTurnIndex++;
		}
		else if (this->enemyTurnIndex == 2) {
			this->enemyAttack();

		}
	}

}

void BattleScene::battleText(int key, Entity* entity, std::string text)
{
	this->battleInfo[key].setString(text);
	this->battleInfo[key].setPosition(entity->getPosition().x, entity->getPosition().y - 18);
	this->timerDamageText = 50;
}

void BattleScene::updateBattleText(const float& dt, int key)
{
	if (this->battleInfo[key].getString() != "") {
		int y = this->battleInfo[key].getPosition().y;
		this->battleInfo[key].setPosition(this->battleInfo[key].getPosition().x, y -= 1);
		if (this->timerDamageText <= 0) {
			this->battleInfo[key].setString("");
		}
		this->timerDamageText -= dt;
	}
}

void BattleScene::useItem()
{
	int itemId = this->player->getEquipedItems()->getItemId();
	this->player->getEquipedItems()->getItem()->Action(this->player->getHero(playerIndex));
	this->battleText(0, this->player->getHero(playerIndex), this->player->getEquipedItems()->getItemById(itemId)->GetAction()->GetDescription());
	if (!this->player->getEquipedItems()->getItemById(itemId)->GetAction()->GetIsPlaying()) {
		this->player->getEquipedItems()->removeItem(itemId);
		this->player->getEquipedItems()->save();
		playerIndex++;
	}
}

void BattleScene::renderButtons(sf::RenderTarget* target)
{
	if (!this->player->checkDeads()) {
		this->buttons[0]->render(target);
	}

	if (turn && this->ais.front()->selectedEnemy()) {
		this->buttons[1]->render(target);
		this->buttons[2]->render(target);
	}

	if (turn && this->player->getEquipedItems()->getItem()) {
		this->buttons[3]->render(target);
	}
}

void BattleScene::battleSystemEnemy(const float& dt)
{
	if (this->timer <= 0 && !this->ais.front()->enemyPlayed()) {
		enemyTurn();
		this->timer = 100;
	}
	if (this->ais.front()->enemyPlayed() == true && this->timer <= 0) {
		this->enemyIndex = 0;
		this->playerIndex = 0;
		this->ais.front()->setTeamToPlay();
		this->player->setTeamToTrue();
		turn = true;
	}

}

void BattleScene::playerReward()
{
	std::fstream fsUnits("res/Player/Units.txt");
	std::fstream fsInventory("res/Player/Inventory.txt");

	if (!this->player->getClear()) {
		if (fsUnits.is_open())
		{
			if (fsUnits.good())
			{
				fsUnits << "knight 25 5 2" << std::endl;
				fsUnits << "archer 35 6 2" << std::endl;
				fsUnits << "slot 0 0 0";
			}

			fsUnits.close();
		}

		if (fsInventory.is_open())
		{
			if (fsInventory.good())
			{
				fsInventory << "potion 1 5 1" << std::endl;
				fsInventory << "knife 1 5 2" << std::endl;
				fsInventory << "axe 1 10 3" << std::endl;
				fsInventory << "sword 1 15 4" << std::endl;
				fsInventory << "magicAxe 1 20 5" << std::endl;
			}
			fsInventory.close();
		}

		this->player->setClear(true);
	}
}

void BattleScene::enemyAttack()
{
	//this->ais.front()->getTeam(this->enemyIndex)->Action(player);
	Hero* player = this->player->getRandomHero();
	if (!player) return;
	Enemy* enemy = this->ais.front()->getTeam(this->enemyIndex);

	std::srand(time(NULL));
	int r = rand() % 100;
	if (r < 33) {
		this->battleText(0, player, "MISS");
		enemy->setPlayed(true);
		enemy->setSelected(false);
		player->setSelected(false);
	}
	else {
		enemy->Action(player);
		this->battleText(0, player, "- " + std::to_string(enemy->getPower()));
	}
	this->enemyIndex++;
}

void BattleScene::playerAttack()
{
	Hero* player = this->player->getHero(this->playerIndex);
	Enemy* enemy = this->ais.front()->getEnemy();
	player->Action(enemy);
	this->battleText(0, enemy, "- " + std::to_string(player->getPower()));
	this->playerIndex++;
}

void BattleScene::playerSpecial()
{
	Hero* player = this->player->getHero(this->playerIndex);
	Enemy* enemy = this->ais.front()->getEnemy();
	player->Special(enemy);
	this->battleText(0, enemy, "- " + std::to_string(player->getPower() *2));
	this->playerIndex++;
}




