//
// Created by intev on 3/03/2021.
//

#include "RE_Inte.h"


void RE_Inte::makeRE(const vector<string> &xalfabet, const vector<vector<string>> &xtransTable, const string &xfinaleState,const string &xstartState) {

    resetAllVar();

    finaleState = xfinaleState;

    if (!finaleState.empty()){

        alfabet = xalfabet;
        transTable = xtransTable;

        startState = xstartState;

        if (REGEX.empty()){
            REGEX = createREGEX();
        }

        else{
            REGEX += "+" + createREGEX();
        }
    }

}

string RE_Inte::createREGEX() {

    //stellen eerst een nieuwe DFA op met enkel 1 startstate
    complTransTable.push_back(alfabet);
    for (const auto & i : transTable) {complTransTable.push_back(i);}

    //we maken een vector aan die alle states bevat
    //en een die enkel de states bevat die geelimineerd moeten worden
    for (auto & i : complTransTable) {
        //de start state en de finale state mogen niet geelimineerd worden
        //de " " hoort er ook niet bij want deze heb ik er gewoon aan toegevoegd
        //om de table gelijk te laten lopen
        if (i[0] != startState && i[0] != finaleState && i[0] != " "){
            statesToElemin.push_back(i[0]);
        }
        if (i[0] != " "){allStates.push_back(i[0]);}
    }

    //maken een map aan die elke transitie bevat
    for (auto & allState : allStates) {createMap(allState);}

    //zolang er meer states zijn dan 2 moeten er states worden geelimineerd
    while (transitions.size() > 2){
        //zoeken naar de eerste state die we gaan elimineren
        string stateToEliminate = getStateToEliminate();

        //we moeten nu de state gaan elimineren
        eleminateState(stateToEliminate);
    }

    if (transitions.size() == 2){
        twoToRE();
    }


    if (startState == finaleState){
        startIsFinal();
    }


    for (auto & transition : transitions) {
        for (auto & i : transition.second) {
            string trns = i.second;
            if (transHasOpperator(trns)){
                i.second = "(" + trns + ")";
            }
        }
    }

    mapToRegex();

    return dfaToRegex;
}

void RE_Inte::createMap(string &state) {

    vector<string> rowState;

    for (auto & i : transTable) {
        if (state == i[0]){rowState = i;}
    }

    for (int i = 1; i < rowState.size(); ++i) {

        pair<bool, int> exist = pairExistAlready(rowState[i], state);

        if (exist.first){
            string addedState = "+";
            addedState += alfabet[i];
            transitions[state][exist.second].second +=  addedState;
        }
        else{
            transitions[state].push_back(make_pair(rowState[i], alfabet[i]));
        }
    }

    for (auto & allState : allStates) {
        bool foundState = false;
        for (auto & trans : transitions) {
            for (auto & i : trans.second) {
                if (i.first == allState){foundState = true; break;}
            }
            if (!foundState){transitions[state].push_back(make_pair(allState, ""));}
            foundState = false;
        }
    }



}

string RE_Inte::getStateToEliminate() {
    //we sorteren de statesToElemin zodat deze alfabetisch of op numerieke volgorde
    //worden geelimineerd
    sort(statesToElemin.begin(), statesToElemin.end());
    return statesToElemin[0];
}

void RE_Inte::eleminateState(string &stateToEliminate) {

    for (auto &transition : transitions){
        for (auto & pair : transition.second) {
            if (transition.first != stateToEliminate && pair.first != stateToEliminate &&
                !pair.first.empty() ){

                addTransitons(transition.first, pair.first,stateToEliminate);
            }
//            else if (transition.first != stateToEliminate && pair.first != stateToEliminate &&
//                     !pair.first.empty() && pair.first == transition.first){
//                 createKleene(transition.first, pair.first);
//            }


        }
    }

    removeEliminatedStateOutMap(stateToEliminate);

}

void RE_Inte::addTransitons(const string &from, string &to, string &stateToEliminate) {

    vector<pair<string, string>> vectorFrom = transitions.find(from)->second;
    vector<pair<string, string>> vectorEliState = transitions.find(stateToEliminate)->second;

    string trans;
    bool foundTrans = false;

    //als de state die geelimineerd wordt naar zich eigen een transitie heeft
    //dan wordt de transitie omhaakt en een kleene star toegevoegd
    for (auto & i : vectorEliState) {
        if (i.first == stateToEliminate && !i.second.empty()){
            string newString = "(";
            newString += i.second;
            newString += ")*";
            trans+=newString;

        }
    }

    //als de state die geelimineerd wordt een transitie heeft naar de state waar we op dat moment
    //naar toe willen gaan om de huidige state te elimineren
    //dan wordt er een bool op true gezet en wordt de transitie achteraan de vorige berekende transitie
    //toegevoegd
    for (auto & i : vectorEliState) {
        if (i.first == to && !i.second.empty()){
            trans += i.second;
            foundTrans = true;
        }
    }


    string newTrans;
    //We kijken of de transitie op dit moment al een operator bevat
    //zoja
    //dan zetten we hier eerst haakjes rond
    //want we gaan deze transitie concateneren met de transitie die uit een state vertrekt
    bool hasOpperator = transHasOpperator(trans);

    //we kijken eerst of er wel een transitie is van de state naar de state die geelimineerd wordt
    //als er geen transitie is gevonden
    //dan blijft de string die we hebben aangemaakt ook leeg
    //want dat betekent dat als we de state elimineren dit geen invloed heeft
    //op de states die op het moment from en to heten
    if (foundTrans){
        for (auto & i : vectorFrom) {
            if (i.first == stateToEliminate && !hasOpperator && !i.second.empty()){
                newTrans = i.second + trans;
                break;
            }
            else if (i.first == stateToEliminate && hasOpperator && !i.second.empty()){
                newTrans = i.second + "(" + trans + ")";
                break;
            }

        }
    }

    //we hebben dus gezocht of er een transitie is die bestaat van from naar to door de state die
    //geelimineerd wordt

    //als dat wel het geval is
    //gaan we de transitie van deze states aanpassen
    if (!newTrans.empty()){
        int locTo = 0;

        //we zoeken eerst in onze vector op welke postie de transitie van from naar to staat
        for (int i = 0; i < vectorFrom.size(); ++i) {
            if (vectorFrom[i].first == to){
                locTo = i;
                break;
            }
        }

        //als er op die positie nog geen transitie bestond dan stellen we daar de nieuwe transitie gewoon
        //aan gelijk
        if (transitions.find(from)->second[locTo].second.empty()){
            transitions.find(from)->second[locTo].second = newTrans;
        }

        //als er al wel een transitie bestond dan hebben we meerdere mogelijkheden om van de ene state
        //naar de andere state te gaan dus zetten we een + tussen de 2 transities
        else{
            string tempString = transitions.find(from)->second[locTo].second;
            transitions.find(from)->second[locTo].second = "(" + tempString + "+" + newTrans + ")";
        }

    }
}

pair<bool, int> RE_Inte::pairExistAlready(string &from, string &state) {


    if (transitions.empty()){return make_pair(false, 0);}

    if (!transitions.count(state)){return make_pair(false, 0);}

    vector<pair<string, string>> vectorState = transitions.find(state)->second;
    for (int i = 0; i < vectorState.size(); ++i) {
        if (vectorState[i].first == from){
            return make_pair(true, i);
        }
    }
    return make_pair(false, 0);
}

void RE_Inte::removeEliminatedStateOutMap(string &stateToEliminate) {

    transitions.erase(stateToEliminate);

    for (auto & transition : transitions) {
        for (int i = 0; i < transition.second.size(); ++i) {
            if (transition.second[i].first == stateToEliminate){
                transition.second.erase(transition.second.begin()+i);
            }
        }
    }

    statesToElemin.erase(statesToElemin.begin());

    for (int i = 0; i < allStates.size(); ++i) {

        if (allStates[i] == stateToEliminate){
            allStates.erase(allStates.begin() + 1);
        }

    }


}

//void RE::createKleene(const string &from, string &to) {
//
//    vector<pair<string, string>> vectorFrom = transitions.find(from)->second;
//
//    string transition;
//    int locTo = 0;
//
//    for (int i = 0; i < vectorFrom.size(); ++i) {
//
//        if (vectorFrom[i].first == to){
//            locTo = i;
//            transition = vectorFrom[i].second;
//        }
//    }
//
//    if (allAddedKleenes.empty() && !transition.empty()){
//
//        string tempString = transitions.find(from)->second[locTo].second;
//        tempString = "(" + tempString + ")*";
//        transitions.find(from)->second[locTo].second = tempString;
//        allAddedKleenes.push_back(tempString);
//    }
//
//    else if (!transition.empty()){
//
//        string tempString = transitions.find(from)->second[locTo].second;
//        tempString = "(" + tempString + ")*";
//        bool exist = false;
//
//        for (auto & allAddedKleene : allAddedKleenes){
//            if (allAddedKleene == transition){
//                exist = true;
//                break;
//            }
//        }
//        if (!exist){
//            transitions.find(from)->second[locTo].second = tempString;
//            allAddedKleenes.push_back(tempString);
//        }
//    }
//}

bool RE_Inte::transHasOpperator(string &trans) {

    bool open = false;
    bool returnBool = false;

    for (char tran : trans) {

        //komen een hakje tegen zetten open op true
        if (tran == '('){open = true;}

            //als we een gesloten haakje tegen komen zetten we de bool op closed
        else if (tran == ')'){open = false; returnBool = false;}

            //als we een + tegen komen maar er geen haakje open is geweest
            //betekent dat het nog niet tussen haakjes staat dus er is een opperator
        else if (tran == '+' && !open){returnBool = true;}
    }

    return returnBool;
}

void RE_Inte::mapToRegex() {

    for (auto & transition : transitions) {
        if (transition.first == startState){
            for (auto & i : transition.second){
                if (i.first == startState){
                    R = i.second;
                }
                else if (i.first == finaleState){
                    S = i.second;
                }

            }
        }
        else if (transition.first == finaleState){
            for (auto & i : transition.second){
                if (i.first == startState){
                    T = i.second;
                }
                else if (i.first == finaleState){
                    U = i.second;
                }
            }
        }
    }



    //(R+SU*T)*SU*

    if (!R.empty() && !S.empty() && !U.empty() && !T.empty()){

        if (uHasHaakjes(U)){
            dfaToRegex = "(" + R + "+" + S  + U + "*" + T + ")*" + S   + U + "*";
        }
        else{
            dfaToRegex = "(" + R + "+" + S  + "(" + U + ")*" + T + ")*" + S + "(" + U + ")*";
        }

    }

    else if(!R.empty() && S.empty() && U.empty() && T.empty()){
        dfaToRegex = "(" + R + ")*";
    }


    //RS
    else if(!R.empty() && !S.empty() && U.empty() && T.empty()){

        dfaToRegex =  "(" + R + ")*" + S;
    }
    //RSU
    else if(!R.empty() && !S.empty() && !U.empty() && T.empty()){

        if (uHasHaakjes(U)){
            dfaToRegex = "("+ R + ")*" + S + U + "*";
        }
        else{
            dfaToRegex = "("+ R + ")*" + S + "(" + U + ")*";
        }

    }
    //S
    else if(R.empty() && !S.empty() && U.empty() && T.empty()){
        dfaToRegex = S;
    }
    //SU
    else if(R.empty() && !S.empty() && !U.empty() && T.empty()){

        if (uHasHaakjes(U)){
            dfaToRegex = S + U + "*";
        }
        else{
            dfaToRegex = S + "(" + U + ")*";
        }

    }
    //SUT
    else if(R.empty() && !S.empty() && !U.empty() && !T.empty()){

        if (uHasHaakjes(U)){
            dfaToRegex = "(" + S + U + "*" + T + ")*" + S + U + "*";
        }
        else{
            dfaToRegex = "(" + S + U + "*" + T + ")*" + S + "(" + U + ")*";
        }


    }
    //ST
    else if(R.empty() && !S.empty() && U.empty() && !T.empty()){

        dfaToRegex = "(" + S + T + ")*" + S;

    }



}

void RE_Inte::twoToRE() {


    vector<pair<string, string>> transStart = transitions.find(startState)->second;
    vector<pair<string, string>> transFinal = transitions.find(finaleState)->second;

    bool startCheck1 = false;
    bool finalCheck1 = false;
    bool startCheck2 = true;
    bool finalCheck2 = true;

    int placeFinal = 0;
    int placeLoop = 0;
    int placeStart = 0;

    for (int i = 0; i < transStart.size(); i++){
        if (transStart[i].first == finaleState && !transStart[i].second.empty()){
            startCheck1 = true;
            placeFinal = i;

        }
        if (transStart[i].first == startState){
            placeLoop = i;
        }
        if (transStart[i].first == startState && !transStart[i].second.empty()){
            startCheck2 = false;
        }

    }


    for (int i = 0; i < transFinal.size(); i++){

        if (transFinal[i].first == startState && !transFinal[i].second.empty()){
            finalCheck1 = true;
            placeStart = i;
        }
//        if (transFinal[i].first == finaleState && !transFinal[i].second.empty()){
//            finalCheck2 = false;
//        }

    }

    if (startCheck1 && finalCheck1 && startCheck2 && finalCheck2){

        string startToFinal = transitions.find(startState)->second[placeFinal].second;
        string finalToStart = transitions.find(finaleState)->second[placeStart].second;
        transitions.find(finaleState)->second[placeStart].second = "";

        if (transitions.find(startState)->second[placeLoop].second.empty()){
            transitions.find(startState)->second[placeLoop].second = startToFinal + finalToStart;
        }

        else{
            string Loop = transitions.find(startState)->second[placeLoop].second;

            transitions.find(startState)->second[placeLoop].second = "(" + Loop + " + " + startToFinal + finalToStart + ")";

        }


    }


}

void RE_Inte::print() {

    cout << REGEX << endl;

}

void RE_Inte::resetAllVar() {

    complTransTable.clear();
    allStates.clear();
    statesToElemin.clear();
    alfabet.clear();
    transTable.clear();
    finaleState = "";
    startState = "";
    allAddedKleenes.clear();
    transitions.clear();
    R = "";
    S = "";
    U = "";
    T = "";
    dfaToRegex = "";

}

bool RE_Inte::uHasHaakjes(string &Uu) {

    char first;
    char last;

    for (int i = 0; i < Uu.size(); ++i) {
        if (i == 0){
            first = Uu[i];
        }
        if (i == Uu.size()-1){
            last = Uu[i];
        }
    }

    if (first == '(' && last == ')'){return true;}
    return false;
}

void RE_Inte::startIsFinal() {

    vector<pair<string, string>>  transitionsStart = transitions[startState];
    vector<pair<string, string>>  transitionsOtherState;

    string otherState;
    //als er een transitie is van de start en final naar de andere state moeten we nog
    //een deel aan de RE toevoegen

    //anders kan de state gewoon weg vallen en heeft dit geen invloed

    //nemen de transities van de andere state
    for (auto & state : allStates) {
        if (state != startState){
            transitionsOtherState = transitions[state];
            otherState = state;
        }
    }

    bool startHasTransToOtherState = false;
    bool otherStateHasTransToStartState = false;

    for (auto & trans : transitionsStart) {
        if (trans.first == otherState && !trans.second.empty()){
            startHasTransToOtherState = true;
            break;
        }
    }

    for (auto & trans : transitionsOtherState) {
        if (trans.first == startState && !trans.second.empty()){
            otherStateHasTransToStartState = true;
            break;
        }
    }

    //ze hebben een transitie naar elkaar
    if (startHasTransToOtherState && otherStateHasTransToStartState){
        string newTransitions;

        string startToStart;
        string startToOther;
        string otherToOther;
        string otherToStart;

        for (auto trans : transitions) {

            if (trans.first == startState && trans.second[0].first == startState && !trans.second[0].second.empty()){
                startToStart = trans.second[0].second;
            }

            if (trans.first == startState && trans.second[1].first == startState && !trans.second[1].second.empty()){
                startToStart = trans.second[1].second;
            }

            if (trans.first == startState && trans.second[0].first == otherState && !trans.second[0].second.empty()){
                startToOther = trans.second[0].second;
            }

            if (trans.first == startState && trans.second[1].first == otherState && !trans.second[1].second.empty()){
                startToOther = trans.second[1].second;
            }

            if (trans.first == otherState && trans.second[0].first == otherState && !trans.second[0].second.empty()) {
                otherToOther = trans.second[0].second;
            }

            if (trans.first == otherState && trans.second[1].first == otherState && !trans.second[1].second.empty()){
                otherToOther = trans.second[1].second;
            }

            if (trans.first == otherState && trans.second[0].first == startState && !trans.second[0].second.empty()){
                otherToStart = trans.second[0].second;
            }

            if (trans.first == otherState && trans.second[1].first == startState && !trans.second[1].second.empty()){
                otherToStart = trans.second[1].second;
            }
        }


        if (transHasOpperator(startToStart)){
            startToStart = "(" + startToStart + ")";
        }

        if (transHasOpperator(startToOther)){
            startToOther = "(" + startToOther + ")";
        }

        if (transHasOpperator(otherToStart)){
            otherToStart = "(" + otherToStart + ")";
        }

        if (transHasOpperator(otherToOther)){
            otherToOther = "(" + otherToOther + ")";
        }

        if (!startToStart.empty() && !startToOther.empty() && !otherToOther.empty() && !otherToStart.empty()){
            newTransitions =  startToStart + "+" + startToOther + "(" + otherToOther + ")*" + otherToStart;
        }
        else if (!startToStart.empty() && !startToOther.empty() && otherToOther.empty() && !otherToStart.empty()){
            newTransitions =  startToStart + "+" + startToOther + otherToStart;
        }
        else if (startToStart.empty() && !startToOther.empty() && !otherToOther.empty() && !otherToStart.empty()){
            newTransitions =  startToOther + "(" + otherToOther + ")*" + otherToStart;
        }
        else if (startToStart.empty() && !startToOther.empty() && otherToOther.empty() && !otherToStart.empty()){
            newTransitions =  startToOther + otherToStart;
        }


        for (int i = 0; i < transitions[startState].size(); ++i) {
            if (transitions[startState][i].first == startState){
                transitions[startState][i].second = newTransitions;
            }
        }
    }

    removeEliminatedStateOutMap(otherState);

}











