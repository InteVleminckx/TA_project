//
// Created by centu on 19/02/2021.
//

#include "Lsysteem.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Line2D::Line2D(Point2D punt1, Point2D punt2, Color kleur) {
    p1.x = punt1.x;
    p1.y = punt1.y;
    p2.x = punt2.x;
    p2.y = punt2.y;
    color.red = kleur.red*255;
    color.blue = kleur.blue*255;
    color.green = kleur.green*255;
}

img::EasyImage draw2DLines(const std::list<Line2D> &lines, const int size, const vector<double>& backgroundColor, bool ZBuffering) {

    double Xmax = 0;
    double Xmin = 0;
    double Ymax = 0;
    double Ymin = 0;

    for (auto it = lines.begin(); it != lines.end(); it++) {

        double XMax = std::max(it->p2.x, it->p1.x);
        if (XMax > Xmax) { // als één van de x coordinaten van de nieuwe lijn groter is, wordt dat het nieuwe maximum
            Xmax = XMax;
        }
        double XMin = std::min(it->p1.x, it->p2.x);
        if (XMin < Xmin) { // als één van de x coordinaten van de nieuwe lijn kleiner is, wordt dat het nieuwe minimum
            Xmin = XMin;
        }
        double YMax = std::max(it->p2.y, it->p1.y);
        if (YMax > Ymax) { // als één van de y coordinaten van de nieuwe lijn groter is, wordt dat het nieuwe maximum
            Ymax = YMax;
        }
        double YMin = std::min(it->p1.y, it->p2.y);
        if (YMin < Ymin) { // als één van de y coordinaten van de nieuwe lijn groter is, wordt dat het nieuwe maximum
            Ymin = YMin;
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

    double schaalfactor = 0.95*(ImageX/Xrange);

    double DCx = schaalfactor*((Xmin+Xmax)/2);
    double DCy = schaalfactor*((Ymin+Ymax)/2);
    double dx = ImageX/2 - DCx;
    double dy = ImageY/2 - DCy;

    for (auto it = lines.begin(); it != lines.end(); it++) {
        img::Color kleur;
        kleur.red = it->color.red;
        kleur.blue = it->color.blue;
        kleur.green = it->color.green;

        double punt1X = it->p1.x*schaalfactor + dx;
        double punt1Y = it->p1.y*schaalfactor + dy;
        double punt2X = it->p2.x*schaalfactor + dx;
        double punt2Y = it->p2.y*schaalfactor + dy;

        if (ZBuffering) {
            image.draw_zbuf_line(roundToInt(punt1X), roundToInt(punt1Y), it->z1,
                                 roundToInt(punt2X), roundToInt(punt2Y), it->z2,
                                 kleur, zBuffer);
        }
        else {
            image.draw_line(roundToInt(punt1X), roundToInt(punt1Y),
                            roundToInt(punt2X), roundToInt(punt2Y),
                            kleur);
        }
    }
    return image;
}


