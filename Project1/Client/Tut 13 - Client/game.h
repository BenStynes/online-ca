#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Client.h"
#include <iostream>
class game
{
public:

	game();
	~game();

	void run();
	std::string returnPos();
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupShapes();

	sf::RenderWindow m_window;
	bool m_exitgame;

	sf::CircleShape m_circle;
	Client myClient;
};

#endif // !GAME

