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
#include "Bestemming.h"
#include "Datastructuur.h"

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {

//    vector<long> times;
//    DFA dfa1 = DFA("../TestenBrzozowski/Test4.json");
//    Brzozowski::brzozowskiAlgorithm(dfa1, times);
//    dfa1.print(cout);
//
//    TFA temp_tfa("../TestenBrzozowski/Test4.json");
//    TFA minimized_TFA = temp_tfa.minimize(times);
//    minimized_TFA.print(cout);
//
//    dfa1.getMemory(times);
//    DFA dfa2 = minimized_TFA.toDFA();
//    dfa2.getMemory(times);
//
//    cout << "Tijd met Brzozowski ==> " << times[0] << " microseconden" << endl;
//    cout << "Tijd met TFA ==> " << times[1] << " microseconden" << endl;
//    cout << "Geheugen DFA met Brzozowski ==> " << times[2] << " bytes" << endl;
//    cout << "Geheugen DFA met TFA ==> " << times[3] << " bytes" << endl;

    Maksim maksim;
    //srand ((int)time(NULL));
    /*for (auto i = 0; i < 10; i++) {
        string re = maksim.generateRE(2);
        cout << re << endl;
        cout << endl;
    }*/

    Datastructuur data;
    vector<string> haltes = {"aaa", "bbb", "ccc" , "ddd"};
    for (int i =0; i < 4; i++){
        string re = maksim.generateRE(data);
        Bestemming* halte = new Bestemming(haltes.at(i), re);
        Node* newHalte = new Node(*halte);
        data.insert(newHalte);
    }
    vector<Bestemming*> hhh;
    data.inorderTraversal(hhh);

    return 0;
}
