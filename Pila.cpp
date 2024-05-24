#include "Pila.h"
#include "Nodo.h"
#include <string>

using namespace std;

Pila::Pila() {
    tope = nullptr;
}

void Pila::push(string s) {
    Nodo* p = new Nodo(s);
    if (tope == nullptr)
        tope = p;
    else {
        p->setSig(tope);
        tope = p;
    }
}

string Pila::pop() {
    string s = "";
    Nodo* q = tope;
    if (q != nullptr) {
        s = q->getNom();
        tope = q->getSig();
        delete q;
    } else {
        s = "Pila Vacia";
    }
    return s;
}

string Pila::top() {
    string s = "";
    if (tope != nullptr) {
        s = tope->getNom();
    }
    return s;
}

bool Pila::isEmpty() {
    return tope == nullptr;
}
