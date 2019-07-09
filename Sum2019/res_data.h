#pragma once

#include <cstdlib> 
#include <iostream>
#include <cstring>
#include <string.h>
#include <stdio.h>
class res_data
{
public:
	int count_ball;
	bool* end_game;
	bool* result_r;
	int64_t time;
	res_data(int count_ball, bool* end_game, bool* result_r, int64_t time);

	~res_data();
};

