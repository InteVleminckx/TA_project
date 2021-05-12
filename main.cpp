#include <iostream>
#include "Importer.h"
#include "Brzozowski.h"
#include "Maksim.h"
#include "TFA_Inte/TFA.h"

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {

    long time;
    DFA dfa1 = DFA("../TestenBrzozowski/Test1.json");
    Brzozowski::brzozowskiAlgorithm(dfa1, time);
//    dfa1.print(cout);

//    cout << time << " microseconden" << endl;

    TFA dfa2("../TestenBrzozowski/Test1.json");
//    dfa2.minimize(time).print();

//    cout << time << " microseconden" <<endl;

    return 0;
}
