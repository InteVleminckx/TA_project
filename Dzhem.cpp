//
// Created by Cem Tuncay on 09/05/2021.
//

#include "Dzhem.h"

bool statechecker(DFA& dfa){
    for (auto state:dfa.getAllStates()){
        if(dfa.stateGoesTo(state, '1') == "none" or dfa.stateGoesTo(state, '0') == "none"){
            return true;
        }
    }
    return false;
}

bool controleSysteem(string& re, Datastructuur &bestemmingen, vector<long>& timeBrz, vector<long>& timeTFA,
                     vector<long>& memoryBrz, vector<long>& memoryTFA) {
    RE newRE = RE(re, 'e');
    DFA dfaRE = newRE.toDFA();
    dfaRE.renameStates();
    DFA dfaReTFA = DFA(dfaRE);
    Brzozowski::brzozowskiAlgorithm(dfaRE, timeBrz);
    dfaRE.getMemory(memoryBrz);
    ofstream json;
    json.open("controlesysteem.json");
    dfaReTFA.print(json);
    json.close();
    TFA* tfa = new TFA("controlesysteem.json");
    tfa->minimize(timeTFA);
    dfaReTFA = tfa->toDFA();
    dfaReTFA.getMemory(memoryTFA);
    vector<Bestemming*> haltes;
    bestemmingen.inorderTraversal(haltes);
    vector<long> halteRE;
    for (int i = 0; i<haltes.size(); i++){
        auto halte  = haltes.at(i);
        if (halte->getName() == "Antoing"){

        }
        RE reHalte = RE(halte->getRegex(), 'e');
        DFA dfaHalte = reHalte.toDFA();
        if (statechecker(dfaHalte)){
            cout << endl;
        }
        dfaHalte.renameStates();
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
