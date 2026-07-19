#include "Inventory.h"

void Inventory::initInventory()
{
	std::ifstream ifsInventory("res/Player/Inventory.txt");
	std::string title = " ", name = " ";
	int type = 0, hp = 0, power = 0, it = 0;


	if (ifsInventory.is_open())
	{
		//std::getline(ifsInventory, title);
		while (ifsInventory.good())
		{
			ifsInventory >> name >> hp >> power >> type;

			sf::Texture* tx;
			tx = new sf::Texture();
			tx->loadFromFile("res/img/items/" + name + ".png");

			this->items[it] = new Item(93 + (25 * it), 23, name, hp, power, type, tx);

			it++;

			if (it == this->maxItems) {
				break;
			}

		}

		ifsInventory.close();
	}
}

Inventory::Inventory()
{
	this->initInventory();
}

Inventory::~Inventory()
{
	for (int i = 0; i < this->maxItems; i++) {
		delete this->items[i];
	}
}

void Inventory::updateInventory(sf::Vector2f mousePos, const float& dt) {
	int count = 0;
	int countSecondLine = 0;
	for (int i = 0; i < this->maxItems; i++) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->items[i]->getSprite()->getGlobalBounds().contains(mousePos) && this->items[i]->getName() != "slot") {
				this->items[i]->setSelected(true);
			}
			else {
				this->items[i]->setSelected(false);
			}
		}
		if (count < 10) {
			this->items[i]->SetPosition(92 + (25 * count), 22);
			count++;
		}
		else {
			this->items[i]->SetPosition(92 + (25 * countSecondLine), 48);
			countSecondLine++;
		}

		this->items[i]->update(mousePos, dt);
	}


}

void Inventory::renderInventory(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxItems; i++) {
		this->items[i]->render(target);
	}
}

bool Inventory::selectedItem()
{
	for (auto i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getSelected()) {
			return true;
		}
	}
	return false;
}

Item* Inventory::getItem()
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getName() != "slot") {
			if (this->items[i]->getSelected()) {
				return this->items[i];
			}
		}
	}
	return nullptr;
}

void Inventory::setItem(int i, Item* item)
{
	this->items[i] = item;
}

void Inventory::setItem(Item* item)
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getName() == "slot") {
			this->items[i] = item;
			break;
		}
	}
}

void Inventory::save()
{
	std::fstream ofsInventory;
	ofsInventory.open("res/Player/Inventory.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; i < this->maxItems; i++) {
		ofsInventory
			<< this->items[i]->getName()
			<< " " << this->items[i]->getHp()
			<< " " << this->items[i]->getPower()
			<< " " << this->items[i]->getSpecial() << std::endl;
	}
	ofsInventory.close();
}

bool Inventory::canPutItemInInventory()
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getName() == "slot") {
			return true;
		}
	}
	return false;
}

Item* Inventory::getItemById(int i)
{
	return this->items[i];
}
void Inventory::removeItem(Item* inventoryItem)
{
	sf::Texture emptyTex;
	emptyTex.loadFromFile("res/img/items/slot.png");
	Item* empty = new Item(0, 0, "slot", 0, 0, 0, &emptyTex);
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i] == inventoryItem) {
			this->items[i] = empty;
			break;
		}
	}
}
int Inventory::inventoryNumber()
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getSelected()) {
			return i;
		}
	}
	return -1;
}
