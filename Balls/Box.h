#pragma once
#include "Entity.h"
#include "PowerUp.h"

class Box: public Entity
{
public:
	Box(EnName _name, sf::Vector2f _position, std::vector<Entity*>* _temp_entities = nullptr);
	~Box();
	void update(float deltatime);
private:
	std::vector<Entity*>* temp_ent;
	int temp_life = 0;
};