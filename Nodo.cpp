#include "Nodo.h"

// Constructor por defecto
Nodo::Nodo() {
    nom = "";
    sig = nullptr;  // Inicializamos el puntero a nullptr
}

// Constructor con parámetro
Nodo::Nodo(string nom) {
    this->nom = nom;
    this->sig = nullptr;  // Inicializamos el puntero a nullptr
}

// Método para obtener el nombre
string Nodo::getNom() {
    return nom;
}

// Método para establecer el nombre
void Nodo::setNom(string s) {
    nom = s;
}

// Getter para el puntero sig
Nodo* Nodo::getSig() {
    return sig;
}

// Setter para el puntero sig
void Nodo::setSig(Nodo* s) {
    sig = s;
}

bool Nodo::getVisitado() {
    return visitado;
}

// Setter para el atributo 'visitado'
void Nodo::setVisitado(bool v) {
    visitado = v;
}