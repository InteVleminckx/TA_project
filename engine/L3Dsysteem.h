//
// Created by centu on 5/03/2021.
//

#ifndef ENGINE_L3DSYSTEEM_H
#define ENGINE_L3DSYSTEEM_H
#include "ini_configuration.h"
#include "l_parser.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include "Lsysteem.h"
#include "vector3d.h"
#include "Hulpfuncties.h"
#include <stack>
//#include "Figuren3D.h"


using namespace std;

class Face {
public:
    vector<int> point_indexes;
};

class Figure {
public:
    vector<Vector3D> points;
    vector<Face> faces;
    Color color;
};

typedef list<Figure> Figures3D;

class L3Dsysteem {
public:

    std::set<char> alfabet;
    map<char, bool> drawMap;
    map<char,vector<pair<string,double>>> replacements;
    double angleDegrees;
    double angle;
    string initiator;
    unsigned int nr_iterations;
//    double startingAngle;

    Figures3D figuren3D;



Matrix scaleFigure(const double scale);

Matrix rotateX(const double angle);

Matrix rotateY(const double angle);

Matrix rotateZ(const double angle);

Matrix translate(const Vector3D &vector);

void applyTranformation(Figure &figuur, const double &rotateX, const double &rotateY, const double &rotateZ, double &scale, Vector3D &center, const vector<double>& eye);

void toPolar(const Vector3D &point, double &theta, double &phi, double &r);

Matrix eyePointTrans(const Vector3D &eyepoint);

Point2D doProjectionPoint(const Vector3D &point, const double d = 1);

list<Line2D> doProjection(const Figures3D &figuren);

list<Line2D> parse(const ini::Configuration &configuration, int nrFigures, const vector<double>& eye, bool zbufTriag);

Figure parseFile(const string& filenaam, const vector<double>& color);

vector<Face> triangulate(const Face& face);
};


Figure createCube();

Figure createTetrahedron();

Figure createOctahedron();

Figure createIcosahedron();

Figure createDodecahedron();

Figure createCylinder(const int n, const double h);

Figure createCone(const int n, const double h);

Figure createSphere(const double radius, const int n);

Figure createTorus(const double r, const double R, const int n, const int m);

#endif //ENGINE_L3DSYSTEEM_H
