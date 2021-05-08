//
// Created by centu on 19/02/2021.
//

#ifndef ENGINE_HULPFUNCTIES_H
#define ENGINE_HULPFUNCTIES_H
# define M_PI   3.14159265358979323846 // gevonden op https://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
#include <cmath>
#include <string>
#include <vector>
using namespace  std;

inline int roundToInt(double d) {
    return static_cast<int>(std::round(d));
}

// functie compMap
// gebruikt als comparator in een sort functie
inline bool compMap(pair<string, double>& a,
                    pair<string, double>& b) {
    return a.second < b.second;
}
//double toRadial(double angle) {
//    angle = angle*(M_PI/180);
//    return angle;
//}

#endif //ENGINE_HULPFUNCTIES_H
