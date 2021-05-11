#include <iostream>
#include "Importer.h"
#include "Brzozowski.h"

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {


    //importerTests
//    for (int i = 1; i < 51; ++i)
//    {
//        Datastructuur datastructuur;
//        string path = "../xmlfiles/importerTest" + to_string(i) + ".xml";
//        Importer::readXMLFile(path, datastructuur);
//        datastructuur.inorderTraversal();
//        cout << endl << endl;
//    }


    long time;
    DFA dfa = DFA("../TestenBrzozowski/OorspronkelijkeFile.json");
    Brzozowski::brzozowskiAlgorithm(dfa, time);
    cout << "Eerste tijd: " << time << " microseconden" << endl;

    DFA dfa2 = DFA("../TestenBrzozowski/Test2.json");
    Brzozowski::brzozowskiAlgorithm(dfa2, time);
    cout << "Tweede tijd: " << time << " microseconden" << endl;

    DFA dfa3 = DFA("../TestenBrzozowski/Test3.json");
    dfa3.minimize(time);
    cout << "Derde tijd: " << time << " microseconden" << endl;

    DFA dfa4 = DFA("../TestenBrzozowski/Test4.json");
    dfa4.minimize(time);
    cout << "Vierde tijd: " << time << " microseconden" << endl;

    return 0;
}
