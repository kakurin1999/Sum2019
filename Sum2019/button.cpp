#include "button.h"
#include <SFML/Graphics.hpp>


button::button(String File, float x, float y)
{
	image.loadFromFile("resources/image/" + File);//загружаем в изображение файл	
	texture.loadFromImage(image);//передаем в текстуру объект Image (изображения)
	sprite.setTexture(texture);
	sprite.setPosition(x-image.getSize().x/2 , y-image.getSize().y/2);
	this->width = image.getSize().x;
	this->height = image.getSize().y;
	this->x = x;
	this->y = y;
}

button::~button()
{
	sprite.~Sprite();	
}
