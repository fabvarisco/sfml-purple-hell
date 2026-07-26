#include "Button.h"

Button::Button()
{
}

Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, sf::Texture texture)
{
	this->state = 0;


	this->texture = texture;
	this->sprite = sf::Sprite(this->texture);
	this->sprite.setTexture(this->texture);


	this->sprite.setPosition(x, y);


	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(14);
	this->text.setPosition(
		this->sprite.getPosition().x + (this->sprite.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->sprite.getPosition().y + (this->sprite.getGlobalBounds().height / 2.f) / 2.f - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->hoverColor = hoverColor;
	this->sprite.setColor(this->idleColor);
}


Button::~Button()
{
	
}

const bool Button::isPressed() const
{
	if (!this->disabled && this->state == 2) {
		return true;
	}
	else {
		return false;
	}
}

void Button::setDisabled(bool d)
{
	this->disabled = d;
}

void Button::update(sf::Vector2f mousePos)
{
	if (this->disabled) {
		this->state = 0;
		this->sprite.setColor(sf::Color(80, 80, 80));
		return;
	}
	this->state = 0;
	if (this->sprite.getGlobalBounds().contains(mousePos)) {
		state = 1;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			state = 2;
		}
	}
	switch (state)
	{
	case 0:
		this->sprite.setColor(this->idleColor);
		break;
	case 1:
		this->sprite.setColor(this->hoverColor);
		break;
	case 2:
		this->sprite.setColor(this->activeColor);
		break;
	default:
		this->sprite.setColor(this->idleColor);
		break;
	}
}

void Button::SetText(std::string text)
{
	this->text.setString(text);
}



void Button::render(sf::RenderTarget * target)
{
	if (target){
		target->draw(this->sprite);
		target->draw(this->text);
	}

	
}