#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "unit.h"

using namespace sf;
using namespace std;

class button :	public unit
{
public:
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт


	button(String File, float x, float y); // x,y - куда надо установить cередину изображения

	~button();
};

