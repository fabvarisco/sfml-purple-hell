#ifndef EQUIPEDITEMS_H
#define EQUIPEDITEMS_H

#include "Inventory.h"

class EquipedItems
{

private:
	static const int maxItems = 6;
	Item *items[maxItems];
	void initEquipedItems();
	void ArquivoEquiped(std::ifstream &ifsEquipedItems, int i);
public:
	EquipedItems();

	void renderEquipedItems(sf::RenderTarget *target);
	void renderActions(sf::RenderTarget* target);
	void updateEquipedItems(sf::Vector2f mousePos,const float &dt, bool deselect = false);
	void removeItem(Item * equipedItem);
	void removeItem(int equipedItemId);
	void setItem(Item *item);
	void save();

	bool canEquip();
	
	int UnitNumber(Entity *item);
	int getItemId();

	Item *getItem();
	Item *getItemById(int i);

	virtual ~EquipedItems();
};

#endif // !EQUIPEITEMS_H