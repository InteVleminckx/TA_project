//
// Created by Cem Tuncay on 06/03/2021.
//

#include "RE.h"

//TODO kleene star fixen
//TODO mss met pair werken

RE::RE(string expr, char epsilon) {
    expressie = expr;
    getAlphabet(expressie, epsilon);
}


void RE::getAlphabet(string& expr, char e) {
    eps = e;
    for(auto c :expr){
        if(isalpha(c) && c != eps && find(alphabet.begin(), alphabet.end(), c) == alphabet.end()){
            alphabet.push_back(c);
        }
        tokens.push_back(c);
    }
}


void RE::parser() {
    int i = 0;
    alphabet = {'0', '1'};

    while(i < tokens.size()){
        auto t = tokens.at(i);
        if(isalnum(t)){ //als het om een character gaat en deze niet epsilon is
            vector<char> subExpr;
            string naamSubExpr;
            while(isalnum(t) or t == '*'){   //Als de character kleenClosed is.
                subExpr.push_back(t);   //t mss weg doen uit if
                naamSubExpr = naamSubExpr + t;
                i++;
                if(i<tokens.size()) {
                    t = tokens.at(i);
                }else{
                    break;
                }
            }
            auto subEnfa = concatenator(subExpr);   //geconcateneerde subENFA.
            if(subENFAs.find(naamSubExpr) == subENFAs.end()) { //Als deze subexpressie no geen subENFA had, een nieuwe key-value pair.
                vector<vector<State_NFA*>> v = {subEnfa};
                subENFAs[naamSubExpr] = v;
                continue;
            }else{  //Anders push_back in destaande vector.
                subENFAs[naamSubExpr].push_back(subEnfa);
                continue;
            }
        }else{
            i++;
        }
    }
}


vector<State_NFA*> RE::getCharENFA(char input) {
    vector<State_NFA*> subENFA;
    nr0fStates++;
    string q = "q" + to_string(nr0fStates);
    State_NFA* state0 = new State_NFA(false, q, false, eps);
    subENFA.push_back(state0);
    nr0fStates++;
    string q1 = "q" + to_string(nr0fStates);
    State_NFA* state1= new State_NFA(false, q1, false, eps);
    state0->addTransition(input, state1); //transitie op de inputchar
    subENFA.push_back(state1);
    return subENFA;
}


vector<State_NFA *> RE::KleeneStar(vector<State_NFA *> subEnfa) {
    //er worden 2 nieuwe staten rond de expressie gezet.
    vector<State_NFA *> KleenStared;
    nr0fStates++;
    string q = "q" + to_string(nr0fStates);
    State_NFA* state0= new State_NFA(false, q, false, eps);
    KleenStared.push_back(state0);
    state0->addTransition(eps, subEnfa.front());
    nr0fStates++;
    KleenStared.insert(KleenStared.end(), subEnfa.begin(), subEnfa.end());
    string q1 = "q" + to_string(nr0fStates);
    State_NFA* state1= new State_NFA(false, q1, false, eps);
    subEnfa.back()->addTransition(eps, state1);
    subEnfa.back()->addTransition(eps, subEnfa.front()); //ster operand
    state0->addTransition(eps, state1); //lege string
    KleenStared.push_back(state1);
    return KleenStared;
}


vector<State_NFA *> RE::concatenator(vector<char> conChar) {
    vector<State_NFA *> concatenated;
    for(int i = 0; i< conChar.size(); i++){
        auto c = conChar.at(i);
        auto c_enfa = getCharENFA(c);
        if(conChar.size()>1 and i != conChar.size()-1 and conChar.at(i+1) == '*'){ //als de char kleenClosed wordt
            auto kleenSub = KleeneStar(c_enfa);
            if(!concatenated.empty()) {
                concatenated.back()->addTransition(eps, kleenSub.at(0));
            }
            concatenated.insert(concatenated.end(), kleenSub.begin(), kleenSub.end());
            i = i + 1;
        }
        else{   //anders wordt er een nieuwe staat achter de geconcateneerde deel.
            if (concatenated.empty()){
                concatenated = c_enfa;
            }else{
                concatenated.back()->addTransition(eps, c_enfa.front());
                concatenated.insert(concatenated.end(), c_enfa.begin(), c_enfa.end());
            }
        }
    }
    return concatenated;
}


vector<State_NFA *> RE::Union(vector<vector<State_NFA *>> subEnfa, bool epsilon, bool kleen) {
    vector<State_NFA *> Unioned;    //vector voor de uiteindelijke unie
    nr0fStates++;
    string q0 = "q" + to_string(nr0fStates);
    nr0fStates++;
    string q1 = "q" + to_string(nr0fStates);
    State_NFA* state0 = new State_NFA(false, q0, false, eps);
    Unioned.push_back(state0);
    State_NFA* state1 = new State_NFA(false, q1, false, eps);
    vector<vector<State_NFA*>> sub_union;   //in geval dat er unie moet worden genomen van meer dan 2 subENFA's.
    if(subEnfa.size()==1){
        return subEnfa.at(0);
    }
    for (int i=0; i<2; i++){ //vebrinden van alle subENFA's met de 2 nieuwe staten.
        auto sub = subEnfa.at(subEnfa.size()-1);
        sub_union.push_back(sub);
        subEnfa.pop_back();
    }
    for (auto sub:sub_union){
        state0->addTransition(eps, sub.at(0));
        sub.at(sub.size()-1)->addTransition(eps, state1);
        Unioned.insert(Unioned.end(), sub.begin(), sub.end());
    }
    Unioned.push_back(state1);
    if (!subEnfa.empty()){  //in geval van meer dan 2 subENFA's.
        subEnfa.push_back(Unioned);
        Unioned = Union(subEnfa, false, false);
    }
    if (kleen){ //als de unio kleenClosed moet worden.
        //2nieuwe staten rond de unie
        nr0fStates++;
        string q3 = "q" + to_string(nr0fStates);
        nr0fStates++;
        string q4 = "q" + to_string(nr0fStates);
        State_NFA* state2 = new State_NFA(false, q3, false, eps);
        state2->addTransition(eps, state0);
        State_NFA* state3 = new State_NFA(false, q4, false, eps);
        state1->addTransition(eps, state3);
        state3->addTransition(eps, state2);
        Unioned.push_back(state2);
        Unioned.push_back(state3);
    }
    return Unioned;
}


void RE::PlaceHolderMaker() {

    int indexIn;
    int indexOut;

    while (expressie.find('(') != expressie.npos) {
        for (int i = 0; i < expressie.size(); i++) {
            auto c = expressie[i];
            if (c == '(') {
                indexIn = i;
            } else if (c == ')') {
                replaced++; //volgnummer van de replacement.
                indexOut = i+1;
                string replacer = "'repl" + to_string(replaced) + "'";
                string to_replace = expressie.substr(indexIn, (indexOut - indexIn));    //substring die vervangen wordt
                expressie.replace(indexIn, (indexOut - indexIn), replacer);
                placeholders[replacer] = to_replace;
                break;
            }
        }
    }
}


void RE::PlaceHolderENFAmaker() {

    for (int i=0; i<replaced+1 ; i++){
        string repl = "'repl" + to_string(i) + "'";
        auto res = replToENFA(repl, i); //resulterenede subENFA va de replacement.
        placeholderENFAs[repl] = res;
    }

}


vector<State_NFA *> RE::replToENFA(string replacedName, int r) {
    vector<State_NFA*> ENFA;
    string r_name;
    if (r>0){   //als de replacement gebruik zou maken van een andere replacement die in deze zit. In dat geval is dat
        //de replacement voor de deze
        r_name = "'repl" + to_string(r-1) + "'";

    }

    string naamSub;
    vector<vector<State_NFA*>> forUnion;
    string repl = placeholders[replacedName];
    for(int i=1; i<repl.size()-1; i++){
        auto c = repl.at(i);
        if (c == '+' or i == repl.size()-2){
            if (i == repl.size()-2 and c != '*'){
                naamSub += c;
            }
            int test = naamSub.find('\'', 1);
            if (r>0 and naamSub.at(0) == '\'' and naamSub.at(naamSub.size()-1) == '\'' and
                (repl.at(i+1) == ')' or repl.at(i) == '+') and naamSub.find('\'', 1) == naamSub.size()-1){ //als het om een replacement in de replacement gaat.
                if (c == '*'){
                    placeholderENFAs[naamSub] = KleeneStar(placeholderENFAs[naamSub]);
                }
                forUnion.push_back(placeholderENFAs[naamSub]);
            }
            else if(subENFAs.find(naamSub) != subENFAs.end()){  //Als het om een character of concatenatie van characters gaat.
                forUnion.push_back(subENFAs[naamSub].back());
                subENFAs[naamSub].pop_back();
            }else{
                vector<State_NFA*> concat = concatChecker(naamSub);
                if (c =='*'){
                    forUnion.push_back(KleeneStar(concat));
                }else{
                    forUnion.push_back(concat);
                }
            }
            naamSub = "";
        }
        else{
            naamSub += c;
        }
    }

    auto res = Union(forUnion,false,false);    //unie van de subENFA's
    ENFA.insert(ENFA.end(), res.begin(), res.end());
    return ENFA;
}


vector<State_NFA *> RE::replacedMerger() {
    vector<State_NFA*> resENFA;
    vector<State_NFA*> concat;  //vector voor in geval van concatenatie.

    string naamSub;
    int size = expressie.size();
    vector<vector<State_NFA*>> forUnion;
    for (int i = 0; i<expressie.size(); i++){
        auto c = expressie.at(i);
        if (i == expressie.size()-1){
            naamSub = naamSub + c;
        }
        if (c == '\''){ //Als het een replaced deel is.
            if(!naamSub.empty()){   //als er voor de replacement een stuk staat.
                auto sub = subENFAs[naamSub].back();
                subENFAs[naamSub].pop_back();
                if (!concat.empty()) {
                    concat.back()->addTransition(eps, sub.front());
                    concat.insert(concat.end(), sub.begin(), sub.end());
                } else {
                    concat = sub;
                }
            }
            int posend = expressie.find('\'', i+1);
            naamSub = expressie.substr(i, posend+1-i);
            i = posend;
            if(i != expressie.size()-1 and expressie.at(i+1) == '*'){   //als de replacement kleenClosed is.
                i++;
                auto res = KleeneStar(placeholderENFAs[naamSub]);
                if (concat.empty()){    //als er niets in de vector zit.
                    concat = res;
                }else{  //anders concateneren door transities toe te voegen.
                    concat.back()->addTransition(eps, res.front());
                    concat.insert(concat.end(),res.begin(), res.end());
                }
                naamSub = "";
            }else{
                auto res = placeholderENFAs[naamSub];
                if (concat.empty()){    //als er niets in de vector zit.
                    concat = res;
                }else{  //anders concateneren door transities toe te voegen.
                    concat.back()->addTransition(eps, res.front());
                    concat.insert(concat.end(),res.begin(), res.end());
                }
                naamSub = "";
            }
            continue;
        }
        else if (c == '+' or i == expressie.size()-1) { //als de character een + is of de laatste character van de string.

            if (naamSub.empty() and !concat.empty()) {
                forUnion.push_back(concat);
                concat.clear();
            } else {
                auto sub = subENFAs[naamSub].back();
                subENFAs[naamSub].pop_back();
                if (!concat.empty()) {
                    concat.back()->addTransition(eps, sub.front());
                    concat.insert(concat.end(), sub.begin(), sub.end());
                    forUnion.push_back(concat);
                    concat.clear();
                } else {
                    forUnion.push_back(sub);
                }
            }
            naamSub = "";
        }else {
            naamSub = naamSub + c;
        }
    }
    if (!concat.empty()){
        forUnion.push_back(concat);
    }
    resENFA = Union(forUnion, false, false);
    return resENFA;
}


ENFA RE::toENFA() {
    parser();
    PlaceHolderMaker();
    PlaceHolderENFAmaker();
    auto res = replacedMerger();
    res.front()->setStarting(true);
    res.back()->setAccepting(true);

    map<string, State_NFA*> ENFA_states;
    for (auto s:res){
        ENFA_states[s->getName()] = s;
    }

    ENFA a(ENFA_states, alphabet, res.front()->getName(), eps);
    return a;
}

DFA RE::toDFA() {
    return this->toENFA().toDFA(false);
}

vector<State_NFA *> RE::concatChecker(string subexpression) {
    vector<string> concatParts;
    int size = subexpression.size();

    for (int i = 0; i<size; i++){
        auto c = subexpression.at(i);
        string repl;
        if (isalnum(c) or c == '*'){
            repl += c;
            int place = i+1;
            for (int k = i+1; k <subexpression.size(); k++){
                place = k;
                if (subexpression.at(k) == '\''){
                    place = k-1;
                    break;
                }
            }
            repl += subexpression.substr(i+1, place-i);
            i = place;
            concatParts.push_back(repl);
        }else if(c == '\''){
            repl += c;
            int place = 0;
            for (int k = i+1; k <subexpression.size(); k++){
                if (subexpression.at(k) == '\''){
                    place = k;
                    break;
                }
            }
            repl += subexpression.substr(i+1, place-i);
            i = place;
            if (i+1 < subexpression.size() and subexpression.at(i+1) == '*'){
                placeholderENFAs[repl] = KleeneStar(placeholderENFAs[repl]);
                i++;
            }
            concatParts.push_back(repl);
        }
    }
    vector<State_NFA*> concatenated;
    for(int i=0;i<concatParts.size(); i++){
        string string = concatParts.at(i);
        vector<State_NFA*> part;
        if (subENFAs.find(string) != subENFAs.end()) {
            if(i < concatParts.size()-1 and concatParts.at(i+1) == "*"){
                part = KleeneStar(subENFAs[string].back());
            }else {
                part = subENFAs[string].back();
            }
            subENFAs[string].pop_back();
        }else if (placeholderENFAs.find(string) != placeholderENFAs.end()){
            part = placeholderENFAs[string];
        }
        if (concatenated.empty()) {
            concatenated.insert(concatenated.end(), part.begin(), part.end());
        }else{
            int conectionPoint = concatenated.size()-1;
            concatenated.insert(concatenated.end(), part.begin(), part.end());
            concatenated[conectionPoint]->addTransition(eps, concatenated[conectionPoint+1]);
        }
    }
    return concatenated;
}



