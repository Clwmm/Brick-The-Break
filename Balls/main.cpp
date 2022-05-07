#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureManager::texturePointers;

int main()
{
	FreeConsole();
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(672, 900), "Brick the Break", sf::Style::None); // 672, 832
	window->display();
	window->setFramerateLimit(240);
	Game* game = new Game(*window);
	while (!game->close)
		game->start();
	window->close();
	delete game;
	delete window;
	return 0;
}