#ifndef CREDITSSCENE_H
#define CREDITSSCENE_H

#include "Scene.h"
#include "Button.h"
#include <map>
#include <string>

class CreditsScene :
	public Scene
{
private:
	sf::Font font;

	sf::Sprite background;
	sf::Texture textureBackground;
	sf::Text texts[3];

	std::map<std::string, Button*> buttonsMap;

	void initFonts();
	void initButtons();
	void initTexts();

public:
	CreditsScene();
	CreditsScene(sf::RenderWindow *window, std::stack<Scene*> *scenes);
	virtual ~CreditsScene();

	void updateButtons();
	void updateInput(const float &dt);
	void update(const float& dt);
	void render(sf::RenderTarget *target = NULL);
	void renderButtons(sf::RenderTarget* target = NULL);
	void renderTexts(sf::RenderTarget* target);
};

#endif
