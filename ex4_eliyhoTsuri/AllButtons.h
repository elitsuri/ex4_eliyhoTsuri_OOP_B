#pragma once
#include <SFML\Graphics.hpp>
#include "Singleton.h"

class AllButtons
{
public:
	AllButtons() { m_text = Singleton::show().get_pic(3); }
	virtual void ClickOn(sf::Vector2f pos, sf::RenderWindow &window, bool & exit_on) = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual sf::Sprite getSprite() = 0;
	virtual void moveOn(sf::Vector2f pos) = 0;
	virtual ~AllButtons() {};
protected:
	sf::Texture *m_text;
	sf::Sprite m_sprite;
	sf::Sprite m_button_on;
	sf::Sprite m_button_before;
};