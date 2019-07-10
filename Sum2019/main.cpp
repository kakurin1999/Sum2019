#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <ctime>


#include <iostream>
//#include <time.h>
#include "scene.h"
#include "button.h"
#include "unit.h"
using namespace sf;
using namespace std;




int main() {
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Summer2019",
		sf::Style::Fullscreen | sf::Style::Close);

	//std::srand(static_cast<unsigned int>(std::time(NULL)));
	Clock clock;

	window.setVerticalSyncEnabled(true);

	

	while (window.isOpen())
	{	
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sf::RenderWindow &windowN = window;
		menu(event, windowN);
	}
	return 0;
}
