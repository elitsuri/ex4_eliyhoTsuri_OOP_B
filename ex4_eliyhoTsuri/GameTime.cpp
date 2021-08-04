#include "GameTime.h"


GameTime::GameTime(int level,int points)
{
	m_level = level;
	m_points = points;
	m_font.loadFromFile("fonts/FONT.ttf");
	t_font.loadFromFile("fonts/crackman.ttf");
	setToolBar(); 
	setPositionTool();
}

void GameTime::setToolBar()
{
	m_points_text.setFont(m_font);
	m_level_text.setFont(m_font);
	m_num_points.setFont(t_font);
	m_num_level.setFont(t_font);
	m_points_text.setString("SCORE");
	m_level_text.setString("LEVEL");
	m_points_text.setCharacterSize(40);
	m_num_level.setCharacterSize(45);
	m_level_text.setCharacterSize(40);
	m_num_points.setCharacterSize(45);
	m_num_points.setStyle(sf::Text::Bold);
	m_points_text.setStyle(sf::Text::Bold);
	m_level_text.setStyle(sf::Text::Bold);
	m_num_level.setStyle(sf::Text::Bold);
	m_points_text.setFillColor(sf::Color::Red);
	m_level_text.setFillColor(sf::Color::Yellow);
	m_num_points.setFillColor(sf::Color::Red);
	m_num_level.setFillColor(sf::Color::Yellow);
	m_num_points.setString(std::to_string(m_points));
	m_num_level.setString(std::to_string(m_level));
}

void GameTime::setPositionTool()
{
	m_level_text.setPosition(85, 60);
	m_num_level.setPosition(165, 130);
	m_points_text.setPosition(605, 60);
	m_num_points.setPosition(675, 130);
}

void GameTime::set_speed(float new_speed)
{
	setToolBar();
	setPositionTool();
}

void GameTime::set_lives(int new_lives)
{
	setToolBar();
	setPositionTool();
}

void GameTime::set_points(int new_points)
{
	m_points = new_points;
	setToolBar();
	setPositionTool();
}

void GameTime::draw(sf::RenderWindow & window)
{
	window.draw(m_level_text);
	window.draw(m_points_text);
	window.draw(m_num_level);
	window.draw(m_num_points);
}