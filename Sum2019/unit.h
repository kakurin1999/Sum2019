#pragma once

class unit
{
public:
	float x, y, width, height; //координаты объекта х и у, высота ширина

	unit();
	unit(float w, float h, float x, float y);
	
	float get_x();
	float get_y();
	void set_x(float new_x);
	void set_y(float new_y);

	~unit();
};

