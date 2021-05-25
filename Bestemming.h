//
// Created by Cem Tuncay on 06/05/2021.
//

#ifndef PROJECTTA_BESTEMMING_H
#define PROJECTTA_BESTEMMING_H

#include <string>
#include "AlgoritmesControlesysteem//DFA.h"

using namespace std;

class Bestemming {
private:
    string fNaam;
    string fRegex;
    DFA dfa;
    vector<string> fBarcodes;

public:

    /**
     * Constructor met memebervariabelen.
     * @param naam: Naam van het halte.
     * @param RegEx: Reguliere expressie voor de halte
     */
    Bestemming(string naam, string RegEx);

    /**
     * Default constructor
     */
    Bestemming();

    /**
     * Deze functie stelt de naam in van de halte.
     * @param naam: naam van de halte
     */
    void setName(string naam);

    /**
     * Deze functie geeft de naam van de halte terug.
     * @return: fNaam
     */
    string getName();

    /**
     * Deze functie stelt het RegEx in voor deze halte.
     * @param RegEx: Unieke Regex voor de halte
     */
    void setRegex(string RegEx);

    /**
     * Deze functie geeft de regex van de halte terug.
     * @return
     */
    string getRegex();

    /**
     * Deze functie stelt de geminimaliseerde DFA in voor de bestemming.
     */
    void setDFA(DFA& dfa);

    /**
     * Deze functie geeft een refference naar de DFA van de bestemming.
     * @return: dfa
     */
    DFA& getDFA();

    /**
     * Deze functie voegt een barcode toe aan een vector die alle barcodes bevat voor een bestemming, waarvan een ticket is gekocht.
     * @param barcode: de nieuw gegenereerde barcode die aangemaakt is bij het aankopen van een ticket.
     */
    void setBarcode(string &barcode);

    /**
     * Deze functie geeft een barcode terug uit en verwijderd de barcode uit de vector.
     * @return: string, een barcode.
     */
    string getBarcode();

     /**
     * Deze functie verwijderd een gekochte barcode voor deze bestemming.
     * @param re: te verwijderen barcode
     */
    void deleteBarcode(string re);
};


#endif //PROJECTTA_BESTEMMING_H
