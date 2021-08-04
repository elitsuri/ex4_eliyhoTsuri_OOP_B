#pragma once
#include "AllButtons.h"
#include "StartButton.h"
#include "HelpButton.h"
#include "ExitButton.h"
#include <memory>
class StartPlay
{
public:
	StartPlay();
	void run(bool &exit_on);
	~StartPlay();
private:
	std::vector <std::unique_ptr<AllButtons>> m_vector_but;
	bool m_startPlay;
	sf::Font m_font;

	sf::Sprite m_back;
};
sf::VideoMode operator/(const sf::VideoMode& mode, unsigned denom);
