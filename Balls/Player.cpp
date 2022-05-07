#include "Player.h"

Player::Player()
{
	sprite.setTexture(*TextureManager::AcquireTexture("res/p.png"));
	sprite.setColor(sf::Color(121, 80, 255));
	height = sprite.getTexture()->getSize().y;
	width = sprite.getTexture()->getSize().x;
	name = EnName::player;
	x = 0;
	y = 368;
	speed = 250;
}

Player::~Player()
{
}

void Player::update(float deltatime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		x -= speed * deltatime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		x += speed * deltatime;
	if (x < -248)
		x = -248;
	if (x > 248)
		x = 248;
}
