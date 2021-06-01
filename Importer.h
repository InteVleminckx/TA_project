/**
 * Dit is de importerklasse. Het heeft als voornamelijke functie het uitlezen van xml-bestanden en deze in onze
 * eigen gemaakte datastructuur steken.
 * @date: 02/05/2021
 * @version: 1.0
 */

#ifndef PROJECTTA_IMPORTER_H
#define PROJECTTA_IMPORTER_H

#include "txml/tinystr.h"
#include "txml/tinyxml.h"
#include <string>
#include <iostream>
#include "Datastructuur.h"
#include "Bestemming.h"
#include "Maksim.h"

using namespace std;

class Importer {
public:

    /**
     * Deze functie leest een XML-bestand in en voegt de bestemmingen toe aan een datastructuur.
     * @param filename = het XML-bestand.
     * @param datastructure = de Datastructuur waar de bestemmingen moeten worden toegevoegd.
     */
    static void readXMLFile(const string &filename, Datastructuur &datastructure);
};


#endif //PROJECTTA_IMPORTER_H
