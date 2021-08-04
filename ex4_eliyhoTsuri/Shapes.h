#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Shapes
{
public:
	Shapes() 
	{
		Texture *back = Singleton::show().get_pic(4);
		m_shapes.setTexture(*back);
	}
	void move(RenderWindow &window, int row, int col, int color)
	{
		m_shapes.setTextureRect(IntRect(color * 18, 0, 18, 18));
		m_shapes.setPosition((float)row * 18 + 315, (float)col * 18 + 1);
		m_shapes.move(28, 31);
		window.draw(m_shapes);
	}
	virtual void draw(RenderWindow &window, int color, int i, int j) = 0;
protected:
	Sprite m_pic;
	Sprite m_shapes;
};