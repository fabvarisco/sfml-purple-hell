#include "Player.h"
#include "BinaryIO.h"



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
	std::ifstream ifs("res/Player/Info.txt", std::ios::binary);
	this->infoFile(ifs, 0);
}
void Player::initHeroes()
{
	std::ifstream ifsHeroes("res/Player/Team.txt", std::ios::binary);
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
	ofsTeam.open("res/Player/Team.txt", std::ios::out | std::ios::trunc | std::ios::binary);

	bin::writeHeader(ofsTeam);
	bin::writeInt(ofsTeam, this->maxUnits);
	for (int i = 0; i < this->maxUnits; i++) {
		bin::writeStr(ofsTeam, this->team[i]->getName());
		bin::writeStr(ofsTeam, this->team[i]->GetJob());
		bin::writeInt(ofsTeam, this->team[i]->getHp());
		bin::writeInt(ofsTeam, this->team[i]->getPower());
		bin::writeInt(ofsTeam, this->team[i]->getSpecial());
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
	if (!ifsHeroes.is_open()) return;
	if (!bin::readHeader(ifsHeroes)) { ifsHeroes.close(); return; }

	int count = bin::readInt(ifsHeroes);
	for (int k = 0; k < count && i < this->maxUnits; k++) {
		std::string name = bin::readStr(ifsHeroes);
		std::string job = bin::readStr(ifsHeroes);
		int hp = bin::readInt(ifsHeroes);
		int power = bin::readInt(ifsHeroes);
		int spell = bin::readInt(ifsHeroes);
		if (!ifsHeroes) break;

		if (name != " ") {
			sf::Texture* tex;
			tex = new sf::Texture();
			tex->loadFromFile("res/img/Player/" + job + ".png");
			this->team[i] = (new Hero(0, 0, name, job, hp, power, spell, tex));
			i++;
		}
	}
	ifsHeroes.close();
}

void Player::infoFile(std::ifstream& ifs, int i)
{
	if (!ifs.is_open()) return;
	if (!bin::readHeader(ifs)) { ifs.close(); return; }

	this->gold = bin::readInt(ifs);
	this->run = bin::readInt(ifs);
	this->level = bin::readInt(ifs);
	ifs.close();
}

void Player::SaveInfoFile()
{
	std::fstream ofs;
	ofs.open("res/Player/Info.txt", std::ios::out | std::ios::trunc | std::ios::binary);

	bin::writeHeader(ofs);
	bin::writeInt(ofs, this->gold);
	bin::writeInt(ofs, this->run);
	bin::writeInt(ofs, this->level);

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
