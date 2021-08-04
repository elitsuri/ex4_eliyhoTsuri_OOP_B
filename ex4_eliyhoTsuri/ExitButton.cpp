#include "ExitButton.h"

ExitButton::ExitButton()
{
	m_sprite.setTexture(*m_text); 
	m_sprite.setTextureRect(sf::IntRect(317,507, 300, 75));
	m_sprite.setPosition(300, 530);
	m_sprite.setColor(sf::Color(sf::Color::Cyan));
	m_button_on.setTexture(*m_text); 
	m_button_on.setTextureRect(sf::IntRect(322,585, 300, 75));
	m_button_on.setPosition(300,530);
	m_button_before = m_sprite;
}

void ExitButton::ClickOn(sf::Vector2f pos,sf::RenderWindow & window,bool & exit_on)
{
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;
	exit_on = false; 
	window.close();
}


void ExitButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on; 
	else
		m_sprite = m_button_before;
}


void ExitButton::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

ExitButton::~ExitButton()
{}