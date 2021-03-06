#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "MapGenerator.h"
#include "Entity.h"
#include "Player.h"
#include "Ball.h"

enum class GameStatus { logo, mainMenu, chooselevel, credits, game};
enum class MainMenuStatus { play, credits, exit };
enum class End { win, lose, normal};

class Game
{
private:
	sf::RenderWindow* window;
	GameStatus status = GameStatus::logo;
	MainMenuStatus mmstatus = MainMenuStatus::play;
	End endstatus = End::normal;
	sf::Font* font = new sf::Font;
	sf::Image icon;

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
	bool first = true;
public:
	void start();
	void logoloading();
	void mainMenu();
	void chooselevel(); 
	void credits();
	void game();
	void renderingthread();
public:
	Game();
	~Game();
};

