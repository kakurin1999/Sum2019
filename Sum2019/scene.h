#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib> // ��� ������� rand() � srand()
#include <ctime> 

const int gameWidth = 800;
const int gameHeight = 600;
const float pi = 3.14159f;



void menu(sf::Event event, sf::RenderWindow &window);
int game_scene(sf::Event event, sf::RenderWindow &window);
void result(sf::Event event, sf::RenderWindow& window,int count, bool* result_p, bool *end_game, int64_t time_game);
// ���������� ��������� ����� ����� ���������� min � max
// ��������������, ��� ������� srand() ��� ��������
