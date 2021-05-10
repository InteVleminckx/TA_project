#include <iostream>
#include "Importer.h"
#include "Brzozowski.h"

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {


    //importerTests
    for (int i = 1; i < 51; ++i)
    {
        Datastructuur datastructuur;
        string path = "../xmlfiles/importerTest" + to_string(i) + ".xml";
        Importer::readXMLFile(path, datastructuur);
        datastructuur.inorderTraversal();
        cout << endl << endl;
    }




//    DFA dfa = DFA("../TestenBrzozowski/Test1.json");
//    Brzozowski::brzozowskiAlgorithm(dfa);
//
//    DFA dfa2 = DFA("../TestenBrzozowski/Test2.json");
//    Brzozowski::brzozowskiAlgorithm(dfa2);

    return 0;
}
