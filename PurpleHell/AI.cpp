#include "AI.h"
#include "BinaryIO.h"

AI::AI()
{
	std::ifstream ifsEnemies("res/AI/0.txt", std::ios::binary);
	ArquivoEnemies(ifsEnemies, 0, 1);
}

AI::AI(int i, int level)
{
	std::ifstream ifsEnemies("res/AI/" + std::to_string(i) + ".txt", std::ios::binary);
	ArquivoEnemies(ifsEnemies, 0, level);
}

AI::~AI()
{
	for (int i = 0; i < this->maxUnits; i++) {
		delete this->team[i];
	}
}

//Update
void AI::updateEnemies(sf::Vector2f mousePos, const float& dt)
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->team[i]->getSprite()->getGlobalBounds().contains(mousePos) && this->team[i]->getName() != "slot") {
					this->team[i]->setSelected(true);
				}
				else {
					this->team[i]->setSelected(false);
				}
			}
			if (this->team[i]->GetSpell()->GetIsPlaying()) {
				this->team[i]->GetSpell()->updateAnimation(dt);
			}
			if (this->team[i]->GetAction()->GetIsPlaying()) {
				this->team[i]->GetAction()->updateAnimation(dt);
			}
			this->team[i]->update(mousePos, dt);
			this->team[i]->updateAnimation(dt);
		}
	}
}

//Render
void AI::renderEnemies(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i] && this->team[i]->getHp() > 0) {
			this->team[i]->render(target);
		}
	}

}

//Stuff
void AI::battlePosition()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i]) {
			this->team[i]->SetPosition(55 + (35 * i), 152);
		}
	}
}

bool AI::selectedEnemy()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			if (team[i]->getSelected()) {
				return true;
			}
	}
	return false;
}

Enemy* AI::getEnemy()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (team[i] && team[i]->getSelected()) {
			return team[i];
		}
	}
	return nullptr;
}

Enemy* AI::getTeam(int i)
{
	return this->team[i];
}

bool AI::checkDeads() {
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			if (this->team[i]->getHp() > 0) {
				return false;
				break;
			}
	}
	return true;
}

int AI::NumberOfEnemies()
{
	int temp = 0;
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			if (this->team[i]->getHp() > 0) {
				temp++;
			}
	}
	return temp;
}

void AI::setTeamToPlay()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i] != nullptr) {
			if (this->team[i]->getName() != "slot" && this->team[i]->getHp() > 0) {
				this->team[i]->setPlayed(false);
			}
		}
	}
}

void AI::renderActions(sf::RenderTarget* target)
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

bool AI::checkPlayed()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (team[i]) {
			if (!team[i]->getPlayed()) {
				return true;
			}
		}
	}
	return false;
}


bool AI::enemyPlayed()
{
	for (int i = 0; i < this->maxUnits; i++) {
		if (this->team[i])
			if (!this->team[i]->getPlayed()) {
				return false;
			}
	}
	return true;
}

//files
void AI::ArquivoEnemies(std::ifstream& ifsEnemies, int i, int level)
{
	if (!ifsEnemies.is_open()) return;
	if (!bin::readHeader(ifsEnemies)) { ifsEnemies.close(); return; }

	if (level < 1) level = 1;

	int count = bin::readInt(ifsEnemies);
	for (int k = 0; k < count && i < this->maxUnits; k++) {
		std::string name = bin::readStr(ifsEnemies);
		int hp = bin::readInt(ifsEnemies);
		int power = bin::readInt(ifsEnemies);
		if (!ifsEnemies) break;

		hp = hp * (level + 1) / 2;
		power = power * (level + 1) / 2;

		if (name != " ") {
			sf::Texture* tex;
			tex = new sf::Texture();
			tex->loadFromFile("res/img/AI/" + name + ".png");
			this->team[i] = (new Enemy(0, 0, name, hp, power, tex));
			i++;
		}
	}
	ifsEnemies.close();

}