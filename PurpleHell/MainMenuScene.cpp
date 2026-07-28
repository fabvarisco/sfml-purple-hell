#include "MainMenuScene.h"
#include "NewGame.h"
#include "CreditsScene.h"



void MainMenuScene::initFonts()
{
	if (!this->font.loadFromFile(this->fontFile)) {
		throw("COULD NOT LOAD FONT");
	}
}

void MainMenuScene::initButtons()
{
	sf::Texture texture1;
	texture1.loadFromFile("res/hud/button1.png");


	//Map
	this->buttonsMap["STARTGAME"] = (new Button(135, 80, 75, 20, &this->font, "New Game", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
	this->buttonsMap["QUIT"] = (new Button(135, 110, 75, 20, &this->font, "QUIT", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
	this->buttonsMap["CREDITS"] = (new Button(135, 140, 75, 20, &this->font, "Credits", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));

}

void MainMenuScene::initTexts()
{
	sf::Text creditname; 

	creditname.setFont(this->font);
	creditname.setString("Trabalho GA\nEstrutura de dados\nFabricio Varisco");
	creditname.setCharacterSize(32);
	creditname.setPosition(475, 75);


	this->texts[0] = creditname;


}

MainMenuScene::MainMenuScene()
{
}

MainMenuScene::MainMenuScene(sf::RenderWindow *window, std::stack<Scene*> *scenes) : Scene(window, scenes)
{

	this->showCredits = false;
	this->initFonts();
	this->initButtons();
	this->initTexts();
	this->textureBackground.loadFromFile("res/backgrounds/Menu.png");
	this->background.setTexture(textureBackground);

}

MainMenuScene::~MainMenuScene()
{
	auto it = this->buttonsMap.begin();
	for (it = this->buttonsMap.begin(); it != this->buttonsMap.end(); ++it) {
		delete it->second;
	}
}


void MainMenuScene::updateButtons()
{

	for (auto &it : this->buttons) {

		it->update(this->mousePosView);
	}

	for (auto &it : this->buttonsMap) {

		it.second->update(this->mousePosView);
	}



	/*if (this->buttons[0]->isPressed()) {
		this->scenes->push(new GameScene(this->window, this->scenes));
		//this->endScene();

	}

	if (this->buttons[1]->isPressed()) {
		this->endScene();
	}
	if (this->buttons[2]->isPressed()) {
		this->showCredits = true;
	}*/

	if (this->buttonsMap["STARTGAME"]->isPressed()) {
		NewGame::resetSaveFiles();
		this->scenes->push(new GameScene(this->window, this->scenes));
	}

	if (this->buttonsMap["CREDITS"]->isPressed()) {
		this->scenes->push(new CreditsScene(this->window, this->scenes));
	}

	if (this->buttonsMap["QUIT"]->isPressed()) {
		this->Exit();
	}

}

void MainMenuScene::updateInput(const float & dt)
{
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		this->scenes->push(new GameScene(this->window, this->scenes));
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->endScene();
	}

}


void MainMenuScene::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttons) {

		it->render(target);
	}
	for (auto &it : this->buttonsMap) {

		it.second->render(target);
	}

}


void MainMenuScene::update(const float & dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();
	this->updateFade(dt);

}


void MainMenuScene::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderButtons(target);

	if (this->showCredits) {
		this->renderTexts(target);
	}

	renderFade(target);

}

void MainMenuScene::renderTexts(sf::RenderTarget* target)
{
	for (int i = 0; i < 3; i++) {
		target->draw(texts[i]);
	}
}