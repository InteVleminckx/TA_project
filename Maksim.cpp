//
// Created by Maksim Karnaukh on 5/05/2021.
//

#include "Maksim.h"

//    Maksim maksim;
//    string a = "010100";
//    maksim.stringToBarcode(a);

void Maksim::stringToBarcode(string &str) {

    ofstream fIniFile;
    fIniFile.open("../iniFile.ini");

    int stringLength = str.size();

    int figures = stringLength; // aantal "rechthoeken" die naast elkaar gaan komen

    fIniFile << "[General]" << endl;
    fIniFile<< "size = 1024" << endl;
    fIniFile<< "backgroundcolor = (0.41, 0.41, 0.41)" << endl; // grijze achtergrond (zodat beide kleuren onderscheidbaar zijn van de achtergrond)
    fIniFile<< "type = \"ZBuffering\"" << endl;
    fIniFile<< "eye = (200, 0, 0)" << endl;
    fIniFile<< "nrFigures = " << figures << "\n";

    for (auto i = 0; i < figures; i++) { // figures = str.size
        fIniFile << "[Figure" <<  i << "]" << endl;
        fIniFile << "type = \"Cylinder\"" << endl;
        fIniFile << "height = " << 15 << endl;
        fIniFile << "n = 36" << endl;
        fIniFile << "scale = 0.25" << endl;
        fIniFile << "rotateX = 0" << endl;
        fIniFile << "rotateY = 0" << endl;
        fIniFile << "rotateZ = 0" << endl;
        fIniFile << "center = " << "(0, " << i*0.5 << ", 0)" << endl; // de y verandert telkens met
        if (str[i] == '1') {
            fIniFile << "color = " << "(0, 0, 0)" << endl;
        }
        else {
            fIniFile << "color = " << "(1, 1, 1)" << endl;

        }
    }

    fIniFile.close();
}

// Maksim maksim;
//    srand ((int)time(NULL));
//    for (auto i = 0; i < 10; i++) {
//        string re = maksim.generateRE();
//        cout << re << endl;
//    }
string Maksim::generateRE(int numberOfIterations) { // het aantal iteraties bepaalt hoeveel bewerkingen we gaan uitvoeren (per deelbewerking)


    // het alfabet van de RE is {0,1}
    vector<string> alfabet{"0", "1"};
    vector<string> bewerkingen{"unie", "concatenatie", "kleeneStar"};

    string RE;

    string R;
    string S;
    string U;
    string T;

    // R bepalen
    int symbool1 = rand() % 2;
    int randomBewerking = rand() % 3;
    string random;
    if (randomBewerking == 0) { // unie
        random = "(" + to_string(symbool1) + "+" + to_string(1-symbool1) + ")";
    }
    else if (randomBewerking == 1) { // concat
        random = "(" + to_string(symbool1) + to_string(1-symbool1) + ")"; // nog maken dat je kan kiezen tussen aa en ab/ba
    }
    else if (randomBewerking == 2) { // kleene
        random = "(" + to_string(symbool1) + ")*";
    }
    R = random;
    // S bepalen

    S = "0";
    // U bepalen

    U = "0";
    // T bepalen

    T = "0";

    // formule samenstellen
    string formule = "(" + R + " + " + S + U + "*" + T + ")" + "*" + S + U + "*"; // algemene vorm van formule

    // doorsnede checken => controlesysteem
    bool doorsnede = false;
    if (doorsnede) {
        return generateRE(numberOfIterations+1);
    }
    else {
        RE = formule;
    }

    return RE;
}
