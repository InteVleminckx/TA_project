#include <iostream>
#include "Importer.h"
#include "Brzozowski.h"
#include "Maksim.h"
#include "TFA_Inte/TFA.h"

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

    long time;
    DFA dfa1 = DFA("../TestenBrzozowski/OorspronkelijkeFile.json");
    Brzozowski::brzozowskiAlgorithm(dfa1, time);
    dfa1.print(cout);

//    cout << time << " microseconden" << endl;

    TFA dfa2("../TestenBrzozowski/OorspronkelijkeFile.json");
    dfa2.minimize(time).print();

//    cout << time << " microseconden" <<endl;

    return 0;
}
