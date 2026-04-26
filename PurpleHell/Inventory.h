#ifndef INVENTORY_H
#define INVENTORY_H

#include <SFML/Graphics.hpp>

#include "Item.h"
#include <fstream>
#include <sstream>
#include <list> 
#include <iterator> 
class Inventory
{
private:
	static const int maxItems = 20;
	sf::Texture* texture;
	sf::Sprite* sprite;

	Item * items[maxItems];
	
	void initInventory();
public:
	Inventory();
	virtual ~Inventory();

	void renderInventory(sf::RenderTarget *target);
	void updateInventory(sf::Vector2f mousePos, const float &dt);
	void setItem(int i, Item* item);
	void setItem(Item* item);
	void save();
	bool canPutItemInInventory();
	bool selectedItem();
	int inventoryNumber();
	Item* getItem();
	Item* getItemById(int i);
	void removeItem(Item* inventoryItem);
};

#endif