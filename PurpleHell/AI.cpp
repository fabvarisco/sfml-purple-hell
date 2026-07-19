#include "AI.h"

AI::AI()
{
	std::ifstream ifsEnemies("res/AI/0.txt");
	ArquivoEnemies(ifsEnemies, 0);
}

AI::AI(int i)
{
	std::ifstream ifsEnemies("res/AI/" + std::to_string(i) + ".txt");
	ArquivoEnemies(ifsEnemies, 0);
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
		if (this->team[i]->getHp() > 0) {
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
		if (team[i]->getSelected()) {
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

//Arquivos
void AI::ArquivoEnemies(std::ifstream& ifsEnemies, int i)
{
	std::string name = " ";
	int hp = 0, power = 0;

	if (ifsEnemies.is_open())
	{

		if (!ifsEnemies.eof())
		{

			ifsEnemies >> name >> hp >> power;
			sf::Texture* tex;
			tex = new sf::Texture();
			tex->loadFromFile("res/img/AI/" + name + ".png");
			this->team[i] = (new Enemy(0, 0, name, hp, power, tex));
			i++;

			ArquivoEnemies(ifsEnemies, i);
		}
		else {
			ifsEnemies.close();
		}
	}

}