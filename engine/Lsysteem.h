//
// Created by centu on 19/02/2021.
//
#ifndef ENGINE_LSYSTEEM_H
#define ENGINE_LSYSTEEM_H
#include "easy_image.h"
#include "Hulpfuncties.h"
#include "ZBuffer.h"
#include <list>
//#include "L3Dsysteem.h"
using namespace std;

//class L3Dsysteem;
class Color{
public:
    double red;
    double green;
    double blue;
};
class Point2D {
public:
    double x;
    double y;
};
class Line2D {
public:
    Point2D p1;
    Point2D p2;
    Color color;

    double z1;
    double z2;


    Line2D(Point2D punt1, Point2D punt2, Color kleur);

};


// functie draw2DLines
// tekent één voor één de lijnen uit de vector lines die meegegeven wordt.
img::EasyImage draw2DLines(const std::list<Line2D> &lines, const int size, const vector<double>& backgroundColor, bool ZBuffering);



#endif //ENGINE_LSYSTEEM_H
