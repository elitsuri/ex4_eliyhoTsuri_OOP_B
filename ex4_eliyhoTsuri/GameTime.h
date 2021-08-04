#pragma once
#include <SFML\Graphics.hpp>

class GameTime
{
public:
	GameTime(int level,int points);
	void setToolBar();
	void setPositionTool();
	void set_speed(float new_speed);
	void set_lives(int new_lives);
	void set_points(int new_points);
	void draw(sf::RenderWindow &window);
	~GameTime() {};
private:
	sf::Font m_font;
	sf::Font t_font;
	sf::Text m_level_text;
	sf::Text m_points_text;
	sf::Text m_num_level;
	sf::Text m_num_points;
	int m_level = 1;
	int m_points = 0;
};