#pragma once
#include <algorithm>
#include <iostream>
#include <ctime>
#include "geom.hpp"
#include "test.hpp"

void make_test(std::vector<geom::point>& T, size_t M, size_t N) {
    std::srand(unsigned(std::time(0)));
    if (N == -1)
        N = rand() % 10000 + 1;
    T.resize(0);
    size_t CN;
    for (size_t k = 0; k < M; ++k) {
        if (k == M - 1)
            CN = N;
        else
            CN = rand() % N + 1;
        N -= CN;
        geom::point pnt(rand() % 200000 - 100000, rand() % 200000 - 100000);
        double r = rand() % 100000;
        for (size_t i = 0; i < CN; ++i) {
            double angle = rand() * 1.0 / RAND_MAX * 1.5;
            double x = 2 * (rand() % 2 * 1.0 - 0.5) * cos(angle) * r + pnt.x;
            double y = 2 * (rand() % 2 * 1.0 - 0.5) * sin(angle) * r + pnt.y;
            bool flag = true;
            for (size_t j = 0; j < T.size(); ++j)
                if (abs(T[j].x - x) < 0.00001 && abs(T[j].y - y) < 0.00001)
                    flag = false;
            if (abs(details::dist(geom::point(x, y), pnt) - r) >= 0.0000001)
                flag = false;
            if (flag)
                T.push_back(geom::point(x, y));
            else
                i--;
        }
    }

    std::random_shuffle(T.begin(), T.end());
}

bool test(std::vector<geom::point>& T, size_t M, std::vector<int>& Ans) {
    size_t N = Ans.size();
    if (Ans.size() != T.size())
        return false;
    std::vector<std::vector<size_t>> Index(M);
    for (size_t i = 0; i < N; ++i) {
        Index[Ans[i] - 1].push_back(i);
    }

    for (size_t k = 0; k < M; ++k) {
        if (Index[k].size() <= 3)
            continue;
        geom::point a, b, c;
        a = T[Index[k].back()];
        Index[k].pop_back();
        b = T[Index[k].back()];
        Index[k].pop_back();
        c = T[Index[k].back()];
        Index[k].pop_back();
        details::circle crcl(a, b, c);
        for (auto i : Index[k]) {
            double q = abs(details::dist(T[i], crcl.pnt) - crcl.r);
            if (q >= 0.00001)
                return false;
        }
    }
    return true;
}

void input_test(std::vector<geom::point>& T, size_t& M, size_t& N) {
    std::cin >> N;
    std::cin >> M;
    T.resize(0);
    for (size_t i = 0; i < N; ++i) {
        double x, y;
        std::cin >> x >> y;
        T.push_back(geom::point(x, y));
    }
}