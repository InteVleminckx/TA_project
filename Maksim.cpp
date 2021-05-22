//
// Created by Maksim Karnaukh on 5/05/2021.
// Ik heb geprobeerd overal waar ik kan te commenten
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
    else { // hier moeten we de scale en hoogte aanpassen

        // 17.5 - 0.25? - 0.575 //
        // 25 - 0.175 - 0.4 //
        // 32.5 - 0.1 - 0.225 //
        // 40 - 0.05 - 0.125 //
        // 47.5 - 0.025 - 0.05 //

        double hoogte = 55;
        double scale = 0.0125;
        for (auto i = 0; i < figures; i++) { // figures = str.size
            fIniFile << "[Figure" <<  i << "]" << endl;
            fIniFile << "type = \"Cylinder\"" << endl;
            fIniFile << "height = " << hoogte << endl;
            fIniFile << "n = 36" << endl;
            fIniFile << "scale = " << scale << endl;
            fIniFile << "rotateX = 0" << endl;
            fIniFile << "rotateY = 0" << endl;
            fIniFile << "rotateZ = 0" << endl;
            fIniFile << "center = " << "(0, " << i*0.03 << ", 0)" << endl; // de y verandert telkens met +0.5, enkel bij deze afstandsverschil komen de cylinders mooi naast elkaar te staan.
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
                          vector<long>& memoryTFA, Bestemming& best, int numberOfIterations) { // het aantal iteraties bepaalt hoeveel bewerkingen we gaan uitvoeren (per deelbewerking)

    // het alfabet van de RE is {0,1}
    // vector<string> alfabet{"0", "1"};
    // vector<string> bewerkingen{"unie", "concatenatie", "kleeneStar"};

    string RE; // string die we returnen
    string R; string S; string U; string T;
    bool leeg = false;
    if (numberOfIterations > 8) {
        leeg = true;
    }

    int isBewerking = rand() % 10; // er is een kans voor elke deelregex om leeg te blijven

    // R bepalen
    string randomR;
    randomR = getRandomString(numberOfIterations);

    R = randomR;

    // S bepalen
    string randomS;
    if (isBewerking < 5 || leeg) {
        randomS = getRandomString(numberOfIterations);
    }
    S = randomS;

    // U bepalen
    string randomU;
    if (isBewerking > 5 || leeg) {
        randomU = getRandomString(numberOfIterations);
    }
    U = randomU;

    // T bepalen
    string randomT;
    if (isBewerking > 7-numberOfIterations%3 || leeg) { // in het slechtste geval => isBewerking > 5
        randomT = getRandomString(numberOfIterations);
    }
    T = randomT;

    if (!R.empty()) {
        R = R + "+";
    }

    //    while (U[U.size()-1] == '*') {
//        U = U.substr(0, U.size()-1);
//    }
    string formule;
    if (S.empty() && U.empty()) {
        formule = R + S + U + T + S + U; // algemene vorm van formule
        if (T.empty()) {
            R = R.substr(0, R.size()-1);
            formule = R;
        }
    }
    else {
        formule = "(" + R + S + U + T +")" + S + U; // algemene vorm van formule
    }

    cout << numberOfIterations << endl;

    // formule samenstellen

    //debugging
    cout << "R = " << R << endl;
    cout << "S = " << S << endl;
    cout << "U = " << U << endl;
    cout << "T = " << T << endl;
    cout << formule << endl << endl;

    //Datastructuur data; //tijdelijke plaatshouder, stelt de bestaande bestemmingen voor.
    //Mss best nog een extra parameter aan deze functie, de echte datastuur meegegeven bij het oproepen van de generatie.

    // doorsnede checken => controlesysteem
    bool doorsnede = controleSysteem(formule, data, timeBrz, timeTFA, memoryBRZ, memoryTFA, best);

    if (!doorsnede) { // als de doorsnedes niet leeg zijn
        timeBrz.pop_back();
        timeTFA.pop_back();
        return generateRE(data, timeBrz, timeTFA,memoryBRZ, memoryTFA,best, numberOfIterations+1); // we vergroten bij de volgende aanroep het aantal bewerkingen met 1.
    }
    else {
        RE = formule;
    }
    return RE;
}

string Maksim::chooseOperationFirstTime() { // hier "maken" we een deelregex voor de eerste keer
    int symbool1 = rand() % 2; // kiest een symbool (0 of 1)
    int randomBewerking = rand() % 2; // kiest een bewerking. 0 = unie, 1 = concatenatie, 2 = kleeneStar
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

string Maksim::chooseOperation(string &deelRegex1) { // vanaf dat we 1 iteratie moeten voltooien bij generateRE(), roepen we deze functie op.
    int symbool1 = rand() % 2; // kiest een symbool (0 of 1)
    int randomBewerking = rand() % 3; // kleene star zit hier niet bij de mogelijke bewerkingen
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

string Maksim::getRandomString(int nr_iterations) {
    string randomRegex;
    if (nr_iterations == 0) {
        randomRegex = chooseOperationFirstTime();
    }
    else {
        randomRegex = chooseOperationFirstTime();

        for (auto i = 0; i < nr_iterations; i++) {
            randomRegex = chooseOperation(randomRegex);
        }
    }
    return randomRegex;
}