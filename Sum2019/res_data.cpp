#include "res_data.h"

res_data::res_data(int count_ball, bool* end_game, bool* result_r, int64_t time)
{
	this->count_ball = count_ball;
	this->time = time;
	for (int i = 0; i < count_ball; i++) {
		this->end_game[i] = end_game[i];
		this->result_r[i] = result_r[i];
	}
}

res_data::~res_data()
{
}
