//
// Created by centu on 24/02/2021.
//

#include "L2Dsysteem.h"
#include <stack>
#include <cstdlib>
#include <time.h>
using namespace std;


list<Line2D> L2Dsysteem::parse(const string& filenaam, vector<double> color) {
    srand (time(NULL));
    LParser::LSystem2D l_system;

    std::ifstream input_stream(filenaam);
    input_stream >> l_system;
    input_stream.close();

    alfabet = l_system.get_alphabet();

    for (auto it = alfabet.begin(); it != alfabet.end(); it++) {
        // we maken 2 mappen: de drawMap bevat telkens de letter met als value of die getekend moet worden of niet (bool)
        // de replacements bevat de string waarin het symbool moet veranderd worden
        char letter = *it;
        drawMap[letter] = l_system.draw(*it);

        replacements[letter] = l_system.get_replacement(*it);
    }

//    for (auto it = alfabet.begin(); it != alfabet.end(); it++) {
//        // we maken 2 mappen: de drawMap bevat telkens de letter met als value of die getekend moet worden of niet (bool)
//        // de replacements bevat de string waarin het symbool moet veranderd worden
//        char letter = *it;
//        drawMap[letter] = l_system.draw(*it);
//        replacements[letter] = l_system.get_replacement(*it);
//    }

    angleDegrees = l_system.get_angle(); // hoek in graden
    angle = angleDegrees*(M_PI/180); // hoek in radialen
    initiator = l_system.get_initiator();
    nr_iterations = l_system.get_nr_iterations();
    startingAngle = l_system.get_starting_angle()*(M_PI/180); // starthoek in radialen

    // dit stuk code hierna zorgt er voor dat we de grenzen kunnen bepalen van de intervallen die
    // nodig zijn om de stochastische replacement rules toe te passen.
    vector<pair<char, vector<pair<string, double>>>> USgrenzen; // UnSorted grenzen
    vector<pair<char, vector<pair<string, pair<double,double>>>>> grenzen; // gesorteerde grenzen
    for (auto it = replacements.begin(); it != replacements.end(); it++) { // alles toevoegen uit replacements map aan USgrenzen
        USgrenzen.emplace_back(it->first, it->second);
    }
    for (auto paar = 0; paar < USgrenzen.size(); paar++) {
        sort(USgrenzen[paar].second.begin(), USgrenzen[paar].second.end(), compMap);
    }
    //sort(USgrenzen.begin(), USgrenzen.end()); // we sorteren USgrenzen zodat de ondergrenzen en bovengrenzen gaan kloppen
    // verder gaan we aan de grenzen map de intervallen toevoegen, en met die intervallen kunnen we dan later werken met
    // een random getal tussen 0 en 1, waarbij we checken in welk interval dit getal zit, en dan de overeenkomstige replacement string nemen.

    double onderGrens = 0;
    char letter = USgrenzen[0].first;
    for (auto p = 0; p < USgrenzen.size(); p++) {
        if (USgrenzen[p].first != letter) {
            letter = USgrenzen[p].first;
            onderGrens = 0;
        }
        for (auto q = 0; q < USgrenzen[p].second.size(); q++) {
            double bovenGrens = USgrenzen[p].second[q].second + onderGrens;
            vector<pair<string, pair<double,double>>> a;
            a.emplace_back(USgrenzen[p].second[q].first,make_pair(onderGrens, bovenGrens));
            grenzen.emplace_back(USgrenzen[p].first, a);
            onderGrens = bovenGrens; // volgend interval => nieuwe ondergrens wordt oude bovengrens
        }

    }

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
                    double rnd = (double) rand() / RAND_MAX;
                    for (auto it = grenzen.begin(); it != grenzen.end(); it++) {
                        if (code[j] == it->first) {
                            for (auto k = 0; k < it->second.size(); k++) {
                                if (it->second[k].second.first < rnd && rnd <= it->second[k].second.second) {
                                    tempstring = it->second[k].first;
                                    break;
                                }
                            }
                        }
                    }
                //tempstring = replacements[code[j]]->second.first; // origineel zonder stoch. repl. rules
            }
            else {
                tempstring = code[j];
            }
            code1 += tempstring;
        }
        code = code1;
    }
    //
    list<Line2D> Lines2D;
    Point2D punt1; punt1.x = 0; punt1.y = 0; // eerste punt start op (0,0)
    Point2D punt2;

    Color kleur;
    kleur.red = color[0]; // niet *255, want dit doen we in de functie die we aanroepen om de lijnen te tekenen
    kleur.blue = color[2];
    kleur.green = color[1];

    stack<pair<Point2D, double>> stack1;

    for (auto c = 0; c < code.size();c++) {

        if (code[c] == '+') {
            startingAngle += angle;
        }
        else if (code[c] == '-') {
            startingAngle -= angle;
        }
        else if (code[c] == '(') {
            stack1.push(make_pair(punt1, startingAngle));
        }
        else if (code[c] == ')') {
            punt1 = stack1.top().first;
            startingAngle = stack1.top().second;
            stack1.pop();
        }
        else {
            punt2.x = punt1.x+cos(startingAngle); // nieuwe x = oude x * cos(hoek)
            punt2.y = punt1.y+sin(startingAngle); // nieuwe y = oude y * sin(hoek)
            if (drawMap[code[c]]) { // als de letter getekend moet worden (bool = true)
                Line2D lijn = Line2D(punt1, punt2, kleur);
                Lines2D.push_back(lijn); // we voegen de lijn toe aan de vector Lines2D
            }
            punt1.x = punt2.x; // oud punt wordt nieuw punt
            punt1.y = punt2.y;
        }

    }
    return Lines2D;
}


