#include "Units.h"


void Units::initUnits()
{
	std::ifstream ifsUnits("res/Player/Units.txt");
	this->ArquivoUnits(ifsUnits, 0);
}

Units::Units()
{
	this->initUnits();
}

Units::~Units()
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		delete this->heroes[i];
	}
}

void Units::renderUnits(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
			this->heroes[i]->render(target);
	}
}

void Units::updateUnits(sf::Vector2f mousePos,const float &dt)
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->heroes[i]->getSprite()->getGlobalBounds().contains(mousePos)) {
					this->heroes[i]->setSelected(true);
				}
				else {
					this->heroes[i]->setSelected(false);
				}
			}
			this->heroes[i]->update(mousePos, dt);
		}
		this->heroes[i]->SetPosition(92 + (25 * i), 22);
	}

}

bool Units::selectedHero()
{

	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]) {
			if (this->heroes[i]->getSelected()) {
				return true;
			}
		}
	}
	return false;
}

bool Units::canRemoveHero()
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]) {
			if (this->heroes[i]->getName() == "slot") {
				return true;
			}
		}
	}
	return false;
}

Hero* Units::getHero()
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]) {
			if(this->heroes[i]->getName() != "slot"){
				if (this->heroes[i]->getSelected()) {
					return this->heroes[i];
				}
			}
		}
	}
	return nullptr;
}


void Units::setUnits(Hero* hero)
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]->getName() == "slot") {
			this->heroes[i] = hero;
			break;
		}
	}
}

void Units::removeHero(Hero* hero)
{
	sf::Texture emptyTex;
	emptyTex.loadFromFile("res/img/items/slot.png");
	Hero* empty = new Hero(0, 0,"slot", "slot", 0, 0, 0, &emptyTex);
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i] == hero) {
			this->heroes[i] = empty;
			break;
		}
	}
}

void Units::equipHero(Hero* hero)
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]->getName() == "slot") {
			this->heroes[i] = hero;
			break;
		}
	}
}

void Units::Save()
{
	std::fstream ofsHeroes;
	ofsHeroes.open("res/Player/Units.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < this->maxUnitsInventory; i++) {
		ofsHeroes
			<< this->heroes[i]->getName() 
			<< " " << this->heroes[i]->GetJob()
			<< " " << this->heroes[i]->getHp()
			<< " " << this->heroes[i]->getPower()
			<< " " << this->heroes[i]->getSpecial() << std::endl;
	}
	ofsHeroes.close();
}

Hero* Units::getTeam(int i)
{
	return this->heroes[i];
}

int Units::UnitNumber()
{
	for (int i = 0; i < this->maxUnitsInventory; i++) {
		if (this->heroes[i]) {
				if (this->heroes[i]->getSelected()) {
					return i;
				}
		}
	}
	return -1;
}
//Arquivos
void Units::ArquivoUnits(std::ifstream &ifsUnits, int i)
{
	std::string name = " ", job = " ";
	int hp = 0, power = 0, spell = 0;

	if (ifsUnits.is_open())
	{

		if (!ifsUnits.eof())
		{

			ifsUnits >> name >> job >> hp >> power >> spell;

			if (name != " ") {
				sf::Texture *tex;
				tex = new sf::Texture();
				tex->loadFromFile("res/img/Player/" + job + ".png");
				this->heroes[i] = new Hero(93 + (25 * i), 23, name, job, hp, power, spell, tex);
				i++;
			}
			ArquivoUnits(ifsUnits, i);
		}
		else {
			ifsUnits.close();
		}
	}

}