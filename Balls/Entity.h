#pragma once
#include <SFML/Graphics.hpp>
#include "Functions.h"
#include "TextureManager.h"

#define DEGTORAD 0.017453

enum class EnName { player, ball, wall, dwall, box , powerup};
enum class PUType { str, dble, tri };

class Entity
{
public:
	//powerup
	PUType type;
	//ball
	int strong = 0;
	float angle;
	float mx, my;
	//all
	float width, height;
	float x, y, r = 0;
	int life = 1;
	bool hit;
	float speed;
	EnName name;
public:
	sf::Sprite sprite;
public:
	//ball & player
	virtual void uptade_angle(float angle);
	//all
	virtual void update(float deltatime);
	virtual void draw(sf::RenderWindow& window);
	Entity();
	virtual ~Entity();
};