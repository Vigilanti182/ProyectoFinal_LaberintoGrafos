#include "Cola.h"
#include "Nodo.h"
#include <string>

Cola::Cola() {
    primero = ultimo = nullptr;
}

Cola::~Cola() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Cola::enqueue(string s) {
    Nodo* nuevoNodo = new Nodo(s);
    if (ultimo == nullptr) {
        primero = ultimo = nuevoNodo;
    } else {
        ultimo->setSig(nuevoNodo);
        ultimo = nuevoNodo;
    }
}

string Cola::dequeue() {
    if (primero == nullptr) {
        return "";
    }
    string valor = primero->getNom();
    Nodo* temp = primero;
    primero = primero->getSig();
    if (primero == nullptr) {
        ultimo = nullptr;
    }
    delete temp;
    return valor;
}

string Cola::first() {
    if (primero == nullptr) {
        return "";
    }
    return primero->getNom(); // Ahora el compilador conoce la clase Nodo
}

bool Cola::isEmpty() {
    return primero == nullptr;
}

