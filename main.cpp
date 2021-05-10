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

    DFA dfa = DFA("../Test1.json");
    Brzozowski::brzozowskiAlgorithm(dfa);

    DFA dfa2 = DFA("../Test2.json");
    Brzozowski::brzozowskiAlgorithm(dfa2);

    return 0;
}
