#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureManager::texturePointers;

int main()
{
	FreeConsole();
	srand(time(0));
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(670, 200), "Brick the Break", sf::Style::None); // 672, 832
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