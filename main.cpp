#include <iostream>
#include "Importer.h"

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Maksim.h"
#include "engine/engine.h"

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {

    Datastructuur datastructuur;
    Importer::readXMLFile("../xmlfiles/test1.xml", datastructuur);
    return 0;

}
