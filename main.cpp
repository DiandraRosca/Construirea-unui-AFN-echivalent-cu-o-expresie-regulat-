#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Structură pentru tranziții
struct Transition {
    int from;            // Starea sursă
    string symbol;       // Simbolul tranziției (inclusiv epsilon)
    int to;              // Starea destinație
};

// Structură pentru AFN
struct NFA {
    int startState;               // Starea inițială
    int finalState;               // Starea finală
    vector<Transition> transitions; // Lista tranzițiilor
};

// Funcție pentru generarea unui fișier .dot pentru vizualizare grafică
void generateDotFile(const NFA& nfa, const string& filename) {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "Eroare la deschiderea fișierului: " << filename << endl;
        return;
    }

    dotFile << "digraph NFA {\n";
    dotFile << "  rankdir=LR;\n"; // Direcția graficului: stânga-dreapta
    dotFile << "  node [shape = circle];\n";
    dotFile << "  " << nfa.startState << " [style=filled, color=green];\n"; // Starea inițială
    dotFile << "  " << nfa.finalState << " [shape=doublecircle];\n";      // Starea finală

    for (const auto& transition : nfa.transitions) {
        dotFile << "  " << transition.from << " -> " << transition.to 
                << " [label=\"" << transition.symbol << "\"];\n";
    }

    dotFile << "}\n";
    dotFile.close();
    cout << "Fișierul .dot a fost generat: " << filename << endl;
}

// Funcție pentru crearea AFN-ului `(a|b)*abb` cu schema exactă și legătura adăugată
NFA createAFNForRegex() {
    NFA nfa;
    int state = 0;

    // Definirea stărilor
    nfa.startState = state++;  // Starea 0
    int state1 = state++;      // Starea 1
    int state2 = state++;      // Starea 2
    int state3 = state++;      // Starea 3
    int state4 = state++;      // Starea 4
    int state5 = state++;      // Starea 5
    int state6 = state++;      // Starea 6
    int state7 = state++;      // Starea 7
    int state8 = state++;      // Starea 8
    int state9 = state++;      // Starea 9
    nfa.finalState = state++;  // Starea 10

    // Tranzițiile pentru `(a|b)*`
    nfa.transitions.push_back({nfa.startState, "ε", state1});    // 0 -> 1
    nfa.transitions.push_back({nfa.startState, "ε", state7});    // 0 -> 7 (ADAUGAT)
    nfa.transitions.push_back({state1, "ε", state2});            // 1 -> 2
    nfa.transitions.push_back({state1, "ε", state4});            // 1 -> 4
    nfa.transitions.push_back({state2, "a", state3});            // 2 -> 3
    nfa.transitions.push_back({state4, "b", state5});            // 4 -> 5
    nfa.transitions.push_back({state3, "ε", state6});            // 3 -> 6
    nfa.transitions.push_back({state5, "ε", state6});            // 5 -> 6
    nfa.transitions.push_back({state6, "ε", state1});            // 6 -> 1
    nfa.transitions.push_back({state6, "ε", state7});            // 6 -> 7

    // Tranzițiile pentru `abb`
    nfa.transitions.push_back({state7, "a", state8});            // 7 -> 8
    nfa.transitions.push_back({state8, "b", state9});            // 8 -> 9
    nfa.transitions.push_back({state9, "b", nfa.finalState});    // 9 -> 10

    return nfa;
}

int main() {
    // Crearea AFN-ului pentru expresia regulată `(a|b)*abb`
    NFA nfa = createAFNForRegex();

    // Generarea fișierului .dot
    string dotFilename = "regex_nfa_updated.dot";
    generateDotFile(nfa, dotFilename);

    // Informații pentru utilizator
    cout << "Pentru a genera imaginea graficului, execută comanda:\n";
    cout << "dot -Tpng regex_nfa_updated.dot -o regex_nfa_updated.png" << endl;

    return 0;
}
