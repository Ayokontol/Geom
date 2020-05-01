#include <iostream>
#include "test.hpp"

int main()
{
    std::vector<geom::point> T;
    std::vector<int> Ans;
    size_t M = 3, N;

    input_test(T, M, N);
    geom::find_circles(T, M, Ans);
    for (size_t i = 0; i < Ans.size(); ++i)
        std::cout << Ans[i] << std::endl;

    //random test
    /*while (1) {
        make_test(T, M);
        geom::find_circles(T, M, Ans);
        bool t = test(T, M, Ans);
        if (!t) {
            std::cout << "ups!";
            return 1;
        }
    }*/
    return 0;
}
