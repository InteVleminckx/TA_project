#include <iostream>
#include "DFA.h"

int main() {
    DFA dfa("input-tfa4.json");
//    dfa.print();
    DFA mindfa = dfa.minimize();
//    dfa.printTable();
    mindfa.print();
//    cout << boolalpha << (dfa == mindfa) << endl;    // zijn ze equivalent? Zou hier zeker moeten. Dit wordt getest in de volgende vraag, maar hiermee kan je al eens proberen
    return 0;
}

//int main() {
//    DFA dfa1("input-tfa3.json");
//    DFA dfa2("input-tfa4.json");
//    cout << boolalpha << (dfa1 == dfa2) << endl;    // zijn ze equivalent? Zou hier zeker moeten. Dit wordt getest in de volgende vraag, maar hiermee kan je al eens proberen
//    return 0;
//}