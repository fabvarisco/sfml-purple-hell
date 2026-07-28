#include "CreditsScene.h"

void CreditsScene::initFonts()
{
	if (!this->font.loadFromFile(this->fontFile)) {
		throw("COULD NOT LOAD FONT");
	}
}

void CreditsScene::initButtons()
{
	sf::Texture texture1;
	texture1.loadFromFile("res/hud/button1.png");

	this->buttonsMap["BACK"] = (new Button(135, 155, 75, 20, &this->font, "Back", sf::Color::White, sf::Color::Black, sf::Color::Blue, texture1));
}

void CreditsScene::initTexts()
{

	sf::Text author;
	author.setFont(this->font);
	author.setString("Developed by\nFabricio Varisco Oliveira");
	author.setCharacterSize(16);
	author.setPosition(60, 70);
	this->texts[0] = author;

	sf::Text repo;
	repo.setFont(this->font);
	repo.setString("github.com/fabvarisco/sfml-purple-hell");
	repo.setCharacterSize(14);
	repo.setPosition(45, 120);
	this->texts[1] = repo;
}

CreditsScene::CreditsScene()
{
}

CreditsScene::CreditsScene(sf::RenderWindow *window, std::stack<Scene*> *scenes) : Scene(window, scenes)
{
	this->initFonts();
	this->initButtons();
	this->initTexts();
	this->textureBackground.loadFromFile("res/backgrounds/Menu.png");
	this->background.setTexture(textureBackground);
}

CreditsScene::~CreditsScene()
{
	for (auto it = this->buttonsMap.begin(); it != this->buttonsMap.end(); ++it) {
		delete it->second;
	}
}

void CreditsScene::updateButtons()
{
	for (auto &it : this->buttonsMap) {
		it.second->update(this->mousePosView);
	}

	if (this->buttonsMap["BACK"]->isPressed()) {
		this->endScene();
	}
}

void CreditsScene::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->endScene();
	}
}

void CreditsScene::renderButtons(sf::RenderTarget * target)
{
	for (auto &it : this->buttonsMap) {
		it.second->render(target);
	}
}

void CreditsScene::renderTexts(sf::RenderTarget* target)
{
	for (int i = 0; i < 3; i++) {
		target->draw(this->texts[i]);
	}
}

void CreditsScene::update(const float & dt)
{
	this->updateInput(dt);
	this->updateMousePosition();
	this->updateButtons();
	this->updateFade(dt);
}

void CreditsScene::render(sf::RenderTarget * target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);
	this->renderTexts(target);
	this->renderButtons(target);
	this->renderFade(target);
}
