#pragma once
#include "Entity.h"

class Player: public Entity
{
private:
	float time = 0;
public:
	Player();
	~Player();
public:
	void update(float deltatime);
};

