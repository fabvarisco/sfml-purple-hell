#include "Enemy.h"



Enemy::Enemy()
{
}

Enemy::Enemy(float x, float y, std::string name, int hp, int power, sf::Texture* texture)
{
	this->name = name;
	this->hp = hp;
	this->power = power;
	this->CreateSprite(texture);
	this->SetPosition(x, y);
	this->createAnimationComponent(*texture);
	this->actionEffect = new Especial("slash");
	this->spell = new Especial("slash");
	this->animationComponent->addAnimation("IDLE_MONSTER", 90.f, 0, 0, 1, 0, 16, 16);
}

Enemy::~Enemy()
{
}

void Enemy::Action(Entity* entity)
{		
	this->actionEffect->SetIsPlaying(true);
	this->actionEffect->SetPosition(entity->getPosition().x, entity->getPosition().y);
	entity->setSelected(false);
	entity->setDamage(this->power);
	this->setPlayed(true);
	this->setSelected(false);
	
}

void Enemy::Special(Entity *entity)
{
}

Especial* Enemy::GetSpell()
{
	return this->spell;
}

Especial* Enemy::GetAction()
{
	return this->actionEffect;
}


void Enemy::update(sf::Vector2f mousePos, const float& dt)
{	
	Entity::update(mousePos, dt);
	if (this->hp > 0) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (this->sprite->getGlobalBounds().contains(mousePos)) {
					this->selected = true;
			}else{
				this->selected = false;
			}
		}
	}
	else {
		this->selected = false;	
		this->played = true;
	}
}

int Enemy::getHp()
{
	return this->hp;
}

std::string Enemy::getName()
{
	return this->name;
}

void Enemy::removeSelected()
{
	this->selected = false;
}

void Enemy::updateAnimation(const float & dt)
{
	if(this->getHp() > 0){
		this->animationComponent->play("IDLE_MONSTER", dt);
	}
}

