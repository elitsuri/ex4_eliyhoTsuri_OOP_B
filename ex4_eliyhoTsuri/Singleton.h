#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Singleton
{
public:
	static Singleton& show()
	{
		static Singleton noun;
		return noun;
	};
	sf::Texture *get_pic(int pic_num) { return &pic_arr[pic_num]; }
	~Singleton() {};
private:
	Singleton()
	{
		pic_arr[0].loadFromFile("pics/back.jpg");
		pic_arr[1].loadFromFile("pics/t.jpg");
		pic_arr[2].loadFromFile("pics/game_over.jpg");
		pic_arr[3].loadFromFile("pics/menu_bottons.png");
		pic_arr[4].loadFromFile("pics/tiles.png");
		pic_arr[5].loadFromFile("pics/winner.jpg");
		pic_arr[6].loadFromFile("pics/help.png");

		for (int i = 0; i < 5; ++i)
			pic_arr[i].setSmooth(true);
	};
	Singleton(const Singleton&) = delete;
	Singleton &operator=(const Singleton&) = delete;
	sf::Texture pic_arr[100];
};