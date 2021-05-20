//
// Created by Cem Tuncay on 09/05/2021.
//

#include "Dzhem.h"

bool controleSysteem(string& re, Datastructuur &bestemmingen, vector<long>& timeBrz, vector<long>& timeTFA,
                     vector<long>& memoryBrz, vector<long>& memoryTFA) {
    RE newRE = RE(re, 'e');
    DFA dfaRE = newRE.toDFA();
    dfaRE.renameStates();
    DFA dfaReTFA = DFA(dfaRE);
    Brzozowski::brzozowskiAlgorithm(dfaRE, timeBrz);
    dfaRE.getMemory(memoryBrz);
    ofstream json;
    json.open("../controlesysteem.json");
    dfaReTFA.print(json);
    json.close();
    TFA* tfa = new TFA("../controlesysteem.json");
    tfa->minimize(timeTFA);
    dfaReTFA = tfa->toDFA();
    dfaReTFA.getMemory(memoryTFA);

    vector<Bestemming*> haltes;
    bestemmingen.inorderTraversal(haltes);
    vector<long> halteRE;
    for (int i = 0; i<haltes.size(); i++){
        auto halte  = haltes.at(i);
        RE reHalte = RE(halte->getRegex(), 'e');
        DFA dfaHalte = reHalte.toDFA();
        dfaHalte.renameStates();
        //Pruductautomaat van de twee met doorsnede van de accepterende staten.
        DFA doorsnede = DFA(dfaRE, dfaHalte, true);
        vector<string> statesDoornsede = doorsnede.getAllStates();
        for (auto state:statesDoornsede){ //Controle of de productautomaat met de doorsnede een accepterende staat bevat
            if(doorsnede.isStateAccepting(state)){
                for (int k=0; k<i; k++){
                    timeTFA.pop_back();
                }
                return false;
            }
        }
    }
    return true;
}
