#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "unit.h"

using namespace sf;
using namespace std;

class button :	public unit
{
public:
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������


	button(String File, float x, float y); // x,y - ���� ���� ���������� c������� �����������

	~button();
};

