#define _CRT_SECURE_NO_WARNINGS
//#include <map>
#include <assert.h>
#include <cstdlib> // 
#include <ctime> // ��� ������� time()
#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <dos.h>


#include <SFML/Graphics.hpp>

#include <tobii/tobii.h>
#include <tobii/tobii_streams.h>
#include <tobii/tobii_wearable.h>
#include <tobii/tobii_engine.h>

#include "unit.h"
#include "button.h"
#include "scene.h"
//#include "res_data.h"

using namespace std;
using namespace sf;

bool btrue(bool * r, int n){
		for (int i = 0; i < n; i++)
		{
			if (r[i] != true)
				return false;
		}
		return true;
}
bool left_eye_b = false;
bool right_eye_b = false;

float* coordinate = new float[2];
float* left_eye_c = new float[3];
float* right_eye_c = new float[3];

int64_t timer;

bool tmf(bool* r, int n) {
	int f = 0;
	int t = 0;
	for (int i = 0; i < n; i++)
	{
		if (r[i] == true) t += 1;
		else f += 1;
	}
	return t>f;
}

void reloader(bool* r,int n ,bool new_bool) {
	for (int i=0; i <n-1)
}

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void gaze_point_callback(tobii_gaze_point_t const* gaze_point, void* user_data)
{
	if (gaze_point->validity == TOBII_VALIDITY_VALID) {
		timer = gaze_point->timestamp_us;
		coordinate[0] = gaze_point->position_xy[0];
		coordinate[1] = gaze_point->position_xy[1];
	}
	else {
		timer = 0;
		coordinate[0] = 0;
		coordinate[1] = 0;
	}

} 

void eye_position_callback(tobii_eye_position_normalized_t const* eye_pos, void* user_data)
{
	if (eye_pos->left_validity == TOBII_VALIDITY_VALID)
	{
		
		left_eye_c[0] = eye_pos->left_xyz[0];
		left_eye_c[1] = eye_pos->left_xyz[1];
		left_eye_c[2] = eye_pos->left_xyz[2];
		left_eye_b = true;
	}
	else 		
	{
			left_eye_c[0] = 0;
			left_eye_c[1] = 0;
			left_eye_c[2] = 0;
			left_eye_b = false;
	}
	if (eye_pos->right_validity == TOBII_VALIDITY_VALID)
	{
		right_eye_c[0] = eye_pos->right_xyz[0];
		right_eye_c[1] = eye_pos->right_xyz[1];
		right_eye_c[2] = eye_pos->right_xyz[2];
		right_eye_b = true;
	}
	else
	{
		right_eye_c[0] = 0;
		right_eye_c[1] = 0;
		right_eye_c[2] = 0;
		right_eye_b = false;
	}
	
}

static void url_receiver(char const* url, void* user_data)
{
	char* buffer = (char*)user_data;
	if (*buffer != '\0') return; // only keep first value
	if (strlen(url) < 256)
		strcpy(buffer, url);
}

int game_scene(sf::Event event, sf::RenderWindow& window)
{
	// connect device
	tobii_api_t* api;

	tobii_error_t error = tobii_api_create(&api, NULL, NULL);
	assert(error == TOBII_ERROR_NO_ERROR);
	char url[256] = { 0 };

	error = tobii_enumerate_local_device_urls(api, url_receiver, url);
	assert(error == TOBII_ERROR_NO_ERROR && *url != '\0');

	tobii_device_t* device;
	error = tobii_device_create(api, url, &device);
	assert(error == TOBII_ERROR_NO_ERROR);

	error = tobii_gaze_point_subscribe(device, gaze_point_callback, 0);
	assert(error == TOBII_ERROR_NO_ERROR);

	error = tobii_eye_position_normalized_subscribe(device, eye_position_callback, 0);
	assert(error == TOBII_ERROR_NO_ERROR);

	cout << "All good!!!" << endl;

	// START Code game //


	int count_ball = 4; // КОЛВО ИГР 
	int count_game = 5; // КОЛВО ИГР 

	int* first_n = new int[count_ball]; // число1 для задания 
	int* second_n = new int[count_ball];	// число2 для задания 
	int64_t* start = new int64_t[count_ball];
	int64_t* end = new int64_t[count_ball];
	// хранит значения время начала зрительного контакта на круг
	String* string = new String[count_ball];	// хранит текст задания
	bool* result_p = new bool[count_ball];	// итоговый результат игры
	bool* answer_r = new bool[count_ball];	// ответ на кругу верный/ложь
	bool* answer_n = new bool[count_ball];	// ответ для это задания вообще существует(с генирирован)
	bool* flag_game_wait_mouse = new bool[count_ball]; // ждем реакции с мышкой
	bool* end_game = new bool[count_ball]; // завершение игры с опред кругом
	bool gaze[10] = { false };
	//float* leftd = new float[10];
	//float* rightd = new float[10];




	const int eps = 20;



	CircleShape kursor(2);
	kursor.setFillColor(sf::Color(0x00, 0x00, 0xff));
	kursor.setPosition(0, 0);
	//int game_n = 0;
	int start_time;
	sf::Time t1 = sf::microseconds(5000000);

	sf::RenderWindow& windowN = window;

	button exit_button("exit.png", gameWidth - 25, 25);

	CircleShape* circle_game = new CircleShape[count_ball];

	sf::Text* answer = new Text[count_ball];

	sf::CircleShape left_eye(20);
	left_eye.setFillColor(sf::Color(0xff, 0xff, 0xff));
	left_eye.setPosition(0, 560);

	sf::CircleShape right_eye(20);
	right_eye.setFillColor(sf::Color(0xff, 0xff, 0xff));
	right_eye.setPosition(40, 560);

	sf::Font font;
	font.loadFromFile("resources/font/arial.ttf");

	sf::Text* text = new Text[count_ball];

	for (int g = 0; g  <count_game; g++){
	start_time = clock();
	bool game_end = false;

	for (int i = 0; i < count_ball; ++i) {
		start[i] = 0;
		end[i] = 0;
		first_n[i] = 0;
		second_n[i] = 0;
		string[i] = "";
		result_p[i] = false;
		answer_r[i] = false;
		flag_game_wait_mouse[i] = false;
		answer_n[i] = false;
		end_game[i] = false;
		cout << "FATAl!!!!!!!!!!!!!" << endl;
	}

	bool flag_game = true;

	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < count_ball; ++i) {
		circle_game[i].setRadius(60);
		circle_game[i].setFillColor(sf::Color(0xff, 0xff, 0xff));
		circle_game[i].setPosition(getRandomNumber(150 * i + 40, 150 * (i + 1) - 40), getRandomNumber(0, 440));
	}


	for (int i = 0; i < count_ball; ++i) {
		answer[i].setFont(font);
		answer[i].setCharacterSize(24);
		answer[i].setFillColor(sf::Color::Red);
		answer[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
		answer[i].setPosition(circle_game[i].getPosition().x + circle_game[i].getRadius() / 2 + 20, circle_game[i].getPosition().y + circle_game[i].getRadius() / 2 + 20);
		answer[i].setString("");
	}

	for (int i = 0; i < count_ball; ++i) {
		text[i].setFont(font);
		text[i].setCharacterSize(24);
		text[i].setFillColor(sf::Color::Green);
		text[i].setStyle(sf::Text::Bold | sf::Text::Underlined);
		text[i].setPosition(circle_game[i].getPosition().x - circle_game[i].getRadius() / 2, circle_game[i].getPosition().y + 2 * circle_game[i].getRadius() + 5);
		text[i].setString("");
	}
	srand(static_cast<unsigned int>(time(0)));
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
					if ((abs(event.mouseButton.x - exit_button.x) <= (exit_button.width / 2)) && (abs(event.mouseButton.y - exit_button.y) <= (exit_button.height / 2))) {
						window.close();
					}
				}
			}
		}


		window.clear();
		
		for (int i = 0; i < count_ball; i++) {
			window.draw(circle_game[i]);

			window.draw(text[i]);
			window.draw(answer[i]);
		}
		window.draw(kursor);
		window.draw(left_eye);
		window.draw(right_eye);
		window.draw(exit_button.sprite);
		window.display();
		error = tobii_wait_for_callbacks(NULL, 1, &device);
		assert(error == TOBII_ERROR_NO_ERROR || error == TOBII_ERROR_TIMED_OUT);
		error = tobii_device_process_callbacks(device);
		assert(error == TOBII_ERROR_NO_ERROR);
		cout << timer << endl;
		kursor.setPosition(coordinate[0] * gameHeight, coordinate[1] * gameWidth);

		if (left_eye_b)
			left_eye.setFillColor(sf::Color(0x00, 0xff, 0x00));
		else
			left_eye.setFillColor(sf::Color(0xff, 0x00, 0x00));
		if (right_eye_b)
			right_eye.setFillColor(sf::Color(0x00, 0xff, 0x00));
		else
			right_eye.setFillColor(sf::Color(0xff, 0x00, 0x00));


		for (int i = 0; i < count_ball; i++) {
			if (!end_game[i]) {
				if (
					circle_game[i].getPosition().x - eps < coordinate[0] * gameHeight
					&& circle_game[i].getPosition().y - eps < coordinate[1] * gameWidth
					&& coordinate[0] * gameHeight < circle_game[i].getPosition().x + 2 * circle_game[i].getRadius() + eps
					&& coordinate[1] * gameWidth < circle_game[i].getPosition().y + 2 * circle_game[i].getRadius() + eps
					&& (left_eye_b || right_eye_b)
					&& !flag_game_wait_mouse[i])
				{
					if (!start[i]) start[i] = timer;
					end[i] = 0;
					circle_game[i].setFillColor(sf::Color(0xff, 0xff, 0x00));
				}
				else {
					start[i] = 0;
					if (!end[i]) end[i] = timer;
					circle_game[i].setFillColor(sf::Color(0xff, 0xff, 0xff));
				}
			}
		}

		for (int i = 0; i < count_ball; i++) {
			if (flag_game && (left_eye_b || right_eye_b)) {
				first_n[i] = getRandomNumber(1, 200);
				second_n[i] = getRandomNumber(1, 200);
				string[i] = to_string(first_n[i]);
				string[i] += " - ";
				string[i] += to_string(second_n[i]);
				string[i] += " = ?";
				text[i].setString(string[i]);
			}
		}
		if (string[0] != "") flag_game = false;

		for (int i = 0; i < count_ball; i++) {
			if (!end_game[i]) {
				if (abs(timer - start[i]) > 500000 && start[i] && !answer_n[i]) {
					int change = getRandomNumber(0, 1);
					if (change) {
						answer[i].setString(to_string(first_n[i] - second_n[i]));
						answer_r[i] = true;
						answer_n[i] = true;
						cout << answer_r[i] << endl;
						//system("pause");
					}
					else {
						int der = getRandomNumber(-100, 100);
						while (!der) der = getRandomNumber(-100, 100); // исключаем 0				
						answer[i].setString(to_string(first_n[i] - second_n[i] + der));
						answer_r[i] = false;
						answer_n[i] = true;
						cout << answer_r[i] << endl;

					}

					flag_game_wait_mouse[i] = true;
				}
			}
		}

		for (int i = 0; i < count_ball; i++) {
			if (!end_game[i]) {
				if (abs(timer - end[i]) > 1500000 && end[i] && answer_n[i]) {
					answer[i].setString("");
					answer_n[i] = false;
					flag_game_wait_mouse[i] = false;
				}
			}
		}


		for (int i = 0; i < count_ball; i++) {
			if (!end_game[i]) {
				if (flag_game_wait_mouse[i]) {
					cout << "MOUSE" << endl;
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
						if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && answer_r[i]) || (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !answer_r[i])) {
							circle_game[i].setFillColor(sf::Color(0x00, 0x00, 0xff));
							result_p[i] = 1;
							end_game[i] = true;

						}
						else {
							circle_game[i].setFillColor(sf::Color(0xff, 0x00, 0x00));
							result_p[i] = 0;
							end_game[i] = true;

						}
					}
				}
			}
		}

		if (btrue(end_game, count_ball) || clock() - start_time > 60 * 1000) {
			game_end = true;
		}
		if (game_end) break;
	}
}
	// END Code game //
	error = tobii_eye_position_normalized_unsubscribe(device);
	assert(error == TOBII_ERROR_NO_ERROR);
	error = tobii_gaze_point_unsubscribe(device);
	assert(error == TOBII_ERROR_NO_ERROR);
	error = tobii_device_destroy(device);
	assert(error == TOBII_ERROR_NO_ERROR);
	error = tobii_api_destroy(api);
	assert(error == TOBII_ERROR_NO_ERROR);
	return 0;
}
	
