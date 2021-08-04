#include "StartButton.h"
#include "Controller.h"
StartButton::StartButton()
{
	
	m_sprite.setTexture(*m_text);
	m_sprite.setTextureRect(sf::IntRect(210,150,616,70));
	m_sprite.setPosition(200,350);
	m_button_on.setTexture(*m_text);
	m_button_on.setTextureRect(sf::IntRect(210, 234, 616, 75));
	m_button_on.setPosition(200, 350);
	m_button_before = m_sprite;
}
void StartButton::ClickOn(sf::Vector2f pos,sf::RenderWindow & window,bool & exit_on)
{
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;
	window.close();
	Controller game;
	game.run();
}

void StartButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on;
	else
		m_sprite = m_button_before;
}

void StartButton::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

StartButton::~StartButton()
{}