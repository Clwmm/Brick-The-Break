#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "MapGenerator.h"
#include "Entity.h"
#include "Player.h"
#include "Ball.h"

enum class GameStatus { mainMenu, chooselevel, game};
enum class MainMenuStatus { play, exit };
enum class End { win, lose, normal};

class Game
{
private:
	sf::RenderWindow* window;
	GameStatus status = GameStatus::mainMenu;
	MainMenuStatus mmstatus = MainMenuStatus::play;
	End endstatus = End::normal;
	sf::Font* font = new sf::Font;

	std::vector<Entity*>* bals = new std::vector<Entity*>;
	std::vector<Entity*> rend_bals;
	std::vector<Entity*>* brcs = new std::vector<Entity*>;
	std::vector<Entity*>* pups = new std::vector<Entity*>;

	std::vector<Entity*>* temp_entities = new std::vector<Entity*>;

	float deltatime = 0;
	sf::Clock clock;

	Player* p;
	int actual_level = 1;
	int wallbrics = 0;
private:
	bool intersects(Entity* a, Entity* b);
	void colision(Entity* a, Entity* b);
	void player_colision(Entity* a, Entity* b);
public:
	bool close = false;
	bool restart = false;
private:
	bool render = false;
	bool counting = false;
public:
	void start();
	void mainMenu();
	void chooselevel(); 
	void game();
	void renderingthread();
public:
	Game(sf::RenderWindow& _window);
};

