//
// Created by Maksim Karnaukh on 5/05/2021.
//

#ifndef PROJECTTA_MAKSIM_H
#define PROJECTTA_MAKSIM_H
#include <iostream>
#include <string>
#include <fstream>
#include "vector"
#include <stdlib.h>
#include <time.h>
#include "DFAtoRE/DFA_Inte.h"

#include "Dzhem.h" //include voor controlesysteem
#include "Datastructuur.h" //tijdelijke include, vervanging woord de dergelijke opslag van de bestemmingen.
using namespace std;

// Zaken die moeten gedaan worden:
// - Omzetten van string geaccepteerd door een RE naar barcode
// - Genereren van een RE

// - feature8: Als bijhorende feature kunnen we wanneer de RE niet geldig is, een geldige RE genereren
//   en deze teruggeven. We kunnen dit doen door telkens de doorsnede te nemen met alle bestaande RE’s en
//   deze allemaal leeg zijn hebben we een nieuwe geldige RE gegenereerd.
// - feature9: We kunnen een functie toevoegen die een overzicht van alle bestemmingen en RE’s weergeeft in een html bestand.

class Maksim {
public:

    /**
     *
     * @param str
     */
    void stringToBarcode(string &str);

    /**
     *
     * @param data
     * @param timeBrz
     * @param timeTFA
     * @param memoryBRZ
     * @param memoryTFA
     * @param best
     * @param numberOfIterations
     * @return
     */
    string generateRE(Datastructuur& data, vector<long>& timeBrz, vector<long>& timeTFA, vector<long>& memoryBRZ,
                      vector<long>& memoryTFA,Bestemming& best, int numberOfIterations = 0);

    /**
     *
     * @param isConcatOnly
     * @return
     */
    string chooseOperationFirstTime(bool isConcatOnly);

    /**
     *
     * @param deelRegex
     * @param isConcatOnly
     * @return
     */
    string chooseOperation(string &deelRegex, bool isConcatOnly);

    /**
     *
     * @param nr_iterations
     * @param isConcatOnly
     * @return
     */
    string getRandomString(int nr_iterations, bool isConcatOnly);

    /**
     *
     * @param datastructuur
     */
    static void createHTMLFile(Datastructuur &datastructuur);

//    string minimizeRegex(string &str1);



};

#include "DFAtoRE/DFA_Inte.h"

#endif //PROJECTTA_MAKSIM_H
