#ifndef BUTTON_H
#define BUTTON_H


#include <iostream>

#include "Button.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"



class Button
{
private:
	int state;
	bool disabled = false;
	//sf::RectangleShape shape;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Font *font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;


public:
	Button();
	Button(float x, float y, float width, float height, sf::Font *font,
		std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Texture texture);

	virtual ~Button();

	//functions
	void render(sf::RenderTarget *target);
	void update(sf::Vector2f mousePos);
	void SetText(std::string text);

	void setDisabled(bool d);

	//accessors
	const bool isPressed() const;
};

#endif