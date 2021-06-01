//
// Created by Cem Tuncay on 09/05/2021.
//

#include "Dzhem.h"

bool controleSysteem(string& re, Datastructuur &bestemmingen, vector<long>& timeBrz, vector<long>& timeTFA,
                     vector<long>& memoryBrz, vector<long>& memoryTFA, Bestemming& best) {
    RE newRE = RE(re, 'e');
    DFA dfaRE = newRE.toDFA();
    dfaRE.renameStates();
    DFA dfaReTFA = DFA(dfaRE);

    //minimalisatie met Brzozowski
    Brzozowski::brzozowskiAlgorithm(dfaRE, timeBrz);
    dfaRE.getMemory(memoryBrz);

    //minimalisatie met TFA als vergleijking
    ofstream json;
    json.open("controlesysteem.json");
    dfaReTFA.print(json);
    json.close();
    TFA* tfa = new TFA("controlesysteem.json");
    *tfa = tfa->minimize(timeTFA);
    dfaReTFA = tfa->toDFA();
    dfaReTFA.getMemory(memoryTFA);

    vector<Bestemming*> haltes;
    bestemmingen.inorderTraversal(haltes);
    vector<long> halteRE;
    vector<long> temp;
    for (int i = 0; i<haltes.size(); i++){
        auto halte  = haltes.at(i);
        //Pruductautomaat van de twee met doorsnede van de accepterende staten.
        DFA doorsnede = DFA(dfaRE, halte->getDFA(), true);
        vector<string> statesDoornsede = doorsnede.getAllStates();
        for (auto state:statesDoornsede){ //Controle of de productautomaat met de doorsnede een accepterende staat bevat
            if(doorsnede.isStateAccepting(state)){
                return false;
            }
        }
    }
    best.setDFA(dfaRE); //als het eengeldige RE is, wordt de geminimaliseerde DFA opgeslagen bij de bestemming.
    return true;
}
