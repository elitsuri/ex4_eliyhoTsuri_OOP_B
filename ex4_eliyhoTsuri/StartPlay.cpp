#include "StartPlay.h"

StartPlay::StartPlay()
{
	m_vector_but.push_back(std::make_unique<StartButton>());
	m_vector_but.push_back(std::make_unique<HelpButton>());	
	m_vector_but.push_back(std::make_unique<ExitButton>()); 
	m_back.setTexture(*(Singleton::show().get_pic(0)));
	m_back.setTextureRect(sf::IntRect(0, 0, 900, 700));
}

void StartPlay::run(bool &exit_on)
{
	sf::RenderWindow window(sf::VideoMode(900, 700, 32), "Tetris", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(500, 100));
	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2f mouseCoords;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					exit_on = false;
					window.close();
					break;
				}
				case sf::Event::MouseButtonPressed: 
				{
					mouseCoords.x = (float)event.mouseButton.x;
					mouseCoords.y = (float)event.mouseButton.y;
					for (size_t i = 0; i < m_vector_but.size(); ++i)
						m_vector_but[i]->ClickOn(mouseCoords, window, exit_on);
				}
				case sf::Event::MouseMoved: 
				{
					mouseCoords = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
					for (size_t i = 0; i < m_vector_but.size(); ++i)
						m_vector_but[i]->moveOn(mouseCoords);
					break;
				}
				default:
					break;
			}
		}
		window.clear();
		window.draw(m_back);
		for (size_t i = 0; i < m_vector_but.size(); ++i)
			m_vector_but[i]->draw(window);
		window.display();
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			exit_on = false;
			window.close();
			break;
		}
	}
}

StartPlay::~StartPlay()
{
}