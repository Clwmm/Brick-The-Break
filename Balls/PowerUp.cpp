#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f _position)
{
	name = EnName::powerup;

	int a = rand();
	if (a % 3 == 1)
	{
		type = PUType::str;
		sprite.setTexture(*TextureManager::AcquireTexture("res/strong.png"));
	}
	else if (a % 3 == 2)
	{
		type = PUType::tri;
		sprite.setTexture(*TextureManager::AcquireTexture("res/triple.png"));
	}
	else
	{
		type = PUType::dble;
		sprite.setTexture(*TextureManager::AcquireTexture("res/double.png"));
	}

	r = sprite.getTexture()->getSize().y/2;
	height = sprite.getTexture()->getSize().y;
	width = sprite.getTexture()->getSize().x;
	speed = 200; //200
	angle = 90;

	x = _position.x;
	y = _position.y;

	mx = cos(angle * DEGTORAD) * speed;
	my = sin(angle * DEGTORAD) * speed;
}

PowerUp::~PowerUp()
{
}

void PowerUp::update(float deltatime)
{
	float actSpeed = sqrt((mx * mx) + (my * my));
	if (actSpeed > speed)
	{
		mx *= speed / actSpeed;
		my *= speed / actSpeed;
	}

	x += mx * deltatime;
	y += my * deltatime;

	if (x > 336 || x < -336 || y > 416 || y < -416)
		life = 0;
}
