#include "Especial.h"
#include <thread>

void Especial::specialInit()
{
	if (this->job == "mage") {

		switch (this->special)
		{
		case 1:
			this->name = "thunder";
			this->description = "Deals damage to all enemies.";
			this->aoe = true;
			this->createAnimation(0, 0, 4, 0, 16, 64, 0, -48);
			break;
		case 2:
			this->name = "Fireball";
			this->description = "Damage and burn one enemy.";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Fire0");
			break;
		case 3:
			this->name = "Waterfall";
			this->description = "Deals extra damage to one enemy.";
			this->createAnimation(0, 0, 5, 0, 32, 48, 0, -36, "Water");
			break;
		}
	}
	else if (this->job == "rogue") {
		switch (this->special)
		{
		case 1:
			this->name = "Steal";
			this->description = "Damage one enemy, steal gold.";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash2");
			break;
		case 2:
			this->name = "Poison Dagger";
			this->description = "Deals damage to one enemy with a poison knife";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Poison");
			break;
		case 3:
			this->name = "Kick";
			this->description = "Stun an enemy";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash");
			break;
		}
	}
	else if (this->job == "knight") {
		switch (this->special)
		{
		case 1:
			this->name = "Double slash";
			this->description = "Double damage to one enemy.";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash");
			break;
		case 2:
			this->name = "Rage";
			this->description = "Deals x4 more damage to one enemy.";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Fire1");
			break;
		case 3:
			this->name = "Kick";
			this->description = "Stun one enemy.";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash2");
			break;
		}
	}
	else if (this->job == "demonhunter") {
		switch (this->special)
		{
		case 1:
			this->name = "Scars slash";
			this->description = "x3 damage to one enemy.";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash2");
			break;
		case 2:
			this->name = "Drain Blood";
			this->description = "Poison damage to one enemy.";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Poison");
			break;
		case 3:
			this->name = "Punch";
			this->description = "Damage one enemy.";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash");
			break;
		}
	}
	else if (this->job == "warlock") {
		switch (this->special)
		{
		case 1:
			this->name = "Drain Life";
			this->description = "Deals damage to one enemy and heal half of the damage.";
			this->createAnimation(0, 0, 5, 0, 32, 48, 0, -36, "Water");
			break;
		case 2:
			this->name = "Death Touch";
			this->description = "Instakill one enemy, lose half HP.";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Poison");
			break;
		case 3:
			this->name = "Curse";
			this->description = "Deals curse damage to one enemy.";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Fire2");
			break;
		}
	}
	else if (this->job == "archer") {
		switch (this->special)
		{
		case 1:
			this->name = "Double slash";
			this->description = "Double damage to one enemy.";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash");
			break;
		case 2:
			this->name = "Poison Dagger";
			this->description = "Deals damage to one enemy with a poison knife";
			this->createAnimation(0, 0, 4, 0, 32, 32, 0, -24, "Poison");
			break;
		case 3:
			this->name = "Kick";
			this->description = "Stun an enemy";
			this->createAnimation(0, 0, 7, 0, 16, 16, 0, -12, "slash2");
			break;
		}
	}
}

Especial::Especial()
{

}
Especial::Especial(std::string name,int frames, int timer,  int sizeX, int sizeY)
{
	this->name = name;
	this->texture = new sf::Texture();
	this->texture->loadFromFile("res/img/Effects/" + this->name + ".png");
	this->CreateSprite(texture);
	this->createAnimationComponent(*texture);
	this->animationComponent->addAnimation(this->name + "_animation", timer, 0, 0, frames, 0, sizeX, sizeY);
}
Especial::Especial( int special, std::string jobName)
{
	this->special = special;
	this->job = jobName;
	this->specialInit();
}

Especial::Especial(std::string name, Entity* entity)
{
	this->name = name;
	this->texture = new sf::Texture();
	this->texture->loadFromFile("res/img/Effects/" + this->name + ".png");
	this->CreateSprite(texture);
	this->createAnimationComponent(*texture);
	this->SetPosition(entity->getPosition().x, entity->getPosition().y);
	this->animationComponent->addAnimation(this->name + "_animation", 8, 0, 0, 4, 0, 16, 16);
}

Especial::~Especial()
{
	//delete this->sprite;
	//delete this->texture;
	//delete this->animationComponent;
}

void Especial::Thunder(Entity* entity[5])
{

}

void Especial::Fireball(Entity* entity)
{
	entity->setHp(entity->getHp() - 10);
}

void Especial::MegaSlash(Entity* entity)
{
	entity->setHp(entity->getHp() - 10);
}

void Especial::Action(Entity* entity)
{
}

void Especial::Special(Entity* entity)
{
}

void Especial::SetIsPlaying(bool value)
{
	this->isPlaying = value;
	if (!value)
		this->extraAOEPositions.clear();
}

void Especial::addAOEPosition(float x, float y)
{
	this->extraAOEPositions.push_back({ x, y });
}

void Especial::render(sf::RenderTarget* target)
{
	if (!this->sprite) return;
	target->draw(*this->sprite);
	sf::Vector2f original = this->sprite->getPosition();
	for (const auto& pos : this->extraAOEPositions) {
		this->sprite->setPosition(pos);
		target->draw(*this->sprite);
	}
	this->sprite->setPosition(original);
}

bool Especial::GetIsPlaying()
{
	return this->isPlaying;
}

void Especial::animationDone()
{
	if (!this->animationComponent) { this->isPlaying = false; return; }
	std::string animation = this->name + "_animation";
	if (this->animationComponent->isDone(animation)) {
		this->isPlaying = false;
	}
}

void Especial::SetDescription(std::string text)
{
	this->description = text;
}

void Especial::updateAnimation(const float& dt)
{
	if (this->isPlaying) {
		if (!this->animationComponent) { this->isPlaying = false; return; }
		std::string animation = this->name + "_animation";
		this->animationComponent->play(animation, dt);
		if (this->animationComponent->isDone(animation)) {
			this->isPlaying = false;
		}
	}
}

std::string Especial::GetDescription()
{
	return this->description;
}

int Especial::GetOffsetX()
{
	return this->offsetx;
}

int Especial::GetOffsetY()
{
	return this->offsety;
}

bool Especial::isAOE()
{
	return this->aoe;
}


void Especial::createAnimation(int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height, int offsetx, int offsety, const std::string& textureName)
{
	this->offsetx = offsetx;
	this->offsety = offsety;
	this->texture = new sf::Texture();
	const std::string& file = textureName.empty() ? this->name : textureName;
	this->texture->loadFromFile("res/img/Effects/" + file + ".png");
	this->CreateSprite(texture);
	this->createAnimationComponent(*texture);
	this->animationComponent->addAnimation(this->name + "_animation", 4, start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}


