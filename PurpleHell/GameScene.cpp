#include "GameScene.h"

//Inits

void GameScene::initFont()
{
	if (!this->font.loadFromFile(this->fontFile)) {
		throw("COULD NOT LOAD FONT");
	}
}

void GameScene::init()
{
	this->player = new Player();
	this->units = new Units();
	this->inventory = new Inventory();
	this->shop = new Shop();
}

void GameScene::initButtons()
{
	sf::Texture texture1;
	texture1.loadFromFile("res/hud/button1.png");

	sf::Texture texture3;
	texture3.loadFromFile("res/hud/button3.png");
	this->buttons.push_back(new Button(5, 18, 75, 20, &this->font, "LEVELS", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
	this->buttons.push_back(new Button(5, 48, 75, 20, &this->font, "SHOP", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
	this->buttons.push_back(new Button(5, 78, 75, 20, &this->font, "INVENTORY", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
	this->buttons.push_back(new Button(5, 108, 75, 20, &this->font, "UNITS", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
	this->buttons.push_back(new Button(5, 138, 75, 20, &this->font, "QUIT", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));

	this->buttonsUnits.push_back(new Button(91, 84, 2, 5, &this->font, "Equip", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));
	this->buttonsUnits.push_back(new Button(134, 84, 2, 5, &this->font, "Sell", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));
	this->buttonsUnits.push_back(new Button(134, 84, 2, 5, &this->font, "Remove", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));


	this->buttonsItems.push_back(new Button(91, 84, 2, 5, &this->font, "Equip", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));
	this->buttonsItems.push_back(new Button(134, 84, 2, 5, &this->font, "Sell", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));
	this->buttonsItems.push_back(new Button(134, 84, 2, 5, &this->font, "Remove", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));

	this->buttonsShop.push_back(new Button(91, 84, 2, 5, &this->font, "Buy", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));
	this->buttonsShop.push_back(new Button(134, 84, 2, 5, &this->font, "Refresh", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));


	this->buttonStages.push_back(new Button(91, 20, 2, 5, &this->font, "Level 1", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));
	this->buttonStages.push_back(new Button(140, 20, 2, 5, &this->font, "Level x", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture3));


}

void GameScene::initTexts()
{
	sf::Text goldText;
	sf::Text unitText;
	sf::Text panelText;
	sf::Text shopText;
	sf::Text equipText;

	goldText.setFont(this->font);
	goldText.setString("Gold: ");
	goldText.setCharacterSize(16);
	goldText.setPosition(5, 175);

	unitText.setFont(this->font);
	unitText.setString("YOUR UNITS");
	unitText.setCharacterSize(52);
	unitText.setPosition(550, 10);

	shopText.setFont(this->font);
	shopText.setString(" ");
	shopText.setCharacterSize(52);
	shopText.setPosition(75, 75);

	equipText.setFont(this->font);
	equipText.setString("EQUIPED ITEMS");
	equipText.setCharacterSize(32);
	equipText.setPosition(300, 300);

	panelText.setFont(this->font);
	panelText.setCharacterSize(16);
	panelText.setPosition(175, 0);

	this->texts[0] = goldText;
	this->texts[1] = unitText;
	this->texts[2] = panelText;
	this->texts[3] = equipText;

	this->textInfoMenu.setFont(this->font);
	this->textInfoMenu.setCharacterSize(15);
	this->textInfoMenu.setLineSpacing(0.9);

	this->textInfoPlayerTeam.setFont(this->font);
	this->textInfoPlayerTeam.setCharacterSize(14);

}
//Constructors

GameScene::GameScene()
{
}

GameScene::GameScene(sf::RenderWindow* window, std::stack<Scene*>* scenes) : Scene(window, scenes)
{
	this->initFont();
	this->init();
	this->initButtons();
	this->initTexts();
	this->textureBackground.loadFromFile("res/backgrounds/game.png");
	this->background.setTexture(textureBackground);
}


GameScene::~GameScene()
{
	delete this->player;
	delete this->units;
	delete this->inventory;
	delete this->shop;
	for (auto& it : this->buttons) {
		delete it;
	}
	for (auto& it : this->buttonsUnits) {
		delete it;
	}

	for (auto& it : this->buttonsItems) {
		delete it;
	}

	for (auto& it : this->buttonStages) {
		delete it;
	}

	for (auto& it : this->buttonsShop) {
		delete it;
	}
}

//Updates
void GameScene::update(const float& dt)
{
	this->updateMousePosition();
	this->updateFade(dt);
	this->updateInput(dt);
	this->updateButtons();

	this->player->update(this->mousePosView, dt, true);
	this->player->getEquipedItems()->updateEquipedItems(this->mousePosView, dt);
	this->player->MenuPosition();

	if (this->texts[2].getString() == "SHOP") {
		this->shop->Update(this->mousePosView, dt);
	}

	if (this->texts[2].getString() == "INVENTORY") {
		this->inventory->updateInventory(this->mousePosView, dt);
	}

	if (this->texts[2].getString() == "UNITS") {
		this->units->updateUnits(this->mousePosView, dt);
	}

	this->updateTexts();

}

void GameScene::updateTexts()
{
	this->texts[0].setString("Gold: " + std::to_string(this->player->getGold ()));
}

void GameScene::updateButtons()
{
	for (auto& it : this->buttons) {
		it->update(this->mousePosView);
	}
	for (auto& it : this->buttonsUnits) {
		it->update(this->mousePosView);
	}

	for (auto& it : this->buttonsItems) {
		it->update(this->mousePosView);
	}

	for (auto& it : this->buttonStages) {
		it->update(this->mousePosView);
	}
	for (auto& it : this->buttonsShop) {
		it->update(this->mousePosView);
	}
	//Menu
	if (this->buttons[0]->isPressed()) {
		this->Stages();
	}
	if (this->buttons[1]->isPressed()) {
		this->listShop();
	}
	if (this->buttons[2]->isPressed()) {
		this->listInventory();
	}
	if (this->buttons[3]->isPressed()) {
		this->listUnits();
	}
	if (this->buttons[4]->isPressed()) {
		this->Exit();
	}

	//Units
	if (this->texts[2].getString() == "UNITS" && this->units->getHero()) {
		if (this->buttonsUnits[0]->isPressed() && !this->buttonPressed) {
			this->EquipHero(this->units->getHero());
			this->buttonPressed = true;
		}
		if (this->buttonsUnits[1]->isPressed() && !this->buttonPressed) {
			this->sellHero();
			this->buttonPressed = true;
		}
	}
	if (this->texts[2].getString() == "UNITS" && this->player->getHero()) {
		if (this->buttonsUnits[2]->isPressed() && !this->buttonPressed) {
			this->RemoveHero(this->player->getHero());
			this->buttonPressed = true;
		}
	}

	//Inventory
	if (this->texts[2].getString() == "INVENTORY" && this->inventory->getItem()) {
		if (this->buttonsItems[0]->isPressed() && !this->buttonPressed) {
			this->EquipItem(this->inventory->getItem());
			this->buttonPressed = true;
		}
		if (this->buttonsItems[1]->isPressed() && !this->buttonPressed) {
			this->SellItem(this->inventory->getItem());
			this->buttonPressed = true;
		}
	}
	if (this->texts[2].getString() == "INVENTORY" && this->player->getEquipedItems()->getItem()) {
		if (this->buttonsItems[2]->isPressed() && !this->buttonPressed) {
			this->RemoveEquipedItem(this->player->getEquipedItems()->getItem());
			this->buttonPressed = true;
		}
	}
	//Stages
	if (this->texts[2].getString() == "LEVELS") {
		if (this->buttonStages[0]->isPressed() && !this->buttonPressed) {
			this->scenes->push(new BattleScene(this->window, this->scenes, 1));
			this->buttonPressed = true;
		}
		if (this->player->GetLevel() > 1) {
			this->buttonStages[1]->SetText("Level " + std::to_string(this->player->GetLevel()));
			if (this->buttonStages[1]->isPressed() && !this->buttonPressed) {
				this->scenes->push(new BattleScene(this->window, this->scenes, this->player->GetLevel()));
				this->buttonPressed = true;
			}
		}
	}
	//Shop
	if (this->texts[2].getString() == "SHOP") {
		if (this->buttonsShop[0]->isPressed() && !this->buttonPressed) {
			this->buttonPressed = true;
			this->buy();
		}
		if (this->buttonsShop[1]->isPressed() && !this->buttonPressed) {
			this->buttonPressed = true;
			if (this->player->getGold() >= 100) {
				this->shop->Refresh();
				this->player->updateGold(-100);
			}
		}
	}
}

void GameScene::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		//this->scenes->push(new BattleState(this->window, this->scenes));
	}
}

//Renders
void GameScene::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);
	this->renderTexts(target);
	this->player->render(target);
	this->player->getEquipedItems()->renderEquipedItems(target);

	if (this->texts[2].getString() == "UNITS") {
		this->units->renderUnits(target);
	}

	if (this->texts[2].getString() == "INVENTORY") {
		this->inventory->renderInventory(target);
	}
	if (this->texts[2].getString() == "SHOP") {
		this->shop->Render(target);
	}
	renderFade(target);
}

void GameScene::renderTexts(sf::RenderTarget* target)
{
	for (int i = 0; i < 4; i++) {
		target->draw(texts[i]);
	}
}

void GameScene::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons) {
		it->render(target);
	}

	if (this->player->getHero()) {
		this->showMenuInfo(&this->textInfoPlayerTeam, this->player->getHero(), { 70, 164 }, target);
	}

	if (this->texts[2].getString() == "UNITS" && this->units->getHero()) {
		this->buttonsUnits[0]->render(target);
		this->buttonsUnits[1]->render(target);
		this->showMenuInfo(&this->textInfoMenu, this->units->getHero(), {180, 72}, target);
	}

	if (this->texts[2].getString() == "UNITS" && this->player->getHero()) {
		this->buttonsUnits[2]->render(target);
	}

	if (this->texts[2].getString() == "INVENTORY" && this->inventory->getItem()) {
		this->buttonsItems[0]->render(target);
		this->buttonsItems[1]->render(target);
	}

	if (this->texts[2].getString() == "INVENTORY" && this->player->getEquipedItems()->getItem()) {
		this->buttonsItems[2]->render(target);
	}

	if (this->texts[2].getString() == "LEVELS") {
		this->buttonStages[0]->render(target);
		if (this->player->GetLevel() > 1) {
			this->buttonStages[1]->render(target);
		}
	}
	if (this->texts[2].getString() == "SHOP") {
		this->buttonsShop[1]->render(target);
	}
	if (this->texts[2].getString() == "SHOP" && (this->shop->GetSelectedHero() || this->shop->GetSelectedItem())) {
		this->buttonsShop[0]->render(target);
		if (this->shop->GetSelectedHero())this->showMenuInfo(&this->textInfoMenu, this->shop->GetSelectedHero(), { 180, 72 }, target);
		if (this->shop->GetSelectedItem())this->showMenuInfo(&this->textInfoMenu, this->shop->GetSelectedItem(), { 180, 72 }, target);

	}
}
void GameScene::listUnits()
{
	this->texts[2].setString("UNITS");
}

void GameScene::listInventory()
{
	this->texts[2].setString("INVENTORY");
}

void GameScene::listShop()
{
	this->texts[2].setString("SHOP");
}

void GameScene::Stages()
{
	this->texts[2].setString("LEVELS");
}

void GameScene::EquipHero(Hero* hero)
{

	if (!this->player->canEquipHero()) return;

	this->player->AddHeroToTeam(hero);
	this->units->removeHero(hero);

	this->units->Save();
	this->player->Save();

}

void GameScene::RemoveHero(Hero* hero)
{
	if (!this->units->canRemoveHero()) return;

	this->units->setUnits(hero);
	this->player->RemoveHero(hero);

	this->units->Save();
	this->player->Save();

}

void GameScene::EquipItem(Item* inventoryItem)
{
	if (!this->player->getEquipedItems()->canEquip()) return;

	this->player->getEquipedItems()->setItem(inventoryItem);
	this->inventory->removeItem(inventoryItem);

	this->inventory->save();
	this->player->getEquipedItems()->save();
}

void GameScene::RemoveEquipedItem(Item* equipedItem) {
	if (!this->inventory->canPutItemInInventory()) return;

	this->inventory->setItem(equipedItem);
	this->player->getEquipedItems()->removeItem(equipedItem);

	this->inventory->save();
	this->player->getEquipedItems()->save();
}

void GameScene::SellItem(Item* inventoryItem)
{
	this->inventory->removeItem(inventoryItem);
	this->player->updateGold(10);
	this->inventory->save();
	this->player->SaveInfoFile();

}

void GameScene::buy()
{
	Item* item = this->shop->GetSelectedItem();
	Hero* hero = this->shop->GetSelectedHero();

	if(item) if (!this->inventory->canPutItemInInventory()) return;
	if (hero) if (!this->units->canRemoveHero()) return;
	if (!this->player->CanBuy(item, hero)) return;

	if (item && this->inventory->canPutItemInInventory()) {
		this->inventory->setItem(item);
		this->shop->RemoveItem();
		this->inventory->save();
	}
	if (hero && this->units->canRemoveHero()) {
		this->units->setUnits(hero);
		this->shop->RemoveItem();
		this->units->Save();
	}
	this->player->SaveInfoFile();
}

void GameScene::sellHero()
{
	Hero* hero = this->units->getHero();
	this->units->removeHero(hero);
	this->player->updateGold(10);
	this->units->Save();
	this->player->SaveInfoFile();
}

void GameScene::showMenuInfo(sf::Text * text, Entity* entity,sf::Vector2f pos, sf::RenderTarget* target) {
	target->draw(*text);
	text->setPosition(pos);
	text->setString(
		entity->getName()
		+ " / "
		+ entity->GetJob()
		+ " / "
		+ "HP:" + std::to_string(entity->getHp())
		+ " / "
		+ "PW:" + std::to_string(entity->getPower())
		+ "\n"
		+ "Spell:" + "Thunder"/*this->units->getHero()->GetSpell()->getName()*/
		+ ": deals damage\nto all enemies");
}