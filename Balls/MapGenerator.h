#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Entity.h"
#include "Box.h"

class MapGenerator
{
public:
	MapGenerator(std::vector<Entity*>* brcs, std::vector<Entity*>* temp_entities, char level, int& wallbrics);
};

