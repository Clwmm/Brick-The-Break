#include "Game.h"

bool Game::intersects(Entity* a, Entity* b)
{
	sf::Vector2f circleDistance;

	circleDistance.x = abs(a->x - b->x);
	circleDistance.y = abs(a->y - b->y);

	if (circleDistance.x > (b->sprite.getTexture()->getSize().x / 2 + a->r))
		return false;
	if (circleDistance.y > (b->sprite.getTexture()->getSize().y / 2 + a->r))
		return false;

	if (circleDistance.x <= (b->sprite.getTexture()->getSize().x / 2))
		return true;
	if (circleDistance.y <= (b->sprite.getTexture()->getSize().y / 2))
		return true;

	float cornerDistance_sq = (circleDistance.x - b->sprite.getTexture()->getSize().x / 2) * (circleDistance.x - b->sprite.getTexture()->getSize().x / 2) + (circleDistance.y - b->sprite.getTexture()->getSize().y / 2) * (circleDistance.y - b->sprite.getTexture()->getSize().y / 2);

	return (cornerDistance_sq <= (a->r * a->r));
}

void Game::colision(Entity* a, Entity* b)
{
	sf::Vector2f A, B, C, D;
	A.x = b->x - (b->width / 2);
	A.y = b->y - (b->height / 2);

	B.x = b->x + (b->width / 2);
	B.y = b->y - (b->height / 2);

	C.x = b->x - (b->width / 2);
	C.y = b->y + (b->height / 2);

	D.x = b->x + (b->width / 2);
	D.y = b->y + (b->height / 2);

	if (a->y >= C.y && a->x >= C.x && a->x <= D.x)
	{
		a->y = C.y + a->r;
		a->my = -a->my;
		return;
	}
	else if (a->y <= A.y && a->x >= A.x && a->x <= B.x)
	{
		a->y = A.y - a->r;
		a->my = -a->my;
		return;
	}
	else if (a->x <= A.x && a->y >= A.y && a->y <= C.y)
	{
		a->x = A.x - a->r;
		a->mx = -a->mx;
		return;
	}
	else if (a->x >= B.x && a->y >= B.y && a->y <= D.y)
	{
		a->x = B.x + a->r;
		a->mx = -a->mx;
		return;
	}
}

void Game::player_colision(Entity* a, Entity* b)
{
	sf::Vector2f A, B, C, D;
	A.x = b->x - (b->width / 2);
	A.y = b->y - (b->height / 2);

	B.x = b->x + (b->width / 2);
	B.y = b->y - (b->height / 2);

	C.x = b->x - (b->width / 2);
	C.y = b->y + (b->height / 2);

	D.x = b->x + (b->width / 2);
	D.y = b->y + (b->height / 2);

	if (a->y >= C.y && a->x >= C.x && a->x <= D.x)
	{
		a->y = C.y + a->r;
		a->my = -a->my;
		return;
	}
	else if (a->y <= A.y && a->x >= A.x && a->x <= B.x)
	{
		float half_width = b->width/2;
		float deltaX = b->x - a->x;



		float angle_multi = deltaX / half_width;
		float angle = 270 - (85 * angle_multi);

		a->uptade_angle(angle);
		a->y = A.y - a->r;
		return;
	}
	else if (a->x <= A.x && a->y >= A.y && a->y <= C.y)
	{
		a->x = A.x - a->r;
		a->mx = -a->mx;
		return;
	}
	else if (a->x >= B.x && a->y >= B.y && a->y <= D.y)
	{
		a->x = B.x + a->r;
		a->mx = -a->mx;
		return;
	}
}

void Game::start()
{
	while (window->isOpen())
	{
		switch (status)
		{
		case GameStatus::mainMenu:
			mainMenu();
			if (close)
				return;
			break;
		case GameStatus::chooselevel:
			chooselevel();
			break;
		case GameStatus::game:
			game();
			if (close)
				return;
			break;
		}
	}
}

void Game::mainMenu()
{
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window->getSize()));
	window->setView(view);
	sf::Text text[2];
	for (int i = 0; i < 2; i++)
	{
		text[i].setCharacterSize(102);
		text[i].setFont(*font);
		text[i].setFillColor(sf::Color(30, 133, 159));
		text[i].setPosition(view.getCenter().x - 51, view.getCenter().y + (i * 105) - 154);
	}
	text[0].setString("Play");
	text[1].setString("Exit");

	sf::Event evnt;

	while (window->isOpen())
	{
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				close = true;
				return;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Down)
					if (mmstatus == MainMenuStatus::play)
						mmstatus = MainMenuStatus::exit;
				if (evnt.key.code == sf::Keyboard::Up)
					if (mmstatus == MainMenuStatus::exit)
						mmstatus = MainMenuStatus::play;
				if (evnt.key.code == sf::Keyboard::Enter)
				{
					switch (mmstatus)
					{
					case MainMenuStatus::play:
						status = GameStatus::chooselevel;
						return;
					case MainMenuStatus::exit:
						close = true;
						return;
					}
				}
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					close = true;
					return;
				}
			}
		}

		switch (mmstatus)
		{
		case MainMenuStatus::play:
			text[0].setFillColor(sf::Color(30, 133, 159));
			text[1].setFillColor(sf::Color(0, 45, 69));
			break;
		case MainMenuStatus::exit:
			text[0].setFillColor(sf::Color(0, 45, 69));
			text[1].setFillColor(sf::Color(30, 133, 159));
			break;
		}

		window->clear();
		for (int i = 0; i < 2; i++)	window->draw(text[i]);
		window->display();
	}
}

void Game::chooselevel()
{
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(window->getSize()));
	window->setView(view);
	sf::Text text[9];
	for (int i = 0; i < 9; i++)
	{
		text[i].setCharacterSize(64);
		text[i].setFont(*font);
		text[i].setFillColor(sf::Color(30, 133, 159));
		text[i].setPosition(view.getCenter().x - 250, view.getCenter().y + (i * 64) - 300);
	}
	text[0].setString("Level 1");
	text[1].setString("Level 2");
	text[2].setString("Level 3");
	text[3].setString("Level 4");
	text[4].setString("Level 5");
	text[5].setString("Level 6");
	text[6].setString("Level 7");
	text[7].setString("Level 8");
	text[8].setString("Level 9");

	sf::Event evnt;

	while (window->isOpen())
	{
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				close = true;
				return;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Down)
					if (actual_level < 9)
						actual_level++;
				if (evnt.key.code == sf::Keyboard::Up)
					if (actual_level > 1)
						actual_level--;
				if (evnt.key.code == sf::Keyboard::Enter)
				{
					status = GameStatus::game;
					return;
				}
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					status = GameStatus::mainMenu;
					return;
				}
			}
		}

		text[actual_level - 1].setFillColor(sf::Color(30, 133, 159));
		for (int i = 0; i < 9; i++)
			if (i != actual_level - 1)
				text[i].setFillColor(sf::Color(0, 45, 69));

		window->clear();
		for (int i = 0; i < 9; i++)	window->draw(text[i]);
		window->display();
	}
}

void Game::game()
{	
	srand(static_cast<unsigned int>(time(0)));
	MapGenerator map(brcs, temp_entities, actual_level, wallbrics);
	
	p = new Player();

	Ball* b = new Ball();
	bals->push_back(b);

	sf::Event evnt;
	
	window->setActive(false);
	render = true;
	sf::Thread th(&Game::renderingthread, this);
	th.launch();

	deltatime = clock.restart().asSeconds();

	while (window->isOpen())
	{
		deltatime = clock.restart().asSeconds();

		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				render = false;
				th.wait();
				window->setActive(true);
				close = true;
				return;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
					if (status == GameStatus::game)
					{
						render = false;
						th.wait();
						window->setActive(true);

						delete p;

						for (auto i = bals->begin(); i != bals->end();)
						{
							Entity* e = *i;
							i = bals->erase(i);
							delete e;
						}
						bals->clear();

						for (auto i = brcs->begin(); i != brcs->end();)
						{
							Entity* e = *i;
							i = brcs->erase(i);
							delete e;
						}
						brcs->clear();

						for (auto i = pups->begin(); i != pups->end();)
						{
							Entity* e = *i;
							i = pups->erase(i);
							delete e;
						}
						pups->clear();

						for (auto i = temp_entities->begin(); i != temp_entities->end();)
						{
							Entity* e = *i;
							i = temp_entities->erase(i);
							delete e;
						}
						temp_entities->clear();

						endstatus = End::normal;
						status = GameStatus::chooselevel;
						return;
					}
			}
		}

		for (auto c : *bals)
		{
			for (auto v : *brcs)
			{
				if (intersects(c, v))
				{
					switch (v->name)
					{
					case EnName::box:
						if (v->life > 0)
						{
							if (c->strong > 0)
								c->strong--;
							else
								colision(c, v);
							v->life--;
						}
						break;
					case EnName::dwall:
						c->life = 0;
						break;
					case EnName::wall:
						colision(c, v);
						break;
					}
				}
			}
			if (intersects(c, p))
				player_colision(c, p);
		}
		for (auto c : *pups)
		{
			if (intersects(c, p) && c->life > 0)
			{
				c->life = 0;
				switch (c->type)
				{
				case PUType::dble:
					if (bals->size() < 50000)
					{
						for (auto i : *bals)
						{
							Ball* b = new Ball(i->x, i->y);
							temp_entities->push_back(b);
						}
					}
					break;
				case PUType::tri:
				{
					for (int i = 0; i < 3; i++)
					{
						Ball* b = new Ball(p->x, p->y - 22);
						temp_entities->push_back(b);
					}
					break;
				}
				case PUType::str:
					for (auto i : *bals)
						i->strong += 4;
					break;
				}
			}
		}

		if (brcs->size() - 184 - wallbrics <= 0)
			endstatus = End::win;
		if (bals->size() <= 0 && endstatus != End::win)
			endstatus = End::lose;

		p->update(deltatime);

		for (auto i = bals->begin(); i != bals->end();)
		{
			Entity* e = *i;

			e->update(deltatime);

			if (e->life <= 0)
			{
				i = bals->erase(i);
				delete e;
			}
			else i++;
		}

		for (auto i = brcs->begin(); i != brcs->end();)
		{
			Entity* e = *i;

			e->update(deltatime);

			if (e->life <= 0)
			{
				i = brcs->erase(i);
				delete e;
			}
			else i++;
		}

		for (auto i = pups->begin(); i != pups->end();)
		{
			Entity* e = *i;

			e->update(deltatime);

			if (e->life <= 0)
			{
				i = pups->erase(i);
				delete e;
			}
			else i++;
		}


		for (auto i = temp_entities->begin(); i != temp_entities->end();)
		{
			Entity* k = *i;
			switch (k->name)
			{
			case EnName::ball:
				bals->push_back(k);
				i = temp_entities->erase(i);
				break;
			case EnName::powerup:
				pups->push_back(k);
				i = temp_entities->erase(i);
				break;
			}
		}

	}
}

void Game::renderingthread()
{
	window->setActive(true);

	sf::Text text;
	text.setCharacterSize(32);
	text.setFont(*font);
	text.setFillColor(sf::Color(30, 133, 159));
	text.setPosition(-250, 404);

	/*sf::Vertex line[2] =
	{
		sf::Vertex(sf::Vector2f(-336, -416)),
		sf::Vertex(sf::Vector2f(336, 416))
	};*/

	while (render && window->isOpen())
	{
		rend_bals = *bals;
		window->clear(sf::Color(23, 24, 69));
		for (auto i : *brcs)
			if (i != nullptr && i->life > 0)
				i->draw(*window);
		for (auto i : rend_bals)
			if (i != nullptr && i->life > 0)
				i->draw(*window);
		for (auto i : *pups)
			if (i != nullptr && i->life > 0)
				i->draw(*window);
		p->draw(*window);

		//window->draw(line, 2, sf::Lines);

		text.setCharacterSize(32);
		text.setPosition(-290, -460);
		text.setString("Movement:  <-  ->     Back: ESC");
		window->draw(text);
		text.setPosition(-290, 404);
		text.setString("Brics: " + std::to_string(brcs->size() - 184 - wallbrics));
		window->draw(text);
		text.setPosition(-150, 404);
		text.setString("Balls: " + std::to_string(bals->size()));
		window->draw(text);
		text.setPosition(-10, 404);
		text.setString("Level: " + std::to_string(actual_level));
		window->draw(text);
		text.setPosition(130, 404);
		text.setString("FPS: " + std::to_string(static_cast<int>(1/deltatime)));
		window->draw(text);

		if (endstatus != End::normal)
		{
			switch (endstatus)
			{
			case End::win:
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(102);
				text.setPosition(-108, -98);
				text.setString("You Win");
				window->draw(text);
				text.setFillColor(sf::Color(30, 133, 159));
				text.setCharacterSize(102);
				text.setPosition(-112, -102);
				text.setString("You Win");
				window->draw(text);
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(32);
				text.setPosition(-110, 2);
				text.setString("Press ESC to go back");
				window->draw(text);
				text.setFillColor(sf::Color(30, 133, 159));
				text.setCharacterSize(32);
				text.setPosition(-112, 0);
				text.setString("Press ESC to go back");
				window->draw(text);
				break;
			case End::lose:
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(102);
				text.setPosition(-128, -98);
				text.setString("You Lose");
				window->draw(text);
				text.setFillColor(sf::Color(30, 133, 159));
				text.setCharacterSize(102);
				text.setPosition(-132, -102);
				text.setString("You Lose");
				window->draw(text);
				text.setFillColor(sf::Color::Black);
				text.setCharacterSize(32);
				text.setPosition(-110, 2);
				text.setString("Press ESC to go back");
				window->draw(text);
				text.setFillColor(sf::Color(30, 133, 159));
				text.setCharacterSize(32);
				text.setPosition(-112, 0);
				text.setString("Press ESC to go back");
				window->draw(text);
				break;
			}
		}

		window->display();
	} 
}

Game::Game(sf::RenderWindow& _window)
{
	window = &_window;

	if (!font->loadFromFile("res/notalot35.ttf"))
		close = true;
}
