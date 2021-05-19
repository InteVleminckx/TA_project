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
#include "Barcode.h"
#include "Datastructuur.h"
#include "Plotter.h"

#include <windows.h>

/**
 * Opmerking: de working directory staat standaard op de cmake-build-debug map, we moeten dus altijd eerst een
 * directory omhoog gaan voordat we aan onze functies en mappen kunnen
 */

int main() {

    vector<long> timeBRZ{1,10,2,5,12,48,45,12};
    vector<long> timeTFA{5,21,18,12,5,18,25,11};
//    DFA dfa1 = DFA("../TestenBrzozowski/Test11.json");
//    Brzozowski::brzozowskiAlgorithm(dfa1, timeBRZ);
//    dfa1.print(cout);
//
////    cout << time << " microseconden" << endl;
//
//    TFA dfa2("../TestenBrzozowski/Test11.json");
//    dfa2.minimize(timeTFA).print(cout);
//
////    cout << time << " microseconden" <<endl;


    string re1 = "(10+(0+1)((0+1))*10)*(0+1)((0+1))*";
//    string re2 = "1001";
//    string re3 = "(1+0+1)*";
//    string re4 = "(1+0)(1+00)";
//    string re5 = "1(1+0)";
//    string re6 = "(100+0)0";
//
    Barcode code;
//

//    for (int i = 0; i < 10; ++i) {
//        srand(time(NULL));
//
//        cout << code.createBarcode(re1) << endl;
//    }

//
//    cout << re2 << endl;
//    code.createBarcode(re2);
//    cout << endl;
//
//    cout << re3 << endl;
//    code.createBarcode(re3);
//    cout << endl;
//
//    cout << re4 << endl;
//    code.createBarcode(re4);
//    cout << endl;
//
//    cout << re5 << endl;
//    code.createBarcode(re5);
//    cout << endl;
//
//    cout << re6 << endl;
//    code.createBarcode(re6);
//    cout << endl;
//
//    Maksim maksim;
//
//    Datastructuur data;
//    vector<string> haltes = {"aaa", "bbb", "ccc" , "ddd"};
//    for (int i =0; i < 4; i++){
//        string re = maksim.generateRE(data);
//        Bestemming* halte = new Bestemming(haltes.at(i), re);
//        Node* newHalte = new Node(*halte);
//        data.insert(newHalte);
//    }
//    vector<Bestemming*> hhh;
//    data.inorderTraversal(hhh);

    Plotter plot = Plotter(timeTFA, timeBRZ, "Speed");
    Plotter plot1 = Plotter(timeTFA, timeBRZ, "Memory");
    ShellExecute(NULL, "open", "..\\Speedcomparison.html", NULL, NULL, SW_SHOWNORMAL);
    ShellExecute(NULL, "open", "..\\Memorycomparison.html", NULL, NULL, SW_SHOWNORMAL);
    return 0;

//
//    tree.deleteNode("bestemming1");
//
//
//    Bestemming* newBestemming = tree.getBestemming("bestemming2").second;

}
