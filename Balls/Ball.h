#pragma once
#include "Entity.h"

class Ball: public Entity
{
public:
	Ball(float _x = 0, float _y = 345);
	~Ball();
	void update(float deltatime);
	void uptade_angle(float angle);
};

