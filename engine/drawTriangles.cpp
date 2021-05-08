//
// Created by centu on 5/05/2021.
//

#include "drawTriangles.h"

img::EasyImage drawTriangles(const int size, const vector<double>& backgroundColor, list<Figure> &figuren) {

    double posInf = numeric_limits<double>::infinity();
    double negInf = -numeric_limits<double>::infinity();

    double Xmax = negInf;
    double Xmin = posInf;
    double Ymax = negInf;
    double Ymin = posInf;

    for (auto it = figuren.begin(); it != figuren.end(); it++) {
        for (auto i = 0; i < it->points.size(); i++) {
            Point2D punt;
            double d = 1;
            punt.x = (d * it->points[i].x) / (-it->points[i].z);
            punt.y = (d * it->points[i].y) / (-it->points[i].z);

            if (punt.x > Xmax) { // als één van de x coordinaten van de nieuwe lijn groter is, wordt dat het nieuwe maximum
                Xmax = punt.x;
            }
            if (punt.x < Xmin) { // als één van de x coordinaten van de nieuwe lijn kleiner is, wordt dat het nieuwe minimum
                Xmin = punt.x;
            }
            if (punt.y > Ymax) { // als één van de y coordinaten van de nieuwe lijn groter is, wordt dat het nieuwe maximum
                Ymax = punt.y;
            }
            if (punt.y < Ymin) { // als één van de y coordinaten van de nieuwe lijn groter is, wordt dat het nieuwe maximum
                Ymin = punt.y;
            }
        }
    }

    double Xrange = Xmax - Xmin;
    double Yrange = Ymax - Ymin;

    double ImageX = size*(Xrange/std::max(Xrange, Yrange));
    double ImageY = size*(Yrange/std::max(Xrange, Yrange));

    ZBuffer zBuffer(ImageX, ImageY);

    img::EasyImage image(roundToInt(ImageX), roundToInt(ImageY));
    img::Color achtergrond;
    achtergrond.red = backgroundColor[0]*255;
    achtergrond.blue = backgroundColor[2]*255;
    achtergrond.green = backgroundColor[1]*255;
    image.clear(achtergrond); // achtergrondkleur zetten

    double schaalfactor = 0.95*(ImageX/Xrange); // = d

    double DCx = schaalfactor*((Xmin+Xmax)/2);
    double DCy = schaalfactor*((Ymin+Ymax)/2);
    double dx = ImageX/2 - DCx;
    double dy = ImageY/2 - DCy;

    for (auto it = figuren.begin(); it != figuren.end(); it++) {
        img::Color kleur;
        kleur.red = it->color.red*255;
        kleur.blue = it->color.blue*255;
        kleur.green = it->color.green*255;

        for (auto it2 = 0; it2 < it->faces.size(); it2++) {
            Vector3D punt1; // eerste punt van de driehoek
            punt1.x = it->points[it->faces[it2].point_indexes[0]].x;
            punt1.y = it->points[it->faces[it2].point_indexes[0]].y;
            punt1.z = it->points[it->faces[it2].point_indexes[0]].z;

            Vector3D punt2; // tweede punt van de driehoek
            punt2.x = it->points[it->faces[it2].point_indexes[1]].x;
            punt2.y = it->points[it->faces[it2].point_indexes[1]].y;
            punt2.z = it->points[it->faces[it2].point_indexes[1]].z;

            Vector3D punt3; // derde punt van de driehoek
            punt3.x = it->points[it->faces[it2].point_indexes[2]].x;
            punt3.y = it->points[it->faces[it2].point_indexes[2]].y;
            punt3.z = it->points[it->faces[it2].point_indexes[2]].z;

            draw_zbuf_triag(image, zBuffer, punt1, punt2, punt3, schaalfactor, dx, dy, kleur);
        }
    }
    return image;
}

void draw_zbuf_triag(img::EasyImage &image, ZBuffer &zbuffer, const Vector3D &A, const Vector3D &B, const Vector3D &C, double d,
                                     double dx, double dy, img::Color &color) {

    Point2D _A;
    _A.x = (d*A.x/-A.z)+dx;
    _A.y = (d*A.y/-A.z)+dy;

    Point2D _B;
    _B.x = (d*B.x/-B.z)+dx;
    _B.y = (d*B.y/-B.z)+dy;

    Point2D _C;
    _C.x = (d*C.x/-C.z)+dx;
    _C.y = (d*C.y/-C.z)+dy;

    vector<Point2D> puntenDriehoek; // vector die de geprojecteerde punten bevat
    puntenDriehoek.push_back(_A);
    puntenDriehoek.push_back(_B);
    puntenDriehoek.push_back(_C);

    //bepalen Ymin en Ymax

    int Ymin = roundToInt(min({_A.y, _B.y, _C.y})+0.5); // https://stackoverflow.com/questions/9424173/find-the-smallest-amongst-3-numbers-in-c
    int Ymax = roundToInt(max({_A.y, _B.y, _C.y})-0.5);

    double posInf = numeric_limits<double>::infinity();
    double negInf = -numeric_limits<double>::infinity();

    //zwaartepunt
    Point2D zwaartepunt;
    zwaartepunt.x = (_A.x+_B.x+_C.x)/3;
    zwaartepunt.y = (_A.y+_B.y+_C.y)/3;
    double _1opZ_G = (1/(3*A.z))+(1/(3*B.z))+(1/(3*C.z)); // 1 over Z waarde van zwaartepunt

    // berekening dzdx en dzdy
    Vector3D u = B - A;
    Vector3D v = C - A;
    Vector3D w = Vector3D::cross(u,v);
    double k = (w.x*A.x) + (w.y*A.y) + (w.z*A.z); // rond cursus 45
    double dzdx = w.x/(-d*k);
    double dzdy = w.y/(-d*k);

    double xI;
    for (int i = Ymin; i <= Ymax; i++) { // elke y waarde doorlopen

        double xL_AB = posInf;
        double xL_AC = posInf;
        double xL_BC = posInf;
        double xR_AB = negInf;
        double xR_AC = negInf;
        double xR_BC = negInf;

        if ((i-_A.y)*(i-_C.y) <= 0 && _A.y != _C.y) { // AC
            xI = _C.x + ((_A.x-_C.x)*((i-_C.y)/(_A.y-_C.y)));
            xL_AC = xI;
            xR_AC = xI;
        }
        if ((i-_A.y)*(i-_B.y) <= 0 && _A.y != _B.y) { // AB
            xI = _B.x + ((_A.x-_B.x)*((i-_B.y)/(_A.y-_B.y)));
            xL_AB = xI;
            xR_AB = xI;
        }
        if ((i-_B.y)*(i-_C.y) <= 0 && _B.y != _C.y) { // BC
            xI = _C.x + ((_B.x-_C.x)*((i-_C.y)/(_B.y-_C.y)));
            xL_BC = xI;
            xR_BC = xI;
        }

        int xLmin = roundToInt(min({xL_AB, xL_BC, xL_AC})+0.5);
        int xRmax = roundToInt(max({xR_AB, xR_BC, xR_AC})-0.5);
        for (int j = xLmin; j <= xRmax; j++) { // elke x waarde doorlopen van xLmin tot xRmax
            double _1opZ = (_1opZ_G*1.0001) + ((j-zwaartepunt.x)*dzdx) + ((i-zwaartepunt.y)*dzdy); // formule dia 12 (ppt) , moet 1.0001 daar staan?

            if (_1opZ < zbuffer.pixelArray[j][i]) {
                (image)(j, i) = color;
                zbuffer.pixelArray[j][i] = _1opZ;
            }
        }
    }
}
