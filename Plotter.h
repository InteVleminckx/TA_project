//
// Created by inte.vleminckx on 11/05/2021.
//
// De javascript code om de grafieken te genereren heb ik gevonden op: https://canvasjs.com/

#ifndef PROJECTTA_PLOTTER_H
#define PROJECTTA_PLOTTER_H
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Plotter
{

    ofstream plot;

    /**
     * Deze maakt de html aan
     * @param TFA: de snelheidswaardes van het Table filling algorithm
     * @param BRZ: de snelheidswaardes van het Brzozoswki algorithm
     */
    void createHTML(vector<double> &TFA, vector<double> &BRZ);

    /**
     * Bepaald de coordinaten voor de punten op de grafiek te zetten
     * @param points: de snelheidswaardes van het Table filling algorithm of Brzozoswki algorithm
     */
    void createCoordinates(vector<double> &points);

public:

    /**
     * Constructor van de plotter
     * @param TFA: de snelheidswaardes van het Table filling algorithm
     * @param BRZ: de snelheidswaardes van het Brzozoswki algorithm
     */
    Plotter(vector<double> &TFA, vector<double> &BRZ);

};


#endif //PROJECTTA_PLOTTER_H
