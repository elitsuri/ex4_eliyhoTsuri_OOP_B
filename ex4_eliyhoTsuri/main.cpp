#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else		
#error "Unrecognized configuration!"
#endif
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "StartPlay.h"


int main()
{
	StartPlay start_play;
	bool exit_on = true;

	while (exit_on)
		start_play.run(exit_on);

	return (EXIT_SUCCESS);
	
	return 0;
}