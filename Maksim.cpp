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

    //    while (U[U.size()-1] == '*') {
//        U = U.substr(0, U.size()-1);
//    }
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

void Maksim::createHTML(Datastructuur &datastructuur) {

}
