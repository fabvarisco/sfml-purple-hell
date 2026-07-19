#include "Player.h"



Player::Player()
{
	this->initPlayerInfo();
	this->initHeroes();
	this->initEquipedItems();
}

Player::~Player()
{
	delete this->equipedItems;

	for (int i = 0; i < this->maxUnits; i++) {
		delete this->team[i];
	}

}
void Player::initPlayerInfo()
{
	std::ifstream ifs("res/Player/Info.txt");
	this->infoFile(ifs, 0);
}
void Player::initHeroes()
{
	std::ifstream ifsHeroes("res/Player/Team.txt");
	this->heroesFile(ifsHeroes, 0);
}

void Player::initEquipedItems()
{
	this->equipedItems = new EquipedItems();
}

void Player::render(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			this->team[i]->render(target);
		}
	}
}

void Player::renderActions(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (this->team[i]->GetSpell()->GetIsPlaying()) {
				this->team[i]->GetSpell()->render(target);
			}
			if (this->team[i]->GetAction()->GetIsPlaying()) {
				this->team[i]->GetAction()->render(target);
			}
		}
	}
}

void Player::update(sf::Vector2f mousePos, const float& dt, bool deselect)
{

	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->team[i]->getSprite()->getGlobalBounds().contains(mousePos) && this->team[i]->getName() != "slot") {
					this->team[i]->setSelected(true);
				}
				else if (deselect) {
					this->team[i]->setSelected(false);
				}
			}
			if (this->team[i]->GetSpell()->GetIsPlaying()) {
				this->team[i]->GetSpell()->updateAnimation(dt);
			}
			if (this->team[i]->GetAction()->GetIsPlaying()) {
				this->team[i]->GetAction()->updateAnimation(dt);
			}

			this->team[i]->UpdateAnimation(dt);
			this->team[i]->update(mousePos, dt);

		}
	}
}

void Player::MenuPosition()
{
	for (int i = 0; i < this->maxUnits; i++) {
		this->team[i]->SetPosition(200 + (23 * i), 148);
	}
}

void Player::AddHeroToTeam(Hero* hero)
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]->getName() == "slot") {
			this->team[i] = hero;
			break;
		}
	}
}


void Player::battlePosition()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			this->team[i]->SetPosition(250 + (23 * i), 150);
	}
}


Hero* Player::getHero()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (this->team[i]->getSelected()) {
				return this->team[i];
			}
		}
	}
	return nullptr;
}

Hero* Player::getHero(int i)
{
	return this->team[i];
}

Hero* Player::getRandomHero()
{
	if (this->checkDeads()) return nullptr;
	int heroIndex = rand() % 3;


	if (this->team[heroIndex] != nullptr) {
		if (this->team[heroIndex]->getHp() > 0) {
			return this->team[heroIndex];
		}
	}


	return getRandomHero();
}

Hero* Player::GetHeroViewStatus()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (this->team[i]->GetViewStatus()) {
				return this->team[i];
			}
		}
	}
	return nullptr;
}

int Player::getGold()
{
	this->initPlayerInfo();
	return this->gold;
}

int Player::GetLevel()
{
	return this->level;
}

void Player::updateGold(int value)
{
	this->gold += value;
	this->SaveInfoFile();

}


void Player::setTeam(int i, Hero* hero)
{
	this->team[i] = hero;
}

EquipedItems* Player::getEquipedItems()
{
	return this->equipedItems;
}

bool Player::getClear()
{
	return this->clear;
}
bool Player::canEquipHero()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (this->team[i]->getName() == "slot") return true;
		}
	}
	return false;
}
bool Player::CanBuy(Item* item, Hero* hero)
{
	int tempGold = 0;
	int totalGold = 0;

	if (item) {
		tempGold += 10;
	}
	if (hero) {
		tempGold += 20;
	}
	totalGold = this->gold - tempGold;

	if (totalGold >= 0) {
		this->gold = totalGold;
		return true;
	}
	else {
		return false;
	}


}
bool Player::IsSelectedForViewStatus()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (this->team[i]->GetViewStatus()) {
				return true;
			}
		}
	}
	return false;
}
void Player::setClear(bool value)
{
	this->clear = value;
}

int Player::teamSize()
{
	int a = 0;
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (this->team[i]->getName() != "slot") {
				a++;
			}
		}
	}
	return a;
}

bool Player::checkPlayed()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]->getHp() > 0) {
			if (!this->team[i]->getPlayed()) {
				return true;
			}
		}
	}
	return false;
}

void Player::setTeamToTrue()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i] && this->team[i]->getName() != "slot")
			this->team[i]->setPlayed(false);
	}
}

void Player::setSpecialToTrue()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i] && this->team[i]->getName() != "slot")
			this->team[i]->setCanUseSpecial(true);
	}
}

void Player::RemoveHero(Hero* hero)
{
	sf::Texture emptyTex;
	emptyTex.loadFromFile("res/img/items/slot.png");
	Hero* empty = new Hero(0, 0, "slot", "slot", 0, 0, 0, &emptyTex);
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i] == hero) {
			this->team[i] = empty;
			break;
		}
	}
}

void Player::Save()
{

	std::fstream ofsTeam;
	ofsTeam.open("res/Player/Team.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < this->maxUnits; i++) {
		ofsTeam
			<< this->team[i]->getName()
			<< " " << this->team[i]->GetJob()
			<< " " << this->team[i]->getHp()
			<< " " << this->team[i]->getPower()
			<< " " << this->team[i]->getSpecial() << std::endl;
	}
	ofsTeam.close();

}

bool Player::checkDeads()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			if (this->team[i]->getHp() > 0) {
				return false;
				break;
			}
	}
	return true;
}

void Player::checkDead()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			if (this->team[i]->getHp() <= 0 && this->team[i]->getPlayed() == false) {
				this->team[i]->setPlayed(true);
			}
	}
}

int Player::UnitNumber(Entity* hero)
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]->getName() == hero->getName()) {
			return i;
		}
	}
	return -1;
}
//Arquivos

void Player::heroesFile(std::ifstream& ifsHeroes, int i)
{
	std::string name = " ", job = " ";
	int hp = 0, power = 0, spell = 0;

	if (ifsHeroes.is_open())
	{
		if (!ifsHeroes.eof())
		{
			ifsHeroes >> name >> job >> hp >> power >> spell;

			if (name != " " && i < this->maxUnits) {
				sf::Texture* tex;
				tex = new sf::Texture();
				tex->loadFromFile("res/img/Player/" + job + ".png");
				this->team[i] = (new Hero(0, 0, name, job, hp, power, spell, tex));
				i++;
			}
			heroesFile(ifsHeroes, i);
		}
		else {
			ifsHeroes.close();
		}
	}
}

void Player::infoFile(std::ifstream& ifs, int i)
{
	std::string name = " ";
	int value = 0;

	if (ifs.is_open())
	{

		if (!ifs.eof())
		{
			ifs >> name >> value;
			if (name == "gold") {
				this->gold = value;
			}
			else if (name == "run") {
				this->run = value;
			}
			else if (name == "level") {
				this->level = value;
			}
			i++;
			infoFile(ifs, i);
		}
		else {
			ifs.close();
		}
	}
}

void Player::SaveInfoFile()
{
	std::fstream ofs;
	ofs.open("res/Player/Info.txt", std::ofstream::out | std::ofstream::trunc);

	ofs
		<< "gold " << this->gold << std::endl
		<< "run " << this->run << std::endl
		<< "level " << this->level;

	ofs.close();
}

void Player::WinBattle()
{
	this->gold += 50;
	this->level++;
	this->SaveInfoFile();
}
void Player::LostBattle()
{
	this->gold = this->gold / 2;
	this->level = 1;
	this->SaveInfoFile();

}

void Player::GameOver()
{
}
