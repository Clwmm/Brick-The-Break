#include "Entity.h"

void Entity::uptade_angle(float angle)
{
}

void Entity::update(float deltatime)
{
}

void Entity::draw(sf::RenderWindow& window)
{
	sprite.setPosition(x - (sprite.getTexture()->getSize().x / 2), y - (sprite.getTexture()->getSize().y / 2));
	window.draw(sprite);

	/*sf::CircleShape circle(r);
	circle.setFillColor(sf::Color(255, 0, 0, 170));
	circle.setPosition(x, y);
	circle.setOrigin(r, r);
	window.draw(circle);*/
}

Entity::Entity()
{
	life = 1;
}

Entity::~Entity()
{
}
