#define POLYGON_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

class Polygon {
private:
    int n;
    std::vector<double> X, Y;

    double norme(double x1, double y1, double x2, double y2);
    double angle(double x1, double y1, double x2, double y2, double x3, double y3);
    bool align(double x1, double y1, double x2, double y2, double x3, double y3);
    void clean();
    bool cut(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
    double T_area(double x1, double y1, double x2, double y2, double x3, double y3);

public:
    void create();
    void load();
    bool regular();
    void afficher();
    double perimeter();
    bool simple();
    bool inside(double x, double y);
    double area();
    bool convex();
};
