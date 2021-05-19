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
     * @param vergelijkingsType: type van de vergelijking -> snelheid of memory
     */
    void createHTML(vector<long> &TFA, vector<long> &BRZ, string &vergelijkingsType);

    /**
     * Bepaald de coordinaten voor de punten op de grafiek te zetten
     * @param points: de snelheidswaardes van het Table filling algorithm of Brzozoswki algorithm
     */
    void createCoordinates(vector<long> &points);

    /**
     * Deze functie maakt de table aan met alle tijden
     * @param TFA: de snelheidswaardes van het Table filling algorithm
     * @param BRZ: de snelheidswaardes van het Brzozoswki algorithm
     */
    void createTable(vector<long> &TFA, vector<long> &BRZ);

public:

    /**
     * Constructor van de plotter
     * @param TFA: de snelheidswaardes van het Table filling algorithm
     * @param BRZ: de snelheidswaardes van het Brzozoswki algorithm
     * @param vergelijkingsType: type van de vergelijking -> snelheid of memory
     */
    Plotter(vector<long> &TFA, vector<long> &BRZ, string vergelijkingsType);

};


#endif //PROJECTTA_PLOTTER_H
