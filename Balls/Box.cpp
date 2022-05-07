#include "Box.h"

Box::Box(EnName _name, sf::Vector2f _position, std::vector<Entity*>* _temp_entities)
{
	name = _name;
	x = _position.x;
	y = _position.y;
	temp_ent = _temp_entities;

	sprite.setTexture(*TextureManager::AcquireTexture("res/box.png"));
	height = sprite.getTexture()->getSize().y;
	width = sprite.getTexture()->getSize().x;

	switch (name)
	{
	case EnName::wall:
		sprite.setColor(sf::Color(145, 145, 145));
		break;
	case EnName::dwall:
		sprite.setColor(sf::Color(255, 0, 0));
		break;
	case EnName::box:
		sprite.setColor(sf::Color(230, 187, 241));
		break;
	}
}

Box::~Box()
{
	if (name == EnName::box && rand() % 14 == 0)
	{
		PowerUp* e = new PowerUp(sf::Vector2f(x, y));
		temp_ent->insert(temp_ent->begin(), e);
	}
}

void Box::update(float deltatime)
{
	if (temp_life != life && name == EnName::box)
	{
		temp_life = life;
		switch (life)
		{
		case 1:
			sprite.setColor(sf::Color(230, 187, 241));
			break;
		case 2:
			sprite.setColor(sf::Color(150, 107, 161));
			break;
		case 3:
			sprite.setColor(sf::Color(70, 27, 81));
			break;
		}
	}
}
