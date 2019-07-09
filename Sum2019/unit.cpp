#include "unit.h"
#include <iostream>
using namespace std;
unit::unit()
{
	this->width = 0.0f;
	this->height = 0.0f;
	this->x = 0.0f;
	this->y = 0.0f;

}

unit::unit(float w, float h, float x , float y)
{	


	this->width = w;
	this->height = h;
	this->x = x;
	this->y = y;
	
}


float unit::get_x()
{
	return x;
}

float unit::get_y()
{
	return y;
}

void unit::set_x(float new_x)
{
	x = new_x;
}

void unit::set_y(float new_y)
{
	y = new_y;
}

unit::~unit()
{
}
