#pragma once
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <list>
#include <time.h>
#include "Singleton.h"
#include "windows.h"
#include "GameTime.h"
#include "Shapes.h"

struct Point
{
	int x, y;
};

const int M = 20;
const int N = 10;
using namespace sf;
using std::make_shared;
using std::shared_ptr;
using namespace std;

class Controller
{
public:
	Controller();
	void run();
	~Controller() {};
private:
	void set_game();
	void set_shapes();
	void set_new_level(RenderWindow & window);
	void initialize_level();
	void move();
	void move_rotate();
	void check_tick(int timer, int delay);
	bool check_board();
	void update_board();
	void check_lines(RenderWindow &window);
	void draw(RenderWindow &window, GameTime &menu);
	void game_over(RenderWindow & window);
	vector <shared_ptr <Shapes>> m_shapes;

	bool m_end = false;
	vector <double> m_speeds;
	Sprite m_back;
	Music m_music;
	Music m_music_line;
	int m_colorNum = 1;
	double m_speed = 0.9;
	float timer = 0;
	int m_level = 1;
	int m_points = 0;
	float m_dx = 0;
	bool m_flag = true;
	bool m_rotate = false;
	int figures[7][4] =
	{
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};
	vector<Point> m_a;
	vector<Point> m_b;
	vector<vector<int>> m_mat;
}; 
class Dest
{
	vector<Point> m_point;
public:
	Dest(vector<Point>point, float dx, bool flag)
	{
		m_point = point;
		for (int i = 0; i < 4; ++i)
		{
			if (!flag)
				m_point[i].y += 1;
			else
				m_point[i].x += (int)dx;
		}
	}
	vector<Point> operator()(double len)
	{
		return vector<Point>(m_point);
	}
};

sf::VideoMode operator/(const sf::VideoMode& mode, unsigned denom);
