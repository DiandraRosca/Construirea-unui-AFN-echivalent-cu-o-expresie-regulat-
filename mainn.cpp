#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Structura pentru tranzitii
struct Transition {
    int from;              // Starea sursă (de unde pleacă tranziția)
    string symbol;         // Simbolul tranziției (poate fi un caracter sau "ε" pentru epsilon)
    int to;                // Starea destinație (unde ajunge tranziția)
};

// Structura pentru AFN
struct NFA {
    int startState;
    int finalState;
    vector<Transition> transitions;                      // Lista tuturor tranzițiilor din automat
};

// Functie pentru generarea unui fisier .dot utilizabil cu Grapviz pentru vizualizare grafica
void generateDotFile(const NFA& nfa, const string& filename) {
    ofstream dotFile(filename);                            //deschidem fisierul de iesire unde se va scrie reprez graf
    if (!dotFile.is_open()) {                              //verificam dc s-a deschis corect
        cerr << "Eroare la deschiderea fisierului: " << filename << endl;
        return;
    }
   
    dotFile << "digraph NFA {\n";                            // Declarația de început pentru un graf direcționat
    dotFile << "  rankdir=LR;\n";                            // Specificăm direcția graficului: de la stânga la dreapta
    //stiluri pentru noduri(st in, fin, tranzactii)
    dotFile << "  node [shape = circle];\n";
    dotFile << "  " << nfa.startState << " [style=filled, color=green];\n";
    dotFile << "  " << nfa.finalState << " [shape=doublecircle];\n";

    // Iterăm prin fiecare tranziție din lista de tranziții a automatului
    for (const auto& transition : nfa.transitions) {
        // Adăugăm fiecare tranziție în graf în formatul "stare_sursă -> stare_destinație [label=symbol]"
        dotFile << "  " << transition.from << " -> " << transition.to
                << " [label=\"" << transition.symbol << "\"];\n";
    }

    dotFile << "}\n";    //inchidem graficul
    dotFile.close();     //inchidem fisierul
    cout << "Fisierul .dot a fost generat: " << filename << endl;
}

// Functie pentru expresia `abb`
NFA createAFNForAbb() {
    NFA nfa;
    int state = 0;

    nfa.startState = state++;
    int state1 = state++;
    int state2 = state++;
    nfa.finalState = state++;

    nfa.transitions.push_back({nfa.startState, "a", state1});
    nfa.transitions.push_back({state1, "b", state2});
    nfa.transitions.push_back({state2, "b", nfa.finalState});

    return nfa;
}

// Functie pentru expresia `a*b+`
NFA createAFNForAStarBPlus() {
    NFA nfa;
    int state = 0;

    nfa.startState = state++;
    int loopA = nfa.startState;
    int stateB = state++;
    int loopB = state++;
    nfa.finalState = state++;

    nfa.transitions.push_back({loopA, "a", loopA});
    nfa.transitions.push_back({loopA, "b", stateB});
    nfa.transitions.push_back({stateB, "b", loopB});
    nfa.transitions.push_back({loopB, "b", nfa.finalState});
   

    return nfa;
}

// Funcție pentru crearea AFN-ului `(a|b)*abb` cu schema exactă și legătura adăugată
NFA createAFNForAorBbb(){
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


// Functie pentru expresia `(a|b|c)*abbc`
NFA createAFNForABCStarABBC(){
    NFA nfa;                          // Creăm o structură AFN care va conține stările și tranzițiile
    int state = 0;                    // Inițializăm un contor pentru a atribui ID-uri unice fiecărei stări

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
    int state9 = state++;             // Starea de început a secvenței `abbc`
    int state10 = state++;
    int state11 = state++;
    int state12 = state++;
    nfa.finalState = state++;

    // Tranzitiile pentru `(a|b|c)*`
    // Creăm un ciclu care permite repetarea simbolurilor `a`, `b`, sau `c`
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
    nfa.transitions.push_back({state9, "a", state10});         // Tranziție pe `a`: 9 -> 10
    nfa.transitions.push_back({state10, "b", state11});        // 10 -> 11
    nfa.transitions.push_back({state11, "b", state12});        // 11 -> 12
    nfa.transitions.push_back({state12, "c", nfa.finalState}); // 12 -> 13

    return nfa;

}

//Functie pentru expresia a?(b|c)*d+
NFA createAFNForAQuestionBorCStarDPlus(){
    NFA nfa;
    int state = 0;

     // Definirea stărilor
    nfa.startState = state++;
    int stateA = state++;
    int stateB = state++;
    int stateC = state++;
    int stateD = state++;
    int stateLoop = state++;
    int stateFinal = state++;

    nfa.finalState = stateFinal;

    // Tranzițiile pentru `a?`
    nfa.transitions.push_back({nfa.startState, "ε", stateA});  // 0 -> 1 (epsilon)
    nfa.transitions.push_back({nfa.startState, "ε", stateB});  // 0 -> 2 (epsilon)
    nfa.transitions.push_back({stateA, "a", stateB});          // 1 -> 2

    // Tranzițiile pentru `(b|c)*`
    nfa.transitions.push_back({stateB, "ε", stateC});          // 2 -> 3 (epsilon)
    nfa.transitions.push_back({stateC, "b", stateC});          // 3 -> 3 (b loop)
    nfa.transitions.push_back({stateC, "c", stateC});          // 3 -> 3 (c loop)
    nfa.transitions.push_back({stateC, "ε", stateD});          // 3 -> 4 (epsilon)

    // Tranzițiile pentru `d+`
    nfa.transitions.push_back({stateD, "d", stateLoop});       // 4 -> 5 (d transition)
    nfa.transitions.push_back({stateLoop, "d", stateLoop});    // 5 -> 5 (d loop)
    nfa.transitions.push_back({stateLoop, "ε", stateFinal});   // 5 -> 6 (epsilon)

    return nfa;
}

// Functie pentru expresia `a(b|c)*d`
NFA createAFNForABorCStarD() {
    NFA nfa;
    int state = 0;

    nfa.startState = state++;
    int stateA = state++;
    int stateLoopStart = state++;
    int stateB = state++;
    int stateC = state++;
    int stateLoopEnd = state++;
    int stateD = state++;
    nfa.finalState = state++;

    nfa.transitions.push_back({nfa.startState, "a", stateA});
    nfa.transitions.push_back({stateA, "ε", stateLoopStart});
    nfa.transitions.push_back({stateLoopStart, "b", stateB});
    nfa.transitions.push_back({stateLoopStart, "c", stateC});
    nfa.transitions.push_back({stateB, "ε", stateLoopEnd});
    nfa.transitions.push_back({stateC, "ε", stateLoopEnd});
    nfa.transitions.push_back({stateLoopEnd, "ε", stateLoopStart});
    nfa.transitions.push_back({stateLoopEnd, "d", stateD});
    nfa.transitions.push_back({stateD, "ε", nfa.finalState});

    return nfa;
}


int main() {
    // Generare pentru `abb`
    NFA nfaAbb = createAFNForAbb();
    generateDotFile(nfaAbb, "regex_abb.dot");
    cout << "Pentru a genera imaginea graficului pentru `abb`, executa comanda:\n";
    cout << "dot -Tpng regex_abb.dot -o regex_abb.png\n\n";

    // Generare pentru `a*b+`
    NFA nfaAStarBPlus = createAFNForAStarBPlus();
    generateDotFile(nfaAStarBPlus, "regex_aStarbPlus.dot");
    cout << "Pentru a genera imaginea graficului pentru `a*b+`, executa comanda:\n";
    cout << "dot -Tpng regex_aStarbPlus.dot -o regex_aStarbPlus.png\n\n";

    // // Crearea AFN-ului pentru expresia regulată `(a|b)*abb`
    NFA nfaAorBStarABB = createAFNForAorBbb();
    generateDotFile(nfaAorBStarABB, "regex_aOrBStarABB.dot");
    cout << "Pentru a genera imaginea graficului pentru `(a|b)*abb`, executa comanda:\n";
    cout << "dot -Tpng regex_aOrBStarABB.dot -o regex_aOrBStarABB.png\n\n";

    // Generare pentru `(a|b|c)*abbc`
    // Crearea AFN-ului pentru expresia regulata `(a|b|c)*abbc`
    NFA nfaABCStarABBC = createAFNForABCStarABBC();                                   // Apelăm funcția pentru a genera AFN-ul
    generateDotFile(nfaABCStarABBC, "regex_abcStarABBC.dot");                         // Generăm fișierul .dot pentru vizualizare
    cout << "Pentru a genera imaginea graficului pentru `(a|b|c)*abbc`, executa comanda:\n";
    cout << "dot -Tpng regex_abcStarABBC.dot -o regex_abcStarABBC.png\n\n";
    
    //generare pentru expresia a?(b|c)*d+
    NFA nfaAQuestionBorCStarDPlus = createAFNForAQuestionBorCStarDPlus();
    generateDotFile(nfaAQuestionBorCStarDPlus, "regex_aQuestionBorCStarDPlus.dot");
    cout << "Pentru a genera imaginea graficului pentru `a?(b|c)*d+`, executa comanda:\n";
    cout << "dot -Tpng regex_aQuestionBorCStarDPlus.dot -o regex_aQuestionBorCStarDPlus.png\n\n";

    // Generare pentru `a(b|c)*d`
    NFA nfaABorCStarD = createAFNForABorCStarD();
    generateDotFile(nfaABorCStarD, "regex_abcd.dot");
    cout << "Pentru a genera imaginea graficului pentru `a(b|c)*d`, executa comanda:\n";
    cout << "dot -Tpng regex_abcd.dot -o regex_abcd.png\n\n";

    
    

    return 0;
}
