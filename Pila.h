#ifndef PILA_H
#define PILA_H
#include "Nodo.h"
#include <string>

class Pila {
private:
    Nodo* tope;

public:
    Pila();
    void push(string s);
    string pop();
    string top();
    bool isEmpty();
};

#endif // PILA_H
