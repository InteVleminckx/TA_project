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
     * functie die een string van 0'en en 1'en omzet naar een barcode afbeelding met verticale lijntjes.
     * @param str : string van 0'en en 1'en.
     */
    void stringToBarcode(string &str);

    /**
     * functie die een (willekeurige) regex aanmaakt. De regex bestaat uit volgende formule (van deelregexen) : (R + S + U + T) + S + U + C.
     * Telkens er een regex wordt aangemaakt, wordt eerst gecheckt of de
     * doorsnede met de bestaande regexen leeg is. Als de regex niet goed is, dan wordt de functie nog eens aangeroepen,
     * maar wel met de parameter aantalBewerkingen vergroot met +1.
     * @param data : (Datastructuur) de datastructuur die de bestemmingen bevat
     * @param timeBrz : (vector<long>) vector die de tijden van het minimaliseren met het Brzozowski algoritme bevat.
     * @param timeTFA : (vector<long>) vector die de tijden van het minimaliseren met het TFA bevat.
     * @param memoryBRZ : (vector<long>) vector die het gebruik van memory van het Brzozowski algoritme bevat.
     * @param memoryTFA : (vector<long>) vector die het gebruik van memory van het TFA bevat.
     * @param best : bestemming waaraan we de DFA meegeven die we in de controlesysteem aanmaken
     * @param numberOfIterations : (int) dit bepaalt het aantal bewerkingen voor elke deelregex in onze gehele regex.
     * Bij elke nieuwe aanroep van dezelfde functie, wordt dit vergroot met +1.
     * @return de gegenereerde regex
     */
    string generateRE(Datastructuur& data, vector<long>& timeBrz, vector<long>& timeTFA, vector<long>& memoryBRZ,
                      vector<long>& memoryTFA,Bestemming& best, int numberOfIterations = 0);

    /**
     * functie die een bewerking kiest en een deelregex opstelt voor eerste keer.
     * @param isConcatOnly : boolean die aangeeft of we enkel de concatenatie bewerking gebruiken.
     * @return de gegenereerde deelregex
     */
    string chooseOperationFirstTime(bool isConcatOnly);

    /**
     * functie die een bewerking kiest en een deelregex opstelt, bestaande uit de meegegeven regex en een willekeurige andere deelregex.
     * @param deelRegex : (string) de bestaande deelregex tot nu toe.
     * @param isConcatOnly : boolean die aangeeft of we enkel de concatenatie bewerking gebruiken.
     * @return de gegenereerde deelregex
     */
    string chooseOperation(string &deelRegex, bool isConcatOnly);

    /**
     * dit is de hoofdfunctie die de functies die de bewerkingen kiezen, aanroept.
     * @param nr_iterations : (int) het aantal bewerkingen dat per deelregex moeten uitgevoerd worden.
     * @param isConcatOnly : boolean die aangeeft of we enkel de concatenatie bewerking gebruiken.
     * @return de gegenereerde deelregex
     */
    string getRandomString(int nr_iterations, bool isConcatOnly);

    /**
     * functie die een HTML tabel aanmaakt die de bestemmingen en de overeenkomstige regexen per bestemming laat zien.
     * @param datastructuur : (Datastructuur) de datastructuur die onze bestemmingen bevat.
     */
    static void createHTMLFile(Datastructuur &datastructuur);

//    string minimizeRegex(string &str1);

};


#endif //PROJECTTA_MAKSIM_H