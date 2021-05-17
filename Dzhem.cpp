//
// Created by Cem Tuncay on 09/05/2021.
//

#include "Dzhem.h"

bool controleSysteem(string& re, Datastructuur &bestemmingen) {
    RE newRE = RE(re, 'e');
    DFA dfaRE = newRE.toDFA();
    dfaRE.renameStates();

    vector<Bestemming> haltes;
    bestemmingen.inorderTraversal(haltes);

    for (auto halte:haltes){
        RE reHalte = RE(halte.getRegex(), 'e');
        DFA dfaHalte = reHalte.toDFA();
        //Pruductautomaat van de twee met doorsnede van de accepterende staten.
        DFA doorsnede = DFA(dfaRE, dfaHalte, true);
        vector<string> statesDoornsede = doorsnede.getAllStates();
        for (auto state:statesDoornsede){ //Controle of de productautomaat met de doorsnede een accepterende staat bevat
            if(doorsnede.isStateAccepting(state)){
                return false;
            }
        }
    }
    return true;
}
