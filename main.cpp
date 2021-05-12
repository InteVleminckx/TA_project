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

//    long time;
//    DFA dfa1 = DFA("../TestenBrzozowski/Test1.json");
//    Brzozowski::brzozowskiAlgorithm(dfa1, time);
//    dfa1.print(cout);

//    cout << time << " microseconden" << endl;

//    TFA dfa2("../TestenBrzozowski/Test1.json");
//    dfa2.minimize(time).print();

//    cout << time << " microseconden" <<endl;

    DFA test("../TestenBrzozowski/reachableTest.json");
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                        test.getStates().at(test.getStartState()),
                                        test.getStates().at("1"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("2"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("3"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("5"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("7"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("8"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("10"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("11"), test.getAlphabet()) << endl;
    cout << Brzozowski::isStateReachable(test.getStates().at(test.getStartState()),
                                         test.getStates().at(test.getStartState()),
                                         test.getStates().at("12"), test.getAlphabet()) << endl;


    return 0;
}
