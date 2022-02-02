#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Client.h"
#include <iostream>
#include <sstream>
#include "PacketStructs.h"
class game
{
public:

	game();
	~game();

	void run();
	void returnPos();
	void returnPos2();
	void returnY1();
	void returnY2();
	std::vector<std::string> splitString(const std::string& s, char delimiter);
	
private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupShapes();
	bool gameOver = false;
	sf::Clock timer;
	sf::RenderWindow m_window;
	bool m_exitgame;
	bool start = false;
	std::vector<std::string> data;
	sf::CircleShape m_circle;
	sf::CircleShape m_circle2;
	std::string uqholder;
	Client myClient;
	int identity;
	sf::Text goodMorning;
	sf::Font evening;
};

#endif // !GAME

