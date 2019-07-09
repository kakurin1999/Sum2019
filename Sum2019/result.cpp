

#include <cstdlib> // 
 // ��� ������� time()
#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>

#include <dos.h>

#include <SFML/Graphics.hpp>


#include "unit.h"
#include "button.h"
#include "scene.h"

using namespace std;
using namespace sf;

string BTS(bool res) {
	if (res)
		return "YES";
	else return "NO";
}
	
void result(sf::Event event, sf::RenderWindow& window, int count, bool* result_p, bool* end_game, int64_t time_game) {
	  
	sf::RenderWindow& windowN = window;
	sf::Font font;
	font.loadFromFile("resources/font/arial.ttf");
	/*
	sf::Text ends;
	ends.setFont(font);
	ends.setCharacterSize(24);
	ends.setFillColor(sf::Color::White);
	ends.setStyle(sf::Text::Bold | sf::Text::Underlined);
	ends.setString("Complete task: ");
	ends.setPosition(0, 300);

	sf::Text* end_text = new Text[count];
	for (int i = 0; i < count; ++i) {
		end_text[i].setFont(font);
		end_text[i].setCharacterSize(24);
		end_text[i].setFillColor(sf::Color::White);
		end_text[i].setStyle(sf::Text::Bold);
		end_text[i].setString(BTS(end_game[i]));
		end_text[i].setPosition(200 + 60 * i, 300);
		cout << end_game[i] << endl;
	}

	sf::Text* res_text = new Text[count];
	for (int i = 0; i < count; ++i) {
		res_text[i].setFont(font);
		res_text[i].setCharacterSize(24);
		res_text[i].setFillColor(sf::Color::White);
		res_text[i].setStyle(sf::Text::Bold);
		if (end_game[i]) res_text[i].setString(BTS(result_p));
		res_text[i].setPosition(200 + 60*i,500);
	}

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//if ((abs(event.mouseButton.x - exit_button.x) <= (exit_button.width / 2)) && (abs(event.mouseButton.y - exit_button.y) <= (exit_button.height / 2))) {
					//	window.close();
					//}
				}
			}
		}
		window.clear();
		window.draw(ends);
		
		for (int i = 0; i< count; i++){
			window.draw(end_text[i]);
			window.draw(res_text[i]);

		}
		window.display();
	}
	*/
}