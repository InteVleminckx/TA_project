#include <iostream>
#include "Importer.h"
#include "Brzozowski.h"

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {

//    Datastructuur datastructuur;
//    Importer::readXMLFile("../xmlfiles/test1.xml", datastructuur);
//    datastructuur.inorderTraversal();

    DFA dfa = DFA("../DFA.json");
    Brzozowski::brzozowskiAlgorithm(dfa);

    return 0;

}
