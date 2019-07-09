#pragma once
#include <iostream>
#include "point.h"
#include "cmath"
//Абстрактный класс – Фигура
class shape {
public:
    // Как корень иерархии полиморфных классов
    // класс обязан иметь виртуальный деструктор
    virtual ~shape();

    // Центр фигуры
    virtual point centre() const = 0;
    // Площадь фигуры
    virtual double area() const = 0;
    //Периметр фигуры
    virtual double perimetr() const = 0;

    // Функция вывод в заданный поток os
    virtual void print(std::ostream& os) const = 0;
};

// Полиморфный оператор вывода
std::ostream & operator<<(std::ostream &os, const shape& s);
