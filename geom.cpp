#include "geom.hpp"
#include <set>

bool geom::point::operator==(const point& a) const {
    if (abs(a.x - x) < 0.00001 && abs(a.y - y) < 0.00001)
        return true;
    return false;
}

bool details::circle::operator<(const details::circle& c) const {
    if (pnt == c.pnt && abs(r - c.r) < 0.00001)
        return false;
    return r == c.r ? (pnt.x == c.pnt.x ? pnt.y < c.pnt.y : pnt.x < c.pnt.x) : r < c.r;
}

double details::len2(point a) {
    return a.x * a.x + a.y * a.y;
}

double details::dist(point a, point b) {
    return len(geom::point(a.x - b.x, a.y - b.y));
}

double details::len(point a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

details::circle::circle(point a, point b, point c) {
    double tmp = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));

    double x = (len2(a) * (b.y - c.y) + len2(b) * (c.y - a.y) + len2(c) * (a.y - b.y)) / tmp;
    double y = (len2(a) * (c.x - b.x) + len2(b) * (a.x - c.x) + len2(c) * (b.x - a.x)) / tmp;

    pnt = point(x, y);
    r = dist(a, pnt);
}

void geom::find_circles(const std::vector<point>& P, int M, std::vector<int>& Ans) {
    if (P.size() == 0)
        return;
    Ans.resize(P.size(), -1);

    if (P.size() < 3) {
        for (size_t i = 0; i < Ans.size(); ++i)
            Ans[i] = 1;
        return;
    }

    switch (M) {
    case 1:
        for (size_t i = 0; i < Ans.size(); ++i)
            Ans[i] = 1;
        return;
    case 2: {
        if (P.size() < 5) {  //P.size() >= 3
            Ans[0] = Ans[1] = 1;
            Ans[2] = 2;
            if (P.size() == 4)
                Ans[3] = 2;
        }
        details::circle c;
        for (size_t i = 0; i < 5; ++i)
            for (size_t j = i + 1; j < 5; ++j)
                for (size_t k = j + 1; k < 5; ++k) {
                    c = details::circle(P[i], P[j], P[k]);

                    std::vector<size_t> Index;
                    for (size_t l = 0; l < P.size(); ++l) {
                        if (abs(details::dist(P[l], c.pnt) - c.r) < 0.00001)
                            Ans[l] = 1;
                        else {
                            Ans[l] = 2;
                            Index.push_back(l);
                        }
                    }

                    bool flag = true;
                    //check
                    if (Index.size() >= 3) {
                        geom::point a, b, c;
                        a = P[Index.back()];
                        Index.pop_back();
                        b = P[Index.back()];
                        Index.pop_back();
                        c = P[Index.back()];
                        Index.pop_back();
                        //if all points on the line
                        if (abs(a.x - b.x) < 0.00001 && abs(b.x - c.x) < 0.00001 || abs(a.y - b.y) < 0.00001 && abs(b.y - c.y) < 0.00001)
                            flag = false;

                        details::circle crcl(a, b, c);
                        for (auto ind : Index)
                            if (abs(details::dist(P[ind], crcl.pnt) - crcl.r) >= 0.00001)
                                flag = false;
                    }

                    if (flag)
                        return;
                }
        return;
    }
    case 3: {
        if (P.size() < 7) {  //P.size() >= 3
            Ans[0] = 1;
            Ans[1] = 1;
            Ans[2] = 2;
            if (P.size() >= 4)
                Ans[3] = 2;
            if (P.size() >= 5)
                Ans[4] = 3;
            if (P.size() >= 6)
                Ans[5] = 3;
        }

        if (P.size() == 7) {  //P.size() >= 3
            Ans[0] = 1;
            Ans[1] = 1;
            geom::point a = P[0], b = P[1], c;
            //find 3rd point: a,b,c are not on the line
            for (size_t i = 2; i < 7; ++i) {
                c = P[i];
                if (abs(a.x - b.x) < 0.00001 && abs(b.x - c.x) < 0.00001 || abs(a.y - b.y) < 0.00001 && abs(b.y - c.y) < 0.00001)
                    continue;
                else
                    Ans[i] = 1;
            }
            //other points
            for (size_t i = 2, t = 0; i < 7 && t < 2; ++i)
                if (Ans[i] == -1) {
                    Ans[i] = 2;
                    t++;
                }
            for (size_t i = 2, t = 0; i < 7 && t < 2; ++i)
                if (Ans[i] == -1) {
                    Ans[i] = 3;
                    t++;
                }
        }

        details::circle c1, c2;
        for (size_t i = 0; i < 7; ++i)
            for (size_t j = i + 1; j < 7; ++j)
                for (size_t k = j + 1; k < 7; ++k) {
                    c1 = details::circle(P[i], P[j], P[k]);

                    std::vector<geom::point> P2;
                    std::vector<size_t> Index2;
                    for (size_t l = 0; l < P.size(); ++l) {
                        if (abs(details::dist(P[l], c1.pnt) - c1.r) < 0.00001)
                            Ans[l] = 1;
                        else {
                            Ans[l] = 2;
                            P2.push_back(P[l]);
                            Index2.push_back(l);
                        }
                    }

                    if (P2.size() < 5) {
                        if (P2.size() > 0)
                            Ans[Index2[0]] = 2;
                        if (P2.size() > 1)
                            Ans[Index2[1]] = 2;
                        if (P2.size() > 2)
                            Ans[Index2[2]] = 3;
                        if (P2.size() > 3)
                            Ans[Index2[3]] = 3;
                        return;
                    }

                    for (size_t f = 0; f < 5; ++f) {
                        for (size_t g = f + 1; g < 5; ++g) {
                            for (size_t h = g + 1; h < 5; ++h) {

                                c2 = details::circle(P2[f], P2[g], P2[h]);

                                std::vector<size_t> Index;
                                for (size_t l = 0; l < P.size(); ++l) {
                                    if (abs(details::dist(P[l], c2.pnt) - c2.r) < 0.00001)
                                        Ans[l] = 2;
                                    else if (Ans[l] != 1) {
                                        Ans[l] = 3;
                                        Index.push_back(l);
                                    }
                                }

                                bool flag = true;
                                //check
                                if (Index.size() >= 3) {
                                    geom::point a, b, c;
                                    a = P[Index.back()];
                                    Index.pop_back();
                                    b = P[Index.back()];
                                    Index.pop_back();
                                    c = P[Index.back()];
                                    Index.pop_back();
                                    //if all points on the line
                                    if (abs(a.x - b.x) < 0.00001 && abs(b.x - c.x) < 0.00001 || abs(a.y - b.y) < 0.00001 && abs(b.y - c.y) < 0.00001)
                                        flag = false;

                                    details::circle crcl(a, b, c);
                                    for (auto ind : Index)
                                        if (abs(details::dist(P[ind], crcl.pnt) - crcl.r) >= 0.00001)
                                            flag = false;
                                }

                                if (flag)
                                    return;
                            }
                        }
                    }
                }
        }
        return;
    }
}

