#include "Enemy.h"
#include <cstdlib>



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

	// Special sorteado por inimigo (1-3), 1 MP / uma vez por partida.
	this->special = std::rand() % 3 + 1;
	switch (this->special) {
	case 1: // AOE em todos os herois — reusa o thunder do player (aoe = true)
		this->spell = new Especial(1, "mage");
		break;
	case 2: // Cura o proprio inimigo
		this->spell = new Especial("Heal0Back");
		break;
	default: // 3 — dano alto em alvo unico
		this->spell = new Especial("thunder", 4, 4, 16, 64);
		break;
	}

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
	this->spell->SetIsPlaying(true);
	this->spell->SetPosition(entity->getPosition().x, entity->getPosition().y + this->spell->GetOffsetY());

	if (this->special == 2) {
		// Cura: ignora o alvo, cura o proprio inimigo.
		this->setHp(this->getHp() + this->power * 2);
	}
	else if (this->special == 3) {
		// Dano alto em alvo unico.
		entity->setDamage(this->power * 3);
	}
	else {
		// AOE: dano por herói (aplicado em laço por BattleScene::enemySpecial).
		entity->setDamage(this->power);
	}

	this->setCanUseSpecial(false);
	this->setPlayed(true);
	this->setSelected(false);
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

