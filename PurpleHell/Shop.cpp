#include "Shop.h"

Shop::Shop()
{
	Refresh();
;}

void Shop::Render(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxArrayValues; i++) {
		if (this->heroes[i]) {
			this->heroes[i]->render(target);
			this->heroes[i]->SetPosition(92 + (25 * i), 22);
			
		}
		if (this->items[i]) {
			this->items[i]->render(target);
			this->items[i]->SetPosition(92 + (25 * i), 48);
		}
	}
}

void Shop::Update(sf::Vector2f mousePos, const float& dt)
{
	for (int i = 0; i < this->maxArrayValues; i++) {
		if (this->heroes[i]) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->heroes[i]->getSprite()->getGlobalBounds().contains(mousePos) && this->heroes[i]->getName() != "slot") {
					this->heroes[i]->setSelected(true);
				}
				else {
					this->heroes[i]->setSelected(false);
				}
			}
			this->heroes[i]->update(mousePos, dt);
		}
		if (this->items[i]) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->items[i]->getSprite()->getGlobalBounds().contains(mousePos) && this->items[i]->getName() != "slot") {
					this->items[i]->setSelected(true);
				}
				else {
					this->items[i]->setSelected(false);
				}
			}
			this->items[i]->update(mousePos, dt);
		}
	}
}

Item* Shop::GetSelectedItem()
{
	for (int i = 0; i < this->maxArrayValues; i++) {
		if (this->items[i] && this->items[i]->getSelected()) {
			return this->items[i];
		}
	}
	return nullptr;
}


Hero* Shop::GetSelectedHero()
{
	for (int i = 0; i < this->maxArrayValues; i++) {
		if (this->heroes[i] && this->heroes[i]->getSelected()) {
			return this->heroes[i];
		}
	}
	return nullptr;
}

Hero* Shop::getHero(int i)
{
	if (i < 0 || i >= this->maxArrayValues) return nullptr;
	return this->heroes[i];
}

Item* Shop::getItem(int i)
{
	if (i < 0 || i >= this->maxArrayValues) return nullptr;
	return this->items[i];
}

void Shop::RemoveItem()
{
	Hero* hero = this->GetSelectedHero();
	Item* item = this->GetSelectedItem();
	if (hero) {
		for (int i = 0; i < this->maxArrayValues; i++) {
			if (this->heroes[i] == hero) {
				sf::Texture* tex = new sf::Texture();
				tex->loadFromFile("res/img/Player/slot.png");
				this->heroes[i] = new Hero(0.0, 0.0, "slot", "slot", 0, 0, 0, tex);
			}
		}
	}
	if (item) {
		for (int i = 0; i < this->maxArrayValues; i++) {
			if (this->items[i] == item) {
				sf::Texture* tex = new sf::Texture();
				tex->loadFromFile("res/img/Player/slot.png");
				this->items[i] = new Item(0.0, 0.0, "slot", 0, 0, 0, tex);
			}
		}
	}
}

void Shop::Refresh()
{
	this->generateHeroes();
	this->generateItems();
}

Shop::~Shop()
{
}

void Shop::generateHeroes()
{
	for (int i = 0; i < this->maxArrayValues; i++) {

		std::random_device rd;
		std::mt19937 generator(rd());

		std::uniform_int_distribution<int> rngName(0, 80);
		std::uniform_int_distribution<int> rngLife(10, 300);
		std::uniform_int_distribution<int> rngPower(1, 300);
		std::uniform_int_distribution<int> rngJob(0, 5);
		std::uniform_int_distribution<int> rngSpecial(1, 3);

		int hp = rngLife(generator);
		int power = rngPower(generator);
		int special = rngSpecial(generator);
		int job = rngJob(generator);
		int name = rngName(generator);

		sf::Texture* tex = new sf::Texture();
		tex->loadFromFile("res/img/Player/" + jobs[job] + ".png");
		this->heroes[i] = new Hero(0.0, 0.0, names[name], jobs[job], hp, power, special, tex);
	}
}

void Shop::generateItems()
{
	for (int i = 0; i < this->maxArrayValues; i++) {

		std::random_device rd;
		std::mt19937 generator(rd());

		std::uniform_int_distribution<int> rngName(0, 3);
		std::uniform_int_distribution<int> rngPower(1, 300);

		int name = rngName(generator);
		int power = rngPower(generator);

		sf::Texture* tex = new sf::Texture();
		tex->loadFromFile("res/img/items/" + itemsArray[name] + ".png");
		this->items[i] = new Item(0.0, 0.0, itemsArray[name], 1, power, name, tex);
	}
}
