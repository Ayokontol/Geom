#pragma once
#include <vector>

namespace geom {
    struct point {
        double x, y;

        point() {}

        point(double x, double y) :x(x), y(y) {}

        bool operator==(const point& a) const;
    };
}

namespace details {
    using namespace geom;

    double len2(point a);

    double len(point a);

    double dist(point a, point b);

    struct circle {
        geom::point pnt;
        double r;

        circle() {};

        circle(point pnt, double r) : pnt(pnt), r(r) {}

        circle(point a, point b, point c);

        bool operator<(const details::circle& c) const;
    };
}

namespace geom {
    void find_circles(const std::vector<point>& P, int M, std::vector<int>& Ans);
}