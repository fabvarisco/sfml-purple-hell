#include "EquipedItems.h"



void EquipedItems::initEquipedItems()
{
	std::ifstream ifsEquipedItems("res/Player/equiped.txt");
	ArquivoEquiped(ifsEquipedItems, 0);
}

EquipedItems::EquipedItems()
{
	this->initEquipedItems();
}


EquipedItems::~EquipedItems()
{
	for (int i = 0; i < this->maxItems; i++) {
		delete this->items[i];
	}
}

void EquipedItems::renderEquipedItems(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]) this->items[i]->render(target);
	}
}

void EquipedItems::renderActions(sf::RenderTarget* target)
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->GetAction()) {
			if (this->items[i]->GetAction()->GetIsPlaying()) {
				std::cout << "RENDER" << std::endl;
				this->items[i]->GetAction()->render(target);
			}
		}
	}
}

void EquipedItems::updateEquipedItems(sf::Vector2f mousePos, const float& dt, bool deselect)
{

	for (int i = 0; i < this->maxItems; i++) {

		if (this->items[i]) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (this->items[i]->getSprite()->getGlobalBounds().contains(mousePos) && this->items[i]->getName() != "slot") {
					this->items[i]->setSelected(true);
				}
				else if (deselect) {
					//na batalha a selecao precisa persistir ate o clique no botao ITEM
					this->items[i]->setSelected(false);
				}
			}
			if (this->items[i]->GetAction()->GetIsPlaying()) {
				std::cout << "UPDATE" << std::endl;
				this->items[i]->GetAction()->updateAnimation(dt);
			}
			this->items[i]->SetPosition(93 + (25 * i), 118);
			this->items[i]->update(mousePos, dt);
		}
	}
}

void EquipedItems::removeItem(int id)
{
	sf::Texture emptyTex;
	emptyTex.loadFromFile("res/img/items/slot.png");
	Item* empty = new Item(0, 0, "slot", 0, 0, 0, &emptyTex);
	this->items[id] = empty;
}

void EquipedItems::removeItem(Item* equipedItem)
{
	sf::Texture emptyTex;
	emptyTex.loadFromFile("res/img/items/slot.png");
	Item* empty = new Item(0, 0, "slot", 0, 0, 0, &emptyTex);
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i] == equipedItem) {
			this->items[i] = empty;
			break;
		}
	}
}

Item* EquipedItems::getItem()
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]) {
			if (items[i]->getSelected()) {
				return this->items[i];
			}
		}
	}
	return nullptr;


}

Item* EquipedItems::getItemById(int i)
{
	return this->items[i];
}

void EquipedItems::setItem(Item* item)
{

	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getName() == "slot") {
			this->items[i] = item;
			break;
		}
	}
}

int EquipedItems::UnitNumber(Entity* item)
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getName() == item->getName()) {
			return i;
		}
	}
	return -1;
}
bool EquipedItems::canEquip()
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]->getName() == "slot") {
			return true;
		}
	}
	return false;
}
void EquipedItems::save()
{
	std::fstream ofsEquiped;
	ofsEquiped.open("res/Player/equiped.txt", std::ofstream::out | std::ofstream::trunc);
	for (int t = 0; t < this->maxItems; t++) {
		if (t < this->maxItems - 1) {
			ofsEquiped
				<< this->items[t]->getName()
				<< " " << this->items[t]->getHp()
				<< " " << this->items[t]->getPower()
				<< " " << this->items[t]->getSpecial() << std::endl;
		}
		else {
			ofsEquiped
				<< this->items[t]->getName()
				<< " " << this->items[t]->getHp()
				<< " " << this->items[t]->getPower()
				<< " " << this->items[t]->getSpecial();
		}
	}
	ofsEquiped.close();
}
int EquipedItems::getItemId()
{
	for (int i = 0; i < this->maxItems; i++) {
		if (this->items[i]) {
			if (items[i]->getSelected()) {
				return i;
			}
		}
	}
	return -1;
}
//Arquivos
void EquipedItems::ArquivoEquiped(std::ifstream& ifsEquipedItems, int i)
{
	std::string name = " ";
	int hp = 0, power = 0, type = 0;

	if (ifsEquipedItems.is_open())
	{
		if (!ifsEquipedItems.eof())
		{
			ifsEquipedItems >> name >> hp >> power >> type;
			sf::Texture* tex = new sf::Texture();
			tex->loadFromFile("res/img/items/" + name + ".png");
			this->items[i] = (new Item(93 + (25 * i), 118, name, hp, power, type, tex));
			i++;
			ArquivoEquiped(ifsEquipedItems, i);
			std::cout << name << hp << power << type << std::endl;


		}
		else {
			ifsEquipedItems.close();
		}
	}
}
