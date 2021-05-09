//
// Created by Maksim Karnaukh on 5/05/2021.
// Ik heb geprobeerd overal waar ik kan te commenten
//

#include "Maksim.h"

//    Maksim maksim;
//    string a = "010100";
//    maksim.stringToBarcode(a);

void Maksim::stringToBarcode(string &str) {

    ofstream fIniFile;
    fIniFile.open("../iniFile.ini"); // plaats van ini file

    int stringLength = str.size();
    int figures = stringLength; // aantal "rechthoeken" (eigenlijk cylinders) die naast elkaar gaan komen

    fIniFile << "[General]" << endl;
    fIniFile<< "size = 1024" << endl;
    fIniFile<< "backgroundcolor = (0.41, 0.41, 0.41)" << endl; // grijze achtergrond (zodat beide kleuren (zwart en wit) onderscheidbaar zijn van de achtergrond)
    fIniFile<< "type = \"ZBuffering\"" << endl; // we doen zbuffering met driehoeken, omdat we de vlakken dan kunnen inkleuren.
    fIniFile<< "eye = (200, 0, 0)" << endl;
    fIniFile<< "nrFigures = " << figures << "\n"; // het aantal figuren wordt bepaald door het aantal bits in onze string

    // vanaf 16 bits met verhoudingen werken

    for (auto i = 0; i < figures; i++) { // figures = str.size
        fIniFile << "[Figure" <<  i << "]" << endl;
        fIniFile << "type = \"Cylinder\"" << endl;
        fIniFile << "height = " << 15 << endl;
        fIniFile << "n = 36" << endl;
        fIniFile << "scale = 0.25" << endl;
        fIniFile << "rotateX = 0" << endl;
        fIniFile << "rotateY = 0" << endl;
        fIniFile << "rotateZ = 0" << endl;
        fIniFile << "center = " << "(0, " << i*0.5 << ", 0)" << endl; // de y verandert telkens met +0.5, enkel bij deze afstandsverschil komen de cylinders mooi naast elkaar te staan.
        if (str[i] == '1') { // als we een 1 tegenkomen, moet er een zwarte rechthoek komen. Bij een 0 is dit dan een witte rechthoek.
            fIniFile << "color = " << "(0, 0, 0)" << endl;
        }
        else {
            fIniFile << "color = " << "(1, 1, 1)" << endl;

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
string Maksim::generateRE(int numberOfIterations) { // het aantal iteraties bepaalt hoeveel bewerkingen we gaan uitvoeren (per deelbewerking)

    // het alfabet van de RE is {0,1}
    // vector<string> alfabet{"0", "1"};
    // vector<string> bewerkingen{"unie", "concatenatie", "kleeneStar"};

    string RE; // string die we returnen
    string R;
    string S;
    string U;
    string T;

    // R bepalen
    string randomR = getRandomString(numberOfIterations);
    R = randomR;

    // S bepalen
    string randomS = getRandomString(numberOfIterations);
    S = randomS;

    // U bepalen
    string randomU = getRandomString(numberOfIterations);
    U = randomU;

    // T bepalen
    string randomT = getRandomString(numberOfIterations);
    T = randomT;

    // formule samenstellen
    string formule = "(" + R + " + " + S + U + "*" + T + ")" + "*" + S + U + "*"; // algemene vorm van formule

    //debugging
    cout << "R = " << R << endl;
    cout << "S = " << S << endl;
    cout << "U = " << U << endl;
    cout << "T = " << T << endl;

    // doorsnede checken => controlesysteem
    bool doorsnede = false;
    if (doorsnede) {
        return generateRE(numberOfIterations+1); // we vergroten bij de volgende aanroep het aantal bewerkingen met 1.
    }
    else {
        RE = formule;
    }

    return RE;
}

string Maksim::chooseOperationFirstTime() { // hier "maken" we een deelregex voor de eerste keer
    int symbool1 = rand() % 2; // kiest een symbool (0 of 1)
    int randomBewerking = rand() % 3; // kiest een bewerking. 0 = unie, 1 = concatenatie, 2 = kleeneStar

    string deelRegex;
    if (randomBewerking == 0) { // unie
        deelRegex = "(" + to_string(symbool1) + "+" + to_string(1-symbool1) + ")"; // (0+1)
    }
    else if (randomBewerking == 1) { // concat
        int randConcat = rand() % 2;

        if (randConcat == 0) {
            deelRegex = "(" + to_string(symbool1) + to_string(1-symbool1) + ")"; // 01 of 10
        }
        else if (randConcat == 1) {
            deelRegex = "(" + to_string(symbool1) + to_string(symbool1) + ")"; // 00 of 11
        }
    }
    else if (randomBewerking == 2) { // kleene
        deelRegex = "(" + to_string(symbool1) + ")*"; // (0)* of (1)*
    }

    return deelRegex;
}

string Maksim::chooseOperation(string &deelRegex1) { // vanaf dat we 1 iteratie moeten voltooien bij generateRE(), roepen we deze functie op.
    int symbool1 = rand() % 2; // kiest een symbool (0 of 1)
    int randomBewerking;
    if (deelRegex1[deelRegex1.size()-1] != '*') {
        randomBewerking = rand() % 3; // kiest een bewerking. 0 = unie, 1 = concatenatie, 2 = kleeneStar
    }
    else {
        randomBewerking = rand() % 2; // kleene star zit hier niet bij de mogelijke bewerkingen
    }

    string deelRegex;
    if (randomBewerking == 0) { // unie
        deelRegex = "(" + to_string(symbool1) + "+" + deelRegex1 + ")"; // (0+1)
    }
    else if (randomBewerking == 1) { // concat
        int randConcat = rand() % 2;

        if (randConcat == 0) {
            deelRegex = "(" + to_string(symbool1) + deelRegex1 + ")"; // 01 of 10
        }
        else if (randConcat == 1) {
            deelRegex = "(" + deelRegex1 + to_string(symbool1) + ")"; // 00 of 11
        }
    }
    else if (randomBewerking == 2) { // kleene
        deelRegex = "(" + deelRegex1 + ")*"; // (0)* of (1)*
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
