#include "Inventory.h"
#include "BinaryIO.h"

void Inventory::initInventory()
{
	std::ifstream ifsInventory("res/Player/Inventory.txt", std::ios::binary);

	if (!ifsInventory.is_open()) return;
	if (!bin::readHeader(ifsInventory)) { ifsInventory.close(); return; }

	int count = bin::readInt(ifsInventory);
	for (int it = 0; it < count && it < this->maxItems; it++) {
		std::string name = bin::readStr(ifsInventory);
		int hp = bin::readInt(ifsInventory);
		int power = bin::readInt(ifsInventory);
		int type = bin::readInt(ifsInventory);
		if (!ifsInventory) break;

		sf::Texture* tx;
		tx = new sf::Texture();
		tx->loadFromFile("res/img/items/" + name + ".png");

		this->items[it] = new Item(93 + (25 * it), 23, name, hp, power, type, tx);
	}

	ifsInventory.close();
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
	ofsInventory.open("res/Player/Inventory.txt", std::ios::out | std::ios::trunc | std::ios::binary);

	bin::writeHeader(ofsInventory);
	bin::writeInt(ofsInventory, this->maxItems);
	for (int i = 0; i < this->maxItems; i++) {
		bin::writeStr(ofsInventory, this->items[i]->getName());
		bin::writeInt(ofsInventory, this->items[i]->getHp());
		bin::writeInt(ofsInventory, this->items[i]->getPower());
		bin::writeInt(ofsInventory, this->items[i]->getSpecial());
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
