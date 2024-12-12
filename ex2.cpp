#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Structura pentru tranzitii
struct Transition {
    int from;            // Starea sursa
    string symbol;       // Simbolul tranzitiei (inclusiv epsilon)
    int to;              // Starea destinatie
};

// Structura pentru AFN
struct NFA {
    int startState;               // Starea initiala
    int finalState;               // Starea finala
    vector<Transition> transitions; // Lista tranzitiilor
};

// Functie pentru generarea unui fisier .dot pentru vizualizare grafica
void generateDotFile(const NFA& nfa, const string& filename) {
    ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        cerr << "Eroare la deschiderea fisierului: " << filename << endl;
        return;
    }

    dotFile << "digraph NFA {\n";
    dotFile << "  rankdir=LR;\n"; // Directia graficului: stanga-dreapta
    dotFile << "  node [shape = circle];\n";
    dotFile << "  " << nfa.startState << " [style=filled, color=green];\n"; // Starea initiala
    dotFile << "  " << nfa.finalState << " [shape=doublecircle];\n";      // Starea finala

    for (const auto& transition : nfa.transitions) {
        dotFile << "  " << transition.from << " -> " << transition.to 
                << " [label=\"" << transition.symbol << "\"];\n";

    }

    dotFile << "}\n";
    dotFile.close();
    cout << "Fisierul .dot a fost generat: " << filename << endl;
}

// Functie pentru crearea AFN-ului pentru expresia regulata `(a|b|c)*abbc`
NFA createAFNForRegex() {
    NFA nfa;
    int state = 0;

    // Definirea starilor
    nfa.startState = state++;
    int state1 = state++;
    int state2 = state++;
    int state3 = state++;
    int state4 = state++;
    int state5 = state++;
    int state6 = state++;
    int state7 = state++;
    int state8 = state++;
    int state9 = state++;
    int state10 = state++;
    int state11 = state++;
    int state12 = state++;
    nfa.finalState = state++;

    // Tranzitiile pentru `(a|b|c)*`
    nfa.transitions.push_back({nfa.startState, "ε", state1});   // 0 -> 1
    nfa.transitions.push_back({nfa.startState, "ε", state9});  // 0 -> 9
    nfa.transitions.push_back({state1, "ε", state2});          // 1 -> 2
    nfa.transitions.push_back({state1, "ε", state4});          // 1 -> 4
    nfa.transitions.push_back({state1, "ε", state6});          // 1 -> 6
    nfa.transitions.push_back({state2, "a", state3});          // 2 -> 3
    nfa.transitions.push_back({state4, "b", state5});          // 4 -> 5
    nfa.transitions.push_back({state6, "c", state7});          // 6 -> 7
    nfa.transitions.push_back({state3, "ε", state8});          // 3 -> 8
    nfa.transitions.push_back({state5, "ε", state8});          // 5 -> 8
    nfa.transitions.push_back({state7, "ε", state8});          // 7 -> 8
    nfa.transitions.push_back({state8, "ε", state1});          // 8 -> 1
    nfa.transitions.push_back({state8, "ε", state9});          // 8 -> 9
    

    // Tranzitiile pentru `abbc`
    nfa.transitions.push_back({state9, "a", state10});          // 9 -> 10
    nfa.transitions.push_back({state10, "b", state11});        // 10 -> 11
    nfa.transitions.push_back({state11, "b", state12});        // 11 -> 12
    nfa.transitions.push_back({state12, "c", nfa.finalState}); // 12 -> 13

    return nfa;
}

int main() {
    // Crearea AFN-ului pentru expresia regulata `(a|b|c)*abbc`
    NFA nfa = createAFNForRegex();

    // Generarea fisierului .dot
    string dotFilename = "regex_nfa_abbc.dot";
    generateDotFile(nfa, dotFilename);

    // Instructiuni pentru utilizator
    cout << "Pentru a genera imaginea graficului, executa comanda:\n";
    cout << "dot -Tpng regex_nfa_abbc.dot -o regex_nfa_abbc.png" << endl;

    return 0;
}
