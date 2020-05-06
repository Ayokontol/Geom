#pragma once
#include <vector>

void make_test(std::vector<geom::point>& T, size_t M = 2, size_t N = -1);
bool test(std::vector<geom::point>& T, size_t M, std::vector<int>& Ans);
void input_test(std::vector<geom::point>& T, size_t& M, size_t& N);