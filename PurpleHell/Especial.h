#ifndef  ESPECIAL_H
#define	 ESPECIAL_H

#include <iostream>
#include "Entity.h"
class Especial : public Entity

{
private:
	bool shouldDestroy = true;
	bool isPlaying = false;
	bool aoe = false;
	int offsetx = 0;
	int offsety = 0;
	std::string description;
	std::string job;
	int special = 0;
	void specialInit();
public:
	Especial();
	Especial(int special, std::string jobName);
	Especial(std::string name, Entity * entity);
	Especial(std::string name, int frames = 6 , int timer = 4, int sizeX = 16, int sizeY = 16);

	virtual ~Especial();

	void Thunder(Entity *entity[5]);
	void Fireball(Entity *entity);
	void MegaSlash(Entity *entity);

	void Action(Entity* entity);
	void Special(Entity *entity);
	void SetIsPlaying(bool value);
	bool GetIsPlaying();
	void updateAnimation(const float &dt);
	void createAnimation(int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height, int offsetx, int offsety);
	void animationDone();
	void SetDescription(std::string text);
	std::string GetDescription();

	int GetOffsetX();
	int GetOffsetY();
	bool isAOE();
};


#endif // ! SPELL_H