#include "Ball.h"

Ball::Ball(float _x, float _y)
{
	sprite.setTexture(*TextureManager::AcquireTexture("res/ball.png"));
	sprite.setColor(sf::Color(121, 200, 255));
	name = EnName::ball;
	x = _x;
	y = _y;
	r = sprite.getTexture()->getSize().y/2;

	height = sprite.getTexture()->getSize().y;
	width = sprite.getTexture()->getSize().x;
	speed = 300; //230
	angle = (rand() % 141) + 200;  //Functions::fromRandom(200, 340);
	mx = cos(angle * DEGTORAD) * speed;
	my = sin(angle * DEGTORAD) * speed;
}

Ball::~Ball()
{
}

void Ball::update(float deltatime)
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

void Ball::uptade_angle(float angle)
{
	mx = cos(angle * DEGTORAD) * speed;
	my = sin(angle * DEGTORAD) * speed;
}
