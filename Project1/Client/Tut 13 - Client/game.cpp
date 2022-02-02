#include "game.h"

game::game() :
	m_window{ sf::VideoMode{ 1800u, 1200u, 32u }, "Basic game" },
	m_exitgame{ false },myClient("149.153.106.176", 1111)
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		throw std::exception("YOU DONE GOOFED");
	}


	setupShapes();
	timer.restart();
	
	
}

game::~game()
{

}

void game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

void game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}

		if (sf::Event::KeyPressed == nextEvent.type)
		{
			if (!gameOver)
			{
				if (nextEvent.key.code == sf::Keyboard::Left)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x - 10, m_circle.getPosition().y);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x - 10, m_circle2.getPosition().y);
					}
				}
				if (nextEvent.key.code == sf::Keyboard::Right)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x + 10, m_circle.getPosition().y);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x + 10, m_circle2.getPosition().y);
					}
				}
				if (nextEvent.key.code == sf::Keyboard::Down)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x, m_circle.getPosition().y + 10);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x, m_circle2.getPosition().y + 10);
					}
				}
				if (nextEvent.key.code == sf::Keyboard::Up)
				{
					if (myClient.Identify == "0")
					{
						m_circle.setPosition(m_circle.getPosition().x, m_circle.getPosition().y - 10);
					}
					if (myClient.Identify == "1")
					{
						m_circle2.setPosition(m_circle2.getPosition().x, m_circle2.getPosition().y - 10);
					}
				}


			}
		}
	}
}

void game::update(sf::Time t_deltaTime)
{
	if (m_exitgame)
	{
		m_window.close();
	}
	if (myClient.Identify == "0")
	{
		
		returnPos();
	}
	else
	{
		returnPos2();
		
	}
    uqholder = myClient.holder;
	data = splitString(uqholder,',');
	
	for (std::string a : data)
	{
		std::cout << a << std::endl ;
	}
	



		if (myClient.Identify == "1")
		{
			m_circle.setPosition(std::stof(data.at(0)), std::stof(data.at(1)));
		}
		else
		{
			m_circle2.setPosition(std::stof(data.at(0)), std::stof(data.at(1)));

		}
	
	if (!gameOver && m_circle.getGlobalBounds().intersects(m_circle2.getGlobalBounds()))
	{
		gameOver = true;
		goodMorning.setString("Yellow Lost got tagged rip ");

	}
	if (gameOver)
	{
		goodMorning.setPosition(700, 600);

	}
}

void game::render()
{
	m_window.clear();

	m_window.draw(m_circle);
	m_window.draw(m_circle2);
	if (gameOver)
	{
		m_window.draw(goodMorning);
	}
	m_window.display();
}

void game::setupShapes()
{
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setRadius(30.0f);
	m_circle.setPosition(1000, 400.0f);

	m_circle2.setFillColor(sf::Color::Yellow);
	m_circle2.setRadius(30.0f);
	m_circle2.setPosition(400.0f, 400.0f);
	
	evening.loadFromFile("C:/Windows/Fonts/comic.ttf");
	goodMorning.setFont(evening);
	goodMorning.setCharacterSize(44);
	goodMorning.setFillColor(sf::Color::Yellow);

}

void game::returnPos()
{
	std::string s;
	if (start == false)
	{
		returnY1();
		start = true;
	}
	else
	{
		s += std::to_string(static_cast<int>(m_circle.getPosition().x));
		s += ",";
		s += std::to_string(static_cast<int>(m_circle.getPosition().y));

		myClient.SendString(s);
	}
}
void game::returnPos2()
{
	std::string s;
	if (start == false)
	{
		returnY2();
		start = true;
	}
	else
	{
		s += std::to_string(static_cast<int>(m_circle2.getPosition().x));
		s += ",";
		s += std::to_string(static_cast<int>(m_circle2.getPosition().y));

		myClient.SendString(s);
	}
}
void game::returnY1()
{

	std::string s;

	s += "1000";
	s += ",";
	s += "400";

	myClient.SendString(s);
}
void game::returnY2()
{

	std::string s;

	s += "400";
	s += ",";
	s += "400";

	myClient.SendString(s);
}
std::vector<std::string> game::splitString(const std::string& s, char delimiter)
{
	std::vector<std::string> splits;
	std::string split;
	std::istringstream ss(s);
	while (std::getline(ss, split, delimiter))
	{
		splits.push_back(split);
	}
	return splits;
}