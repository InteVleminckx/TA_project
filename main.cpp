#include <iostream>
#include "Importer.h"
#include "Brzozowski.h"
#include "Maksim.h"

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

    // Brzozowski en TFA Tests
//    long time;
//    DFA dfa = DFA("../TestenBrzozowski/Test1.json");
//    Brzozowski::brzozowskiAlgorithm(dfa, time);
//    cout << "Eerste tijd: " << time << " microseconden" << endl;
//
//    DFA dfa2 = DFA("../TestenBrzozowski/Test2.json");
//    Brzozowski::brzozowskiAlgorithm(dfa2, time);
//    cout << "Tweede tijd: " << time << " microseconden" << endl;
//
//    DFA dfa3 = DFA("../TestenBrzozowski/Test1.json");
//    dfa3.minimize(time);
//    cout << "Derde tijd: " << time << " microseconden" << endl;
//
//    DFA dfa4 = DFA("../TestenBrzozowski/Test2.json");
//    dfa4.minimize(time);
//    cout << "Vierde tijd: " << time << " microseconden" << endl;

    // Barcode Maksim tests
    /// Opmerking: figuren hun afmetingen veranderen niet wanneer er meer dan 16 bits zijn
    /// steeds 15, 36, 0.25
//    Maksim kaas;
//    string barcode1 = "0101010101";
//    string barcode2 = "0011001100";
//    string barcode3 = "0000011111";
//    string barcode4 = "000000";
//    string barcode5 = "1111111";
//    string barcode6 = "01";
//    string barcode7 = "101010101010101010101010101010101010101010";
//    string barcode8 = "000111000111";
//    string barcode9 = "00110011";
//    string barcode10 = "00110011";
//    kaas.stringToBarcode(barcode1);
//    kaas.stringToBarcode(barcode2);
//    kaas.stringToBarcode(barcode3);
//    kaas.stringToBarcode(barcode4);
//    kaas.stringToBarcode(barcode5);
//    kaas.stringToBarcode(barcode6);
//    kaas.stringToBarcode(barcode7);
//    kaas.stringToBarcode(barcode8);
//    kaas.stringToBarcode(barcode9);
//    kaas.stringToBarcode(barcode10);

    long time;
    DFA dfa1 = DFA("../TestenBrzozowski/input-tfa4.json");
    Brzozowski::brzozowskiAlgorithm(dfa1, time);
    dfa1.print(cout);

    cout << time << " microseconden" << endl;

    TFA dfa2("../TestenBrzozowski/input-tfa2.json");
    dfa2.minimize(time).print();

    cout << time << " microseconden" <<endl;

    return 0;
}
