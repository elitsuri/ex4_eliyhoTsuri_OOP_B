#pragma once
#include "Shapes.h"
class T_Shape : public Shapes
{

public:
	T_Shape() {};
	virtual void draw(RenderWindow &window, int color, int i, int j)
	{
		m_pic = m_shapes;
		m_pic.setTextureRect(IntRect(color * 18, 0, 18, 18));
		m_pic.setPosition((float)j * 18 + 315, (float)i * 18 + 2);
		m_pic.move(28, 31);
		window.draw(m_pic);
	}
	~T_Shape() {};
};

