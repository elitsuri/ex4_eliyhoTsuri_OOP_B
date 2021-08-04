#pragma once
#include "AllButtons.h"
class HelpButton :public AllButtons
{
public:
	HelpButton();
	virtual void ClickOn(sf::Vector2f pos, sf::RenderWindow &window, bool & exit_on);
	virtual sf::Sprite getSprite() { return m_sprite; };
	virtual void moveOn(sf::Vector2f pos);
	virtual void draw(sf::RenderWindow & window);
	~HelpButton();
private:
	bool m_button_help;
};