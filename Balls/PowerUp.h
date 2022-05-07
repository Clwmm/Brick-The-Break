#pragma once
#include "Entity.h"

class PowerUp: public Entity
{
public:
	PowerUp(sf::Vector2f _position);
	~PowerUp();
	void update(float deltatime);
};

