//
// Created by jonas on 9/05/21.
//

#ifndef PROJECTTA_BRZOZOWSKI_H
#define PROJECTTA_BRZOZOWSKI_H

#include "Datastructuur.h"

using namespace std;

class DFA;

class Brzozowski {
public:
    static void brzozowskiAlgorithm(DFA &productAutomaat);
    static void reversal(DFA &productAutomaat);
    // Extra functie van NFA naar DFA = subsetconstruction toevoegen
};


#endif //PROJECTTA_BRZOZOWSKI_H
