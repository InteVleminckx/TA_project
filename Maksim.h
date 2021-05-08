//
// Created by Maksim Karnaukh on 5/05/2021.
//

#ifndef PROJECTTA_MAKSIM_H
#define PROJECTTA_MAKSIM_H
#include <string>
#include <fstream>
#include "vector"

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

    void stringToBarcode(string &str);

    string generateRE();
};


#endif //PROJECTTA_MAKSIM_H
