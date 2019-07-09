#include "unit.h"
#include "button.h"
#include "scene.h"
#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

//Добавляем изображения	
void menu(sf::Event event, sf::RenderWindow &window) {
	int result_game = NULL;
	button start_button("start.png", gameWidth >> 1, (gameHeight >> 2) * 3);
	button exit_button("exit.png", gameWidth - 25, 25);
	button fon("fon.jpg", gameWidth >> 1, gameHeight >> 1);
	sf::RenderWindow &windowN = window;
	while (window.isOpen())
	{


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(fon.sprite);
		window.draw(start_button.sprite);
		window.draw(exit_button.sprite);//выводим кнопку старта на экран
		window.display();
		cout << "rend!!!" << endl;
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if ((abs(event.mouseButton.x - start_button.x) <= (start_button.width / 2)) && (abs(event.mouseButton.y - start_button.y) <= (start_button.height / 2))) {
					cout << "click!!!" << endl;
					result_game = game_scene(event, windowN);

				}
				if ((abs(event.mouseButton.x - exit_button.x) <= (exit_button.width / 2)) && (abs(event.mouseButton.y - exit_button.y) <= (exit_button.height / 2))) {
					window.close();
				}
			}
		}

	}
}