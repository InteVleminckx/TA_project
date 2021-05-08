//
// Created by centu on 5/03/2021.
//

# define M_PI   3.14159265358979323846 // gevonden op https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c

#include "L3Dsysteem.h"

Matrix L3Dsysteem::scaleFigure(const double scale) {
    Matrix s;
    s(1, 1) = scale;
    s(2, 2) = scale;
    s(3, 3) = scale;

    return s;
}

Matrix L3Dsysteem::rotateX(const double angle) {

    Matrix Mx;
    double angleRad = angle*(M_PI/180);
    Mx(2, 2) = cos(angleRad);
    Mx(2, 3) = sin(angleRad);
    Mx(3, 2) = -sin(angleRad);
    Mx(3, 3) = cos(angleRad);

    return Mx;
}

Matrix L3Dsysteem::rotateY(const double angle) {
    Matrix My;
    double angleRad = angle*(M_PI/180);
    My(1, 1) = cos(angleRad);
    My(1, 3) = -sin(angleRad);
    My(3, 1) = sin(angleRad);
    My(3, 3) = cos(angleRad);

    return My;
}

Matrix L3Dsysteem::rotateZ(const double angle) {
    Matrix Mz;
    double angleRad = angle*(M_PI/180);
    Mz(1, 1) = cos(angleRad);
    Mz(1, 2) = sin(angleRad);
    Mz(2, 1) = -sin(angleRad);
    Mz(2, 2) = cos(angleRad);

    return Mz;
}

Matrix L3Dsysteem::translate(const Vector3D &vector) {
    Matrix T;
    T(4, 1) = vector.x;
    T(4, 2) = vector.y;
    T(4, 3) = vector.z;

    return T;
}

list<Line2D> L3Dsysteem::parse(const ini::Configuration &configuration, int nrFigures, const vector<double>& eye, bool zbufTriag) {
    Figures3D figuren;
    for (auto i = 0; i < nrFigures; i++) {
        string figuurNaam = "Figure" + to_string(i);
        Figure figuur;

        double rotateX = configuration[figuurNaam]["rotateX"].as_double_or_die();
        double rotateY = configuration[figuurNaam]["rotateY"].as_double_or_die();
        double rotateZ = configuration[figuurNaam]["rotateZ"].as_double_or_die();

        double scale = configuration[figuurNaam]["scale"].as_double_or_die();

        vector<double> center = configuration[figuurNaam]["center"].as_double_tuple_or_die();

        Vector3D centerPunt;
        centerPunt.x = center[0];
        centerPunt.y = center[1];
        centerPunt.z = center[2];

        vector<double> color = configuration[figuurNaam]["color"].as_double_tuple_or_die();
        figuur.color.red = color[0];
        figuur.color.blue = color[2];
        figuur.color.green = color[1];

        if (configuration[figuurNaam]["type"].as_string_or_die() == "Cube") {

            Figure kubus = createCube();

            kubus.color.red = color[0];
            kubus.color.blue = color[2];
            kubus.color.green = color[1];

            applyTranformation(kubus, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(kubus);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Tetrahedron") {
            Figure tetrahedron = createTetrahedron();

            tetrahedron.color.red = color[0];
            tetrahedron.color.blue = color[2];
            tetrahedron.color.green = color[1];

            applyTranformation(tetrahedron, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(tetrahedron);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Icosahedron") {
            Figure icosahedron = createIcosahedron();

            icosahedron.color.red = color[0];
            icosahedron.color.blue = color[2];
            icosahedron.color.green = color[1];

            applyTranformation(icosahedron, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(icosahedron);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Dodecahedron") {
            Figure dodecahedron = createDodecahedron();

            dodecahedron.color.red = color[0];
            dodecahedron.color.blue = color[2];
            dodecahedron.color.green = color[1];

            applyTranformation(dodecahedron, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(dodecahedron);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Octahedron") {
            Figure octahedron = createOctahedron();

            octahedron.color.red = color[0];
            octahedron.color.blue = color[2];
            octahedron.color.green = color[1];

            applyTranformation(octahedron, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(octahedron);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Cone") {
            double height = configuration[figuurNaam]["height"].as_double_or_die();
            int n = configuration[figuurNaam]["n"].as_int_or_die();
            Figure cone = createCone(n, height);

            cone.color.red = color[0];
            cone.color.blue = color[2];
            cone.color.green = color[1];

            applyTranformation(cone, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(cone);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Cylinder") {
            double height = configuration[figuurNaam]["height"].as_double_or_die();
            int n = configuration[figuurNaam]["n"].as_int_or_die();
            Figure cylinder = createCylinder(n, height);

            cylinder.color.red = color[0];
            cylinder.color.blue = color[2];
            cylinder.color.green = color[1];

            applyTranformation(cylinder, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(cylinder);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Sphere") {
            int radius;
            int n = configuration[figuurNaam]["n"].as_int_or_die();
            Figure sphere = createSphere(radius, n);

            sphere.color.red = color[0];
            sphere.color.blue = color[2];
            sphere.color.green = color[1];

            applyTranformation(sphere, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(sphere);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "Torus") {
            int m = configuration[figuurNaam]["m"].as_int_or_die();
            int n = configuration[figuurNaam]["n"].as_int_or_die();
            double r = configuration[figuurNaam]["r"].as_double_or_die();
            double R = configuration[figuurNaam]["R"].as_double_or_die();
            Figure torus = createTorus(r, R, n, m);

            torus.color.red = color[0];
            torus.color.blue = color[2];
            torus.color.green = color[1];

            applyTranformation(torus, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(torus);
        }
        else if (configuration[figuurNaam]["type"].as_string_or_die() == "3DLSystem") {
            string inputfile = configuration[figuurNaam]["inputfile"].as_string_or_die();

            Figure figuur1 = parseFile(inputfile, color);

            figuur1.color.red = color[0];
            figuur1.color.blue = color[2];
            figuur1.color.green = color[1];

            applyTranformation(figuur1, rotateX, rotateY, rotateZ, scale, centerPunt, eye);
            figuren.push_back(figuur1);
        }
        else {
            int nrPoints = configuration[figuurNaam]["nrPoints"].as_int_or_die();
            int nrLines = configuration[figuurNaam]["nrLines"].as_int_or_die();

            for (auto j = 0; j < nrPoints; j++) {
                string puntNaam = "point" + to_string(j);
                Vector3D punt;
                vector<double> puntTuple = configuration[figuurNaam][puntNaam].as_double_tuple_or_die();
                punt.x = puntTuple[0];
                punt.y = puntTuple[1];
                punt.z = puntTuple[2];
                figuur.points.push_back(punt);
            }

            for (auto k = 0; k < nrLines; k++) {
                string lijnNaam = "line" + to_string(k);
                Face vlak;
                vector<int> lijn = configuration[figuurNaam][lijnNaam].as_int_tuple_or_die();
                vlak.point_indexes = lijn;
                figuur.faces.push_back(vlak);
            }

            applyTranformation(figuur, rotateX, rotateY, rotateZ, scale, centerPunt, eye);

            figuren.push_back(figuur);
        }
    }
    if (zbufTriag) {
        for (auto it = figuren.begin(); it != figuren.end(); it++) {
            Figure figuur;
            figuur.points = it->points;
            figuur.color = it->color;

            vector<Face> vlakken = it->faces;
            for (auto it2 = 0; it2 < vlakken.size(); it2++) {
                vector<Face> getrianguleerdeVlakken = triangulate(vlakken[it2]);
                for (auto it3 = 0; it3 < getrianguleerdeVlakken.size(); it3++) {
                    figuur.faces.push_back(getrianguleerdeVlakken[it3]);
                }
            }
            figuren3D.push_back(figuur);
        }
    }
    list<Line2D> lijnen = doProjection(figuren);
    return lijnen;
}

Matrix L3Dsysteem::eyePointTrans(const Vector3D &eyepoint) {
    double theta;
    double phi;
    double r;
    toPolar(eyepoint, theta, phi, r);

    Matrix V;
    V(1, 1) = -sin(theta);
    V(1, 2) = -cos(theta) * cos(phi);
    V(1, 3) = cos(theta) * sin(phi);
    V(2, 1) = cos(theta);
    V(2, 2) = -sin(theta) * cos(phi);
    V(3, 2) = sin(phi);
    V(2, 3) = sin(theta) * sin(phi);
    V(3,3) = cos(phi);
    V(4, 3) = -r;

    return V;

}

void L3Dsysteem::toPolar(const Vector3D &point, double &theta, double &phi, double &r) {
    r = sqrt(pow((point.x), 2) + pow((point.y), 2) + pow((point.z), 2));
    theta = atan2(point.y, point.x);
    phi = acos(point.z / r);

}

list<Line2D> L3Dsysteem::doProjection(const Figures3D &figuren) {
    list<Line2D> lijnen;

    for (auto it = figuren.begin(); it != figuren.end(); it++) {
        vector<Vector3D> punten = it->points;
        vector<Face> vlakken = it->faces;

        for (auto it2 = 0; it2 < vlakken.size(); it2++) {
            vector<Point2D> lijn;
            vector<double> Z_waarden;
            for (auto it3 = 0; it3 < vlakken[it2].point_indexes.size(); it3++) {
                Point2D punt = doProjectionPoint(punten[vlakken[it2].point_indexes[it3]], 1); // index -1 doen?
                lijn.push_back(punt);

                Z_waarden.push_back(punten[vlakken[it2].point_indexes[it3]].z);
            }

            if (lijn.size() == 2) {
                Line2D lijn1 = Line2D(lijn[0], lijn[1], it->color);
                lijn1.z1 = Z_waarden[0];
                lijn1.z2 = Z_waarden[1];
                lijnen.push_back(lijn1);
            }
            else {
                for (auto i = 0; i < lijn.size()-1; i++) {
                    Line2D lijn1 = Line2D(lijn[i], lijn[i+1], it->color);
                    lijn1.z1 = Z_waarden[i];
                    lijn1.z2 = Z_waarden[i+1];
                    lijnen.push_back(lijn1);
                }
                Line2D lijn1 = Line2D(lijn[0], lijn[lijn.size()-1], it->color);
                lijn1.z1 = Z_waarden[0];
                lijn1.z2 = Z_waarden[Z_waarden.size()-1];
                lijnen.push_back(lijn1);
            }
        }
    }

    return lijnen;
}

Point2D L3Dsysteem::doProjectionPoint(const Vector3D &point, const double d) {
    Point2D punt;
    punt.x = (d * point.x) / (-point.z);
    punt.y = (d * point.y) / (-point.z);
    return punt;
}

void L3Dsysteem::applyTranformation(Figure &figuur, const double &RotateX, const double &RotateY, const double &RotateZ,
                        double &scale, Vector3D &center, const vector<double>& eye) {
    Vector3D eyepoint;
    eyepoint.x = eye[0];
    eyepoint.y = eye[1];
    eyepoint.z = eye[2];

    Matrix TransformatieMatrix = scaleFigure(scale);
    TransformatieMatrix *= rotateX(RotateX);
    TransformatieMatrix *= rotateY(RotateY);
    TransformatieMatrix *= rotateZ(RotateZ);
    TransformatieMatrix *= translate(center);
    TransformatieMatrix *= eyePointTrans(eyepoint);
    for (auto it = 0; it < figuur.points.size(); it++) {
        figuur.points[it] *= TransformatieMatrix;
    }
}


//
Figure createCube() {
    Figure kubus;
    Vector3D punt1;
    punt1.x = 1;
    punt1.y = -1;
    punt1.z = -1;
    Vector3D punt2;
    punt2.x = -1;
    punt2.y = 1;
    punt2.z = -1;
    Vector3D punt3;
    punt3.x = 1;
    punt3.y = 1;
    punt3.z = 1;
    Vector3D punt4;
    punt4.x = -1;
    punt4.y = -1;
    punt4.z = 1;
    Vector3D punt5;
    punt5.x = 1;
    punt5.y = 1;
    punt5.z = -1;
    Vector3D punt6;
    punt6.x = -1;
    punt6.y = -1;
    punt6.z = -1;
    Vector3D punt7;
    punt7.x = 1;
    punt7.y = -1;
    punt7.z = 1;
    Vector3D punt8;
    punt8.x = -1;
    punt8.y = 1;
    punt8.z = 1;
    kubus.points.push_back(punt1);
    kubus.points.push_back(punt2);
    kubus.points.push_back(punt3);
    kubus.points.push_back(punt4);
    kubus.points.push_back(punt5);
    kubus.points.push_back(punt6);
    kubus.points.push_back(punt7);
    kubus.points.push_back(punt8);

    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(6);

    kubus.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(2);

    kubus.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(7);

    kubus.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(3);

    kubus.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(3);

    kubus.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(4);

    kubus.faces.push_back(vlak1);

    return kubus;
}
//
Figure createTetrahedron() {
    Figure tetrahedron;
    Vector3D punt1;
    punt1.x = 1;
    punt1.y = -1;
    punt1.z = -1;
    Vector3D punt2;
    punt2.x = -1;
    punt2.y = 1;
    punt2.z = -1;
    Vector3D punt3;
    punt3.x = 1;
    punt3.y = 1;
    punt3.z = 1;
    Vector3D punt4;
    punt4.x = -1;
    punt4.y = -1;
    punt4.z = 1;
    tetrahedron.points.push_back(punt1);
    tetrahedron.points.push_back(punt2);
    tetrahedron.points.push_back(punt3);
    tetrahedron.points.push_back(punt4);

    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(2);
    tetrahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(2);
    tetrahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(1);
    tetrahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(3);
    tetrahedron.faces.push_back(vlak1);

    return tetrahedron;
}
//
Figure createOctahedron() {
    Figure octahedron;
    Vector3D punt1;
    punt1.x = 1;
    punt1.y = 0;
    punt1.z = 0;
    Vector3D punt2;
    punt2.x = 0;
    punt2.y = 1;
    punt2.z = 0;
    Vector3D punt3;
    punt3.x = -1;
    punt3.y = 0;
    punt3.z = 0;
    Vector3D punt4;
    punt4.x = 0;
    punt4.y = -1;
    punt4.z = 0;
    Vector3D punt5;
    punt5.x = 0;
    punt5.y = 0;
    punt5.z = -1;
    Vector3D punt6;
    punt6.x = 0;
    punt6.y = 0;
    punt6.z = 1;

    octahedron.points.push_back(punt1);
    octahedron.points.push_back(punt2);
    octahedron.points.push_back(punt3);
    octahedron.points.push_back(punt4);
    octahedron.points.push_back(punt5);
    octahedron.points.push_back(punt6);

    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(5);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(5);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(5);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(5);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(4);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(4);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(4);

    octahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(4);

    octahedron.faces.push_back(vlak1);

    return octahedron;
}
//
Figure createIcosahedron() {
    Figure icosahedron;

    for (auto i = 1; i < 13; i++) {
        Vector3D punt1;
        if (i == 1) {
            punt1.x = 0;
            punt1.y = 0;
            punt1.z = sqrt(5)/2;
        }
        else if (i > 1 && i < 7) {
            punt1.x = cos((i-2)*(2*M_PI)/5);
            punt1.y = sin((i-2)*(2*M_PI)/5);
            punt1.z = 0.5;
        }
        else if (i > 6 && i < 12) {
            punt1.x = cos((M_PI/5)+(i-7)*(2*M_PI)/5);
            punt1.y = sin((M_PI/5)+(i-7)*(2*M_PI)/5);
            punt1.z = -0.5;
        }
        else if (i == 12) {
            punt1.x = 0;
            punt1.y = 0;
            punt1.z = -sqrt(5)/2;
        }
        icosahedron.points.push_back(punt1);
    }

    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(2);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(3);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(4);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(5);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(1);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(2);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(7);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(3);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(8);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(8);
    vlak1.point_indexes.push_back(4);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(8);
    vlak1.point_indexes.push_back(9);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(9);
    vlak1.point_indexes.push_back(5);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(9);
    vlak1.point_indexes.push_back(10);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(10);
    vlak1.point_indexes.push_back(1);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(10);
    vlak1.point_indexes.push_back(6);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(6);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(8);
    vlak1.point_indexes.push_back(7);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(9);
    vlak1.point_indexes.push_back(8);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(10);
    vlak1.point_indexes.push_back(9);

    icosahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(10);

    icosahedron.faces.push_back(vlak1);

    return icosahedron;
}
//
Figure createDodecahedron() {
    Figure dodecahedron;
    Figure icosahedron = createIcosahedron();

    for (auto i = 0; i < icosahedron.faces.size(); i++) {

        vector<int> puntIndexen = icosahedron.faces[i].point_indexes;

        Vector3D puntA = icosahedron.points[puntIndexen[0]];
        Vector3D puntB = icosahedron.points[puntIndexen[1]];
        Vector3D puntC = icosahedron.points[puntIndexen[2]];

        Vector3D punt1;

        punt1.x = (puntA.x + puntB.x + puntC.x)/3;
        punt1.y = (puntA.y + puntB.y + puntC.y)/3;
        punt1.z = (puntA.z + puntB.z + puntC.z)/3;

        dodecahedron.points.push_back(punt1);
    }

    Face vlak1;
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(4);


    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(0);
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(1);


    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(1);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(8);
    vlak1.point_indexes.push_back(9);
    vlak1.point_indexes.push_back(2);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(2);
    vlak1.point_indexes.push_back(9);
    vlak1.point_indexes.push_back(10);
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(3);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(3);
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(12);
    vlak1.point_indexes.push_back(13);
    vlak1.point_indexes.push_back(4);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(4);
    vlak1.point_indexes.push_back(13);
    vlak1.point_indexes.push_back(14);
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(0);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(19);
    vlak1.point_indexes.push_back(18);
    vlak1.point_indexes.push_back(17);
    vlak1.point_indexes.push_back(16);
    vlak1.point_indexes.push_back(15);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(19);
    vlak1.point_indexes.push_back(14);
    vlak1.point_indexes.push_back(13);
    vlak1.point_indexes.push_back(12);
    vlak1.point_indexes.push_back(18);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(18);
    vlak1.point_indexes.push_back(12);
    vlak1.point_indexes.push_back(11);
    vlak1.point_indexes.push_back(10);
    vlak1.point_indexes.push_back(17);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(17);
    vlak1.point_indexes.push_back(10);
    vlak1.point_indexes.push_back(9);
    vlak1.point_indexes.push_back(8);
    vlak1.point_indexes.push_back(16);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(16);
    vlak1.point_indexes.push_back(8);
    vlak1.point_indexes.push_back(7);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(15);

    dodecahedron.faces.push_back(vlak1);

    vlak1.point_indexes.clear();
    vlak1.point_indexes.push_back(15);
    vlak1.point_indexes.push_back(6);
    vlak1.point_indexes.push_back(5);
    vlak1.point_indexes.push_back(14);
    vlak1.point_indexes.push_back(19);

    dodecahedron.faces.push_back(vlak1);

    return dodecahedron;
}
//
Figure createCylinder(const int n, const double h) {
    Figure cylinder;
    for (auto i = 0; i < n; i++) {
        Vector3D punt;
        punt.x = cos(2*i*M_PI/n);
        punt.y = sin(2*i*M_PI/n);
        punt.z = 0;
        cylinder.points.push_back(punt);
    }
    for (auto i = 0; i < n; i++) {
        Vector3D punt;
        punt.x = cos(2*i*M_PI/n);
        punt.y = sin(2*i*M_PI/n);
        punt.z = h;
        cylinder.points.push_back(punt);
    }
    // zijvlakken
    for (auto i = 0; i < n; i++) {
        Face vlak;
        vlak.point_indexes.push_back(i);
        vlak.point_indexes.push_back((i+1)%(n));
        vlak.point_indexes.push_back((i+1)%n+n);
        vlak.point_indexes.push_back(n+i);
        cylinder.faces.push_back(vlak);
    }
    // grondvlak
    Face vlak;
    for (auto i = n-1; i >= 0; i--) {
        vlak.point_indexes.push_back(i);
    }
    cylinder.faces.push_back(vlak);
    vlak.point_indexes.clear();
    // bovenvlak
    for (auto i = n-1; i >= 0; i--) {
        vlak.point_indexes.push_back(n+i);
    }
    cylinder.faces.push_back(vlak);

    return cylinder;
}
//
Figure createCone(const int n, const double h) {
    Figure cone;
    for (auto i = 0; i < n; i++) {
        Vector3D punt;
        punt.x = cos(2*i*M_PI/n);
        punt.y = sin(2*i*M_PI/n);
        punt.z = 0;
        cone.points.push_back(punt);
    }
    Vector3D puntBoven;
    puntBoven.x = 0;
    puntBoven.y = 0;
    puntBoven.z = h;
    cone.points.push_back(puntBoven);

    for (auto i = 0; i < n; i++) {
        Face vlak;
        vlak.point_indexes.push_back(i);
        vlak.point_indexes.push_back((i+1)%(n));
        vlak.point_indexes.push_back(n);
        cone.faces.push_back(vlak);
    }
    Face vlak;
    for (auto i = n-1; i >= 0; i--) {
        vlak.point_indexes.push_back(i);
    }
    cone.faces.push_back(vlak);

    return cone;
}
//
Figure createSphere(const double radius, const int n) {
    Figure icosahedron = createIcosahedron();

    for (auto i = 0; i < n; i++) {
        Figure icosahedronVerfijnd;

        for (auto j = 0; j < icosahedron.faces.size(); j++) {
            vector<int> puntIndexen = icosahedron.faces[j].point_indexes;

            Vector3D puntA = icosahedron.points[puntIndexen[0]];
            Vector3D puntB = icosahedron.points[puntIndexen[1]];
            Vector3D puntC = icosahedron.points[puntIndexen[2]];

            Vector3D puntD = (puntA + puntB)/2; // (A + B) / 2

            Vector3D puntE = (puntA + puntC)/2; // (A + C) / 2

            Vector3D puntF = (puntB + puntC)/2; // (B + C) / 2

            icosahedronVerfijnd.points.push_back(puntA);
            icosahedronVerfijnd.points.push_back(puntD);
            icosahedronVerfijnd.points.push_back(puntB);
            icosahedronVerfijnd.points.push_back(puntF);
            icosahedronVerfijnd.points.push_back(puntC);
            icosahedronVerfijnd.points.push_back(puntE);

            Face driehoek; // + (j*6) omdat we telkens 6 punten maken met driehoek, voor de volgende faces
            driehoek.point_indexes.push_back(0+(j*6)); // A
            driehoek.point_indexes.push_back(1+(j*6)); // D
            driehoek.point_indexes.push_back(5+(j*6)); // E
            icosahedronVerfijnd.faces.push_back(driehoek);
            driehoek.point_indexes.clear();

            driehoek.point_indexes.push_back(2+(j*6)); // B
            driehoek.point_indexes.push_back(3+(j*6)); // F
            driehoek.point_indexes.push_back(1+(j*6)); // D
            icosahedronVerfijnd.faces.push_back(driehoek);
            driehoek.point_indexes.clear();

            driehoek.point_indexes.push_back(4+(j*6)); // C
            driehoek.point_indexes.push_back(5+(j*6)); // E
            driehoek.point_indexes.push_back(3+(j*6)); // F
            icosahedronVerfijnd.faces.push_back(driehoek);
            driehoek.point_indexes.clear();

            driehoek.point_indexes.push_back(1+(j*6)); // D
            driehoek.point_indexes.push_back(3+(j*6)); // F
            driehoek.point_indexes.push_back(5+(j*6)); // E
            icosahedronVerfijnd.faces.push_back(driehoek);
            driehoek.point_indexes.clear();

        }
        icosahedron = icosahedronVerfijnd;
    }

    //herschalen punten
    for (auto i = 0; i < icosahedron.points.size(); i++) {
        Vector3D oudPunt = icosahedron.points[i];
        double r = sqrt(pow(oudPunt.x, 2) + pow(oudPunt.y, 2) + pow(oudPunt.z, 2));
        icosahedron.points[i].x = icosahedron.points[i].x/r;
        icosahedron.points[i].y = icosahedron.points[i].y/r;
        icosahedron.points[i].z = icosahedron.points[i].z/r;
    }
    return icosahedron;
}
//
Figure createTorus(const double r, const double R, const int n, const int m) {
    Figure torus;

    // punten
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < m; j++) {
            double u = 2*i*M_PI/n;
            double v = 2*j*M_PI/m;
            Vector3D punt;
            punt.x = (R + r*cos(v))*cos(u);
            punt.y = (R + r*cos(v))*sin(u);
            punt.z = r*sin(v);
            torus.points.push_back(punt);

        }
    }

    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < m; j++) {
            Face vlak;
            vlak.point_indexes.push_back(i*m+j);
            vlak.point_indexes.push_back(((i+1)%(n))*m+j);
            vlak.point_indexes.push_back(((i+1)%(n))*m+(j+1)%m);
            vlak.point_indexes.push_back(i*m+(j+1)%m);

            torus.faces.push_back(vlak);
        }
    }

    return torus;
}

Figure L3Dsysteem::parseFile(const string &filenaam, const vector<double>& color) {

    LParser::LSystem3D l_system;

    std::ifstream input_stream(filenaam);
    input_stream >> l_system;
    input_stream.close();

    alfabet = l_system.get_alphabet();

    for (auto it = alfabet.begin(); it != alfabet.end(); it++) {
        // we maken 2 mappen: de drawMap bevat telkens de letter met als value of die getekend moet worden of niet (bool)
        // de replacements bevat de string waarin het symbool moet veranderd worden
        char letter = *it;
        drawMap[letter] = l_system.draw(*it);
        replacements[letter] = l_system.get_replacement(letter);
    }

    angleDegrees = l_system.get_angle(); // hoek in graden
    angle = angleDegrees*(M_PI/180); // hoek in radialen
    initiator = l_system.get_initiator();
    nr_iterations = l_system.get_nr_iterations();

    string code = initiator;
    string code1;

    for (auto i = 0; i < nr_iterations;i++) {
        // hier vervangen we elk symbool in onze huidige string door de replacement rule die ermee
        // overeenkomt (als er meerdere repl. rules zijn ieder met een percentage, dan kiezen we een getal tussen 0 en 1
        // en kijken we in welk interval uit onze map grenzen dit getal zit, zo kiezen we dan de juiste replacement string)
        string tempstring;
        code1 = "";

        for (auto j = 0; j < code.size();j++) {
            if (count(alfabet.begin(), alfabet.end(), code[j])) {
                tempstring = replacements[code[j]][0].first; // origineel zonder stoch. repl. rules
            }
            else {
                tempstring = code[j];
            }
            code1 += tempstring;
        }
        code = code1;
    }

//    list<Line2D> Lines2D;

//    Point2D punt1; punt1.x = 0; punt1.y = 0; // eerste punt start op (0,0)
//    Point2D punt2;

    Figure figuur;

    // huidige locatie
    Vector3D huidigeLocatie = Vector3D::point(0,0,0);
//    huidigeLocatie.x = 0;
//    huidigeLocatie.y = 0;
//    huidigeLocatie.z = 0;

    Vector3D nieuweLocatie;

    // initiële waarden voor de vectoren H, L en U.
    Vector3D H = Vector3D::vector(1,0,0);
//    H.x = 1;
//    H.y = 0;
//    H.z = 0;
    Vector3D L = Vector3D::vector(0,1,0);
//    L.x = 0;
//    L.y = 1;
//    L.z = 0;
    Vector3D U = Vector3D::vector(0,0,1);
//    U.x = 0;
//    U.y = 0;
//    U.z = 1;

    Color kleur;
    kleur.red = color[0]; // niet *255, want dit doen we in de functie die we aanroepen om de lijnen te tekenen
    kleur.blue = color[2];
    kleur.green = color[1];

    stack<vector<Vector3D>> stack1;
    int index = 0;
    for (auto c = 0; c < code.size();c++) {

        if (code[c] == '+') { // we draaien naar links over een hoek delta (we roteren de H- en de L-vector delta radialen om de U-vector.
            Vector3D H1 = H*cos(angle) + L*sin(angle);
            Vector3D L1 = -H*sin(angle) + L*cos(angle);
            H = H1;
            L = L1;
        }
        else if (code[c] == '-') { // we draaien naar rechts over een hoek delta.
            Vector3D H1 = H*cos(-angle) + L*sin(-angle);
            Vector3D L1 = -H*sin(-angle) + L*cos(-angle);
            H = H1;
            L = L1;
        }
        else if (code[c] == '^') { // we draaien delta radialen opwaarts
            Vector3D H1 = H*cos(angle) + U*sin(angle);
            Vector3D U1 = -H*sin(angle) + U*cos(angle);
            H = H1;
            U = U1;
        }
        else if (code[c] == '&') { // we draaien delta radialen neerwaarts
            Vector3D H1 = H*cos(-angle) + U*sin(-angle);
            Vector3D U1 = -H*sin(-angle) + U*cos(-angle);
            H = H1;
            U = U1;
        }
        else if (code[c] == '\\') { // we maken een rolbeweging naar links over delta radialen
            Vector3D L1 = L*cos(angle) + U*sin(-angle);
            Vector3D U1 = -L*sin(-angle) + U*cos(angle);
            L = L1;
            U = U1;
        }
        else if (code[c] == '/') { // we maken een rolbeweging naar rechts over delta radialen
            Vector3D L1 = L*cos(angle) + U*sin(angle);
            Vector3D U1 = -L*sin(angle) + U*cos(angle);
            L = L1;
            U = U1;
        }
        else if (code[c] == '|') { // we keren onze richting om
            H = -H;
            L = -L;
        }
        else if (code[c] == '(') {
            vector<Vector3D> vector;
            vector.push_back(huidigeLocatie);
            vector.push_back(H);
            vector.push_back(L);
            vector.push_back(U);

            stack1.push(vector);
        }
        else if (code[c] == ')') {
            huidigeLocatie = stack1.top()[0];
            H = stack1.top()[1];
            L = stack1.top()[2];
            U = stack1.top()[3];

            stack1.pop();
        }
        else {
//            nieuweLocatie.x = huidigeLocatie.x+H.x; // nieuwe x = oude x * cos(hoek)
//            nieuweLocatie.y = huidigeLocatie.y+H.y; // nieuwe y = oude y * sin(hoek)
//            nieuweLocatie.z = huidigeLocatie.z+H.z;
            Vector3D nieuwPunt = huidigeLocatie;
            huidigeLocatie += H;
            if (drawMap[code[c]]) { // als de letter getekend moet worden (bool = true)
//                Line2D lijn = Line2D(punt1, punt2, kleur);
//                Lines2D.push_back(lijn); // we voegen de lijn toe aan de vector Lines2D

                figuur.points.push_back(nieuwPunt);
                figuur.points.push_back(huidigeLocatie);

                Face vlak;
                vlak.point_indexes.push_back(figuur.points.size()-2);
                vlak.point_indexes.push_back(figuur.points.size()-1);

                figuur.faces.push_back(vlak);

                index++;

            }
//            punt1.x = punt2.x; // oud punt wordt nieuw punt
//            punt1.y = punt2.y;
        }
    }
    return figuur;
}

vector<Face> L3Dsysteem::triangulate(const Face& face) {
    vector<Face> vlakken;

//    if (face.point_indexes.size() == 3) {
//        vlakken.push_back(face);
//    }
//    else {
        for (auto i = 0; i < face.point_indexes.size()-2; i++) {
            Face driehoek;
            driehoek.point_indexes.push_back(face.point_indexes[0]);
            driehoek.point_indexes.push_back(face.point_indexes[i+1]);
            driehoek.point_indexes.push_back(face.point_indexes[i+2]);

            vlakken.push_back(driehoek);
        }
//    }
    return vlakken;
}
