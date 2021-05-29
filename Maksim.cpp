//
// Created by Maksim Karnaukh on 5/05/2021.
//
//

#include "Maksim.h"

//Maksim maksim;
//string a = "010100";
//maksim.stringToBarcode(a);
//save_image("../iniFile.ini");


void Maksim::stringToBarcode(string &str) {


    ofstream fIniFile;
    fIniFile.open("../iniFile.ini"); // plaats van ini file

    int stringLength = str.size();
    int figures = stringLength; // aantal "rechthoeken" (eigenlijk cylinders) die naast elkaar gaan komen

    fIniFile << "[General]" << endl;
    fIniFile << "size = 1024" << endl;
    fIniFile << "backgroundcolor = (0.41, 0.41, 0.41)" << endl; // grijze achtergrond (zodat beide kleuren (zwart en wit) onderscheidbaar zijn van de achtergrond)
    fIniFile << "type = \"ZBuffering\"" << endl; // we doen zbuffering met driehoeken, omdat we de vlakken dan kunnen inkleuren.
    fIniFile << "eye = (200, 0, 0)" << endl;
    fIniFile << "nrFigures = " << figures << "\n"; // het aantal figuren wordt bepaald door het aantal bits in onze string.

    // vanaf 16 bits met verhoudingen werken

    if (figures < 16) {
        for (auto i = 0; i < figures; i++) { // figures = str.size
            fIniFile << "[Figure" <<  i << "]" << endl;
            fIniFile << "type = \"Cylinder\"" << endl;
            fIniFile << "height = " << 15 << endl;
            fIniFile << "n = 36" << endl;
            fIniFile << "scale = 0.25" << endl;
            fIniFile << "rotateX = 0" << endl;
            fIniFile << "rotateY = 0" << endl;
            fIniFile << "rotateZ = 0" << endl;
            fIniFile << "center = " << "(0, " << i*0.55 << ", 0)" << endl; // de y verandert telkens met +0.5, enkel bij deze afstandsverschil komen de cylinders mooi naast elkaar te staan.
            if (str[i] == '1') { // als we een 1 tegenkomen, moet er een zwarte rechthoek komen. Bij een 0 is dit dan een witte rechthoek.
                fIniFile << "color = " << "(0, 0, 0)" << endl;
            }
            else {
                fIniFile << "color = " << "(1, 1, 1)" << endl;

            }
        }
    }
    else { // hier moeten we de scale, factorI en hoogte aanpassen

        double hoogte;
        double scale;
        double factorI;

        if (16 <= figures && figures < 24) {
            hoogte = 20;
            scale = 0.25;
            factorI = 0.575;
        }
        else if (24 <= figures && figures < 32) {
            hoogte = 34;
            scale = 0.175;
            factorI = 0.4;
        }
        else if (32 <= figures && figures < 40) {
            hoogte = 44;
            scale = 0.1;
            factorI = 0.225;
        }
        else if (40 <= figures && figures < 48) {
            hoogte = 60;
            scale = 0.05;
            factorI = 0.125;
        }
        else if (48 <= figures && figures < 56) {
            hoogte = 70;
            scale = 0.025;
            factorI = 0.055;
        }
        else { // if (49 <= figures && figures < 56)
            hoogte = 80;
            scale = 0.0125;
            factorI = 0.03;
        }
        cout << hoogte;

        for (auto i = 0; i < figures; i++) { // figures = str.size
            fIniFile << "[Figure" <<  i << "]" << endl;
            fIniFile << "type = \"Cylinder\"" << endl;
            fIniFile << "height = " << hoogte << endl;
            fIniFile << "n = 36" << endl;
            fIniFile << "scale = " << scale << endl;
            fIniFile << "rotateX = 0" << endl;
            fIniFile << "rotateY = 0" << endl;
            fIniFile << "rotateZ = 0" << endl;
            fIniFile << "center = " << "(0, " << i*factorI << ", 0)" << endl; // de y verandert telkens met +0.5, enkel bij deze afstandsverschil komen de cylinders mooi naast elkaar te staan.
            if (str[i] == '1') { // als we een 1 tegenkomen, moet er een zwarte rechthoek komen. Bij een 0 is dit dan een witte rechthoek.
                fIniFile << "color = " << "(0, 0, 0)" << endl;
            }
            else {
                fIniFile << "color = " << "(1, 1, 1)" << endl;

            }
        }
    }

    fIniFile.close();
}

//Maksim maksim;
//srand ((int)time(NULL));
//for (auto i = 0; i < 10; i++) {
//string re = maksim.generateRE(2);
//cout << re << endl;
//cout << endl;
//}
string Maksim::generateRE(Datastructuur& data, vector<long>& timeBrz, vector<long>& timeTFA, vector<long>& memoryBRZ,
                          vector<long>& memoryTFA, int numberOfIterations) { // het aantal iteraties bepaalt hoeveel bewerkingen we gaan uitvoeren (per deelbewerking)

    // het alfabet van de RE is {0,1}
    // vector<string> alfabet{"0", "1"};
    // vector<string> bewerkingen{"unie", "concatenatie", "kleeneStar"};

    string RE; // string die we returnen
    string R; string S; string U; string T; string C;
    bool notEmpty = false;
    bool isConcatDeelRegex = false;
    if (numberOfIterations > 8) {
        notEmpty = true;
        isConcatDeelRegex = true;
    }

    int isBewerking = rand() % 10; // er is een kans voor elke deelregex om leeg te blijven

    // R bepalen
    string randomR;
    randomR = getRandomString(numberOfIterations, false);

    R = randomR;

    // S bepalen
    string randomS;
    if (isBewerking < 5 || notEmpty) {
        randomS = getRandomString(numberOfIterations, false);
    }
    S = randomS;

    // U bepalen
    string randomU;
    if (isBewerking > 5 || notEmpty) {
        randomU = getRandomString(numberOfIterations, false);
    }
    U = randomU;

    // T bepalen
    string randomT;
    if (isBewerking > 7-numberOfIterations%3 || notEmpty) { // in het slechtste geval => isBewerking > 5
        randomT = getRandomString(numberOfIterations, false);
    }
    T = randomT;

    string concatDeelRegex;
    if (isConcatDeelRegex) { // in het slechtste geval => isBewerking > 5
        concatDeelRegex = getRandomString(numberOfIterations-7, true);
    }
    C = concatDeelRegex;

    if (!R.empty()) {
        R = R + "+";
    }
    if (!S.empty()) {
        string reverseR = R;
        reverse(reverseR.begin(), reverseR.end());
        string reverseS = S;
        reverse(reverseS.begin(), reverseS.end());
        if (R == S || reverseR == S || R == reverseS) {
            S = "";
        }
    }


    string formule;
    if (S.empty() && U.empty()) {
        formule = R + S + U + T + S + U + C; // algemene vorm van formule
        if (T.empty()) {
            formule = R + C;
            if (C.empty()) {
                R = R.substr(0, R.size()-1);
                formule = R;
            }
        }
    }
    else {
        formule = "(" + R + S + U + T +")" + S + U + C; // algemene vorm van formule
    }

    cout << numberOfIterations << endl;

    // formule samenstellen

    //debugging
    cout << "R = " << R << endl;
    cout << "S = " << S << endl;
    cout << "U = " << U << endl;
    cout << "T = " << T << endl;
    cout << "C = " << C << endl;

    cout << formule << endl << endl;

    // doorsnede checken => controlesysteem
    bool doorsnede = controleSysteem(formule, data, timeBrz, timeTFA, memoryBRZ, memoryTFA);

    if (!doorsnede) { // als de doorsnedes niet leeg zijn
        timeBrz.pop_back();
        timeTFA.pop_back();
        return generateRE(data, timeBrz, timeTFA,memoryBRZ, memoryTFA, numberOfIterations+1); // we vergroten bij de volgende aanroep het aantal bewerkingen met 1.
    }
    else {
        formule = minimizeRegex(formule);
        RE = formule;
    }
    return RE;
}

string Maksim::chooseOperationFirstTime(bool isConcatOnly) { // hier "maken" we een deelregex voor de eerste keer
    int symbool1 = rand() % 2; // kiest een symbool (0 of 1)
    int randomBewerking;
    if (isConcatOnly) {
        randomBewerking = 1;
    }
    else {
        randomBewerking = rand() % 2; // kiest een bewerking. 0 = unie, 1 = concatenatie, 2 = kleeneStar
    }
    int geenBewerking = rand() % 10;

    string deelRegex;

    if (geenBewerking < 3) {
        deelRegex = to_string(symbool1);
    }
    else {
        if (randomBewerking == 0) { // unie
            deelRegex = "(" + to_string(symbool1) + "+" + to_string(1-symbool1) + ")"; // (0+1)
        }
        else if (randomBewerking == 1) { // concat
            int randConcat = rand() % 2;

            if (randConcat == 0) {
                deelRegex = to_string(symbool1) + to_string(1-symbool1); // 01 of 10
            }
            else if (randConcat == 1) {
                deelRegex = to_string(symbool1) + to_string(symbool1); // 00 of 11
            }
        }
        else if (randomBewerking == 2) { // kleene
            deelRegex = "(" + to_string(symbool1) + ")*"; // (0)* of (1)*
        }
    }

    return deelRegex;
}

string Maksim::chooseOperation(string &deelRegex1, bool isConcatOnly) { // vanaf dat we 1 iteratie moeten voltooien bij generateRE(), roepen we deze functie op.
    int symbool1 = rand() % 2; // kiest een symbool (0 of 1)
    int randomBewerking; // kleene star zit hier niet bij de mogelijke bewerkingen
    if (isConcatOnly) {
        randomBewerking = 1;
    }
    else {
        randomBewerking = rand() % 3; // kiest een bewerking. 0 = unie, 1 = concatenatie, 2 = kleeneStar
    }
    int geenBewerking = rand() % 10;

    string deelRegex;

    if (geenBewerking < 2) {
        deelRegex = deelRegex1;
    }
    else {
        if (randomBewerking == 0) { // unie
            if (deelRegex1 == to_string(symbool1)) {
                symbool1 = 1 - symbool1;
            }
            deelRegex = "(" + to_string(symbool1) + "+" + deelRegex1 + ")"; // (0+1)
        }
        else if (randomBewerking == 1 || randomBewerking == 2) { // concat
            int randConcat = rand() % 2;

            if (randConcat == 0) {
                deelRegex = to_string(symbool1) + deelRegex1; // 01 of 10
            }
            else if (randConcat == 1) {
                deelRegex = deelRegex1 + to_string(symbool1); // 00 of 11
            }
        }
//        else if (randomBewerking == 2) { // kleene
//            deelRegex = "(" + deelRegex1 + ")*"; // (0)* of (1)*
//        }
    }

    return deelRegex;
}

string Maksim::getRandomString(int nr_iterations, bool isConcatOnly) {
    string randomRegex;
    if (nr_iterations == 0) {
        randomRegex = chooseOperationFirstTime(isConcatOnly);
    }
    else {
        randomRegex = chooseOperationFirstTime(isConcatOnly);

        for (auto i = 0; i < nr_iterations; i++) {
            randomRegex = chooseOperation(randomRegex, isConcatOnly);
        }
    }
    return randomRegex;
}

void Maksim::createHTMLFile(Datastructuur &datastructuur) {
    vector<Bestemming*> bestemmingen;
    datastructuur.inorderTraversal(bestemmingen);

    ofstream htmlTabel;
    htmlTabel.open("../html.html");
    htmlTabel << "<!DOCTYPE html><html><head></head><body>";

    // de opmaak voor de tabel heeft Inte gemaakt, hier is de opmaak hetzelfde als bij de andere delen van de GUI.
    htmlTabel << "<style>";
    htmlTabel << "th {";
    htmlTabel << "text-align: left;";
    htmlTabel << "}";

    htmlTabel << "td {";
    htmlTabel << "text-align: left;";
    htmlTabel << "}";
        htmlTabel << ".styled-table";
            htmlTabel << "{";
            htmlTabel << "border-collapse: collapse;";
            htmlTabel << "margin: 25px 0;";
            htmlTabel << "font-size: 0.9em;";
            htmlTabel << "font-family: sans-serif;";
            htmlTabel << "min-width: 1000px;"; // 98vw
            htmlTabel << "background-color: #32373a;";
            htmlTabel << "color: white;";
            htmlTabel << "text-align: center;";
            htmlTabel << "border-radius: 10px 10px 10px 10px;";
            htmlTabel << "overflow: hidden;";
            htmlTabel << "box-shadow: 0 0 20px rgba(0,0,0,0.25);";
            htmlTabel << "}";
        htmlTabel << ".styled-table thead tr";
            htmlTabel << "{";
            htmlTabel << "background-color: #32373a;";
            htmlTabel << "color: white;";
            htmlTabel << "text-align: center;";
            htmlTabel << "font-weight: bold;";
            htmlTabel << "font-size: 18px;";
            htmlTabel << "}";
        htmlTabel << ".styled-table th,";
        htmlTabel << ".styled-table td";
            htmlTabel << "{";
            htmlTabel << "padding: 12px 15px;";
            htmlTabel << "}";
        htmlTabel << ".styled-table tbody tr";
            htmlTabel << "{";
            htmlTabel << "border-bottom: 1px solid white;";
            htmlTabel << "}";

    htmlTabel << "</style>";

    htmlTabel << "<table class=\"styled-table\">";
    htmlTabel << "<thead>";
        htmlTabel << "<tr>";
            htmlTabel << "<th>Bestemming</th>";
            htmlTabel << "<th>" << "</th>";
            htmlTabel << "<th>" << "</th>";
            htmlTabel << "<th>" << "</th>";
            htmlTabel << "<th>Regex</th>";
        htmlTabel << "</tr>";
    htmlTabel << "</thead>";

    htmlTabel << "<tbody>";

    for (auto i = 0; i < bestemmingen.size(); i++) {
        htmlTabel << "<tr>";

        htmlTabel << "<td>" << bestemmingen[i]->getName() << "</td>";
        htmlTabel << "<td>" << "</td>";
        htmlTabel << "<td>" << "</td>";
        htmlTabel << "<td>" << "</td>";
        htmlTabel << "<td>" << bestemmingen[i]->getRegex() << "</td>";

        htmlTabel << "</tr>";
    }

    htmlTabel << "</tbody>";
    htmlTabel << "</table>";

    htmlTabel << "</body></html>";
    htmlTabel.close();
}

string Maksim::minimizeRegex(string &regex) {
    string re;
    RE newRE = RE(regex, 'e');

    // RE -> ENFA
    ENFA enfa = newRE.toENFA();
    // ENFA -> DFA
    DFA dfa = enfa.toDFA(false);
    // DFA minimaliseren
    long time;
    dfa.minimize(time);
    // DFA -> RE
    ofstream json;
    json.open("regex.json");
//    re =
    return re;
}

//Node *Maksim::parseRegex(string &formula) {
//    bool a = true;
//    for (auto i = 0; i < formula.size(); i++) {
//        if (formula[i] != '0' && formula[i] != '1' && formula[i] != '(' && formula[i] != ')') {
//            a = false;
//            break;
//        }
//        if (formula[i] == '(' || formula[i] == ')') {
//            break;
//        }
//    }
//    if (a) {
//        formula = toRegexWithDots(formula, fAlphabet, fEpsilon);
//    }
//    if (formula.size() == 0) { // een formule kan nooit leeg zijn
//        cerr << "Lege formule!";
//        return nullptr;
//    } else if (formula.size() == 1) { //de enige geldige formules van lengte 1 zijn variabelen
//        if (!count(fAlphabet.begin(), fAlphabet.end(), formula[0]) && formula[0] != fEpsilon) { //# enkel a, b, c zijn toegestaan als variabelen
//            cerr << "Ongeldige variabele naam: " << formula << endl;
//            return nullptr;
//        }
//        else {
//            return new varNode(formula[0]);
//        }
//    } else { // samengestelde formule
////        if (formula[0] == '-') { // unaire operator not
////            return new starNode(parseRegex(formula.substr(1, formula.size() - 1)));
////        } else { // binaire operator, dus formule is van de vorm oper1 operator oper2
//        if (formula[formula.size()-1] == '*') {
//            string gedeelteVoorStar = formula.substr(1, formula.size() - 3);
//            return new starNode(parseRegex(gedeelteVoorStar));
//        }
//        if (formula[0] == '(' && formula[formula.size()-1] == ')') {
//            bool allowedToRemoveParentheses = true;
//            for (auto it = 1; it < formula.size()-1; it++) {
//                if (formula[it] == '(' || formula[it] == ')') {
//                    allowedToRemoveParentheses = false;
//                }
//            }
//            if (allowedToRemoveParentheses) {
//                formula = formula.substr(1, formula.size() - 2);
//            }
//        }
//        int i = 0;
//        int depth = 0;
//        while (((formula[i] != '+') && (formula[i] != '.')) ||
//               depth > 0) {    // zoek de positie van de operator
//            // let op! er kunnen geneste haakjes zijn
//            if (formula[i] == '(') { // een subexpressie; operatoren die hierbinnen staan negeren we
//                depth += 1;    // dit is hoe diep we in geneste haakjes zitten
//            } else if (formula[i] == ')') { // 1 nestingsdiepte terug omhoog
//                depth -= 1;
//            }
//            i += 1;
//        }
//        // de operator staat op positie i
//        string oper1 = formula.substr(0, i);
//        char oper = formula[i];
//        string oper2 = formula.substr(i + 1, formula.size() - i - 1);
//        if (oper == '+') {
//            return new plusNode(parseRegex(oper1), parseRegex(oper2));
//        } else {
//            return new concatNode(parseRegex(oper1), parseRegex(oper2));
//        }
////        }
//    }
//}
//
//string Maksim::toRegexWithDots(string &str, vector<char> &alphabet, char epsilon) {
//    string reWithDots;
//    for (auto i = 0; i < str.size(); i++) {
//        if (i > 0) { // niet eerste character
//            char prevChar = str[i-1];
//            if (count(alphabet.begin(), alphabet.end(), prevChar) || prevChar == epsilon || prevChar == '*' || prevChar == ')') { // als het vorige character een deel is van het alfabet
//                if (str[i] == '(') {
//                    reWithDots += '.';
//                    reWithDots += str[i];
//                }
//                else if (count(alphabet.begin(), alphabet.end(), str[i])) {
//                    reWithDots += '.';
//                    reWithDots += str[i];
//                }
//                else {
//                    reWithDots += str[i];
//                }
//            }
//            else {
//                reWithDots += str[i];
//            }
//        }
//        else {
//            reWithDots += str[i];
//        }
//    }
//    return reWithDots;
//}
