//
// Created by Maksim Karnaukh on 5/05/2021.
//

#include "Maksim.h"


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
        fIniFile << "center = " << "(0, " << i*0.5 << ", 0)" << endl;
        if (str[i] == '1') {
            fIniFile << "color = " << "(0, 0, 0)" << endl;
        }
        else {
            fIniFile << "color = " << "(1, 1, 1)" << endl;

        }
    }

    fIniFile.close();
}

string Maksim::generateRE() {

    string RE = "";

    return RE;
}
