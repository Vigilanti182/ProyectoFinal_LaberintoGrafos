#include "Grafo.h"
#include "Cola.h"
#include "Pila.h"
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

Grafo::Grafo(string nomArch) {
    string cad;
    arch.open(nomArch);
    if (arch.fail()) {
        cout << "Error al abrir el archivo" << endl;
        return;  // En lugar de exit(1), retornamos del constructor
    }
    getline(arch, cad);
    numNodos = stoi(cad);
    listaNodos = new Nodo[numNodos];
    matAdj = new int*[numNodos];
    for (int i = 0; i < numNodos; i++) {
        matAdj[i] = new int[numNodos];
        for (int j = 0; j < numNodos; j++) {
            matAdj[i][j] = 0;
        }
    }
}

Grafo::~Grafo() {
    for (int i = 0; i < numNodos; i++) {
        delete[] matAdj[i];
    }
    delete[] matAdj;
    delete[] listaNodos;
}

void Grafo::generaListaNodos() {
    string cad;
    for (int i = 0; i < numNodos; i++) {
        getline(arch, cad);
        listaNodos[i].setNom(cad);
    }
}

int Grafo::buscaNodo(string nombre) {
    for (int i = 0; i < numNodos; i++) {
        if (listaNodos[i].getNom() == nombre) {
            return i;
        }
    }
    return -1;
}

void Grafo::generaMatriz() {
    string cad;
    while (getline(arch, cad)) {
        if (cad.empty()) continue;
        int pos1 = cad.find('*');
        int pos2 = cad.find('*', pos1 + 1);
        string origen = cad.substr(0, pos1);
        string destino = cad.substr(pos1 + 1, pos2 - pos1 - 1);
        int peso = stoi(cad.substr(pos2 + 1));
        int posOrigen = buscaNodo(origen);
        int posDestino = buscaNodo(destino);
        if (posOrigen != -1 && posDestino != -1) {
            matAdj[posOrigen][posDestino] = peso;
            matAdj[posDestino][posOrigen] = peso; // Para grafo no dirigido
        }
    }
    muestraMatriz();
}

void Grafo::muestraListaNodos() {
    cout << "Lista de vertices del grafo" << endl;
    for (int i = 0; i < numNodos; i++) {
        cout << listaNodos[i].getNom() << endl;
    }
}

void Grafo::muestraMatriz() {
    cout << "Matriz de Adyacencia:" << endl;
    for (int i = 0; i < numNodos; i++) {
        for (int j = 0; j < numNodos; j++) {
            cout << matAdj[i][j] << "\t";
        }
        cout << endl;
    }
}

void Grafo::busquedaAnchura() {
    int inicio = 0;
    int fin = numNodos - 1;
    int* padre = new int[numNodos];

    // Inicializar todos los nodos como no visitados
    for (int i = 0; i < numNodos; ++i) {
        listaNodos[i].setVisitado(false);
        padre[i] = -1;
    }

    Cola cola;
    cola.enqueue(listaNodos[inicio].getNom());
    listaNodos[inicio].setVisitado(true); // Marcar el nodo inicial como visitado

    while (!cola.isEmpty()) {
        string nodoActual = cola.dequeue();
        int nodo = buscaNodo(nodoActual);

        if (nodo == fin) {
            cout << "Camino encontrado (Busqueda por Anchura): ";
            imprimirCamino(padre, inicio, fin);
            cout << endl;
            delete[] padre;
            return;
        }

        for (int i = 0; i < numNodos; ++i) {
            if (matAdj[nodo][i] != 0 && !listaNodos[i].getVisitado()) {
                cola.enqueue(listaNodos[i].getNom());
                listaNodos[i].setVisitado(true); // Marcar el nodo como visitado
                padre[i] = nodo;
            }
        }
    }

    cout << "No se encontró camino." << endl;
    delete[] padre;
}



void Grafo::busquedaProfundidad() {
    int inicio = 0;
    int fin = numNodos - 1;
    int* padre = new int[numNodos];

    // Inicializar todos los nodos como no visitados
    for (int i = 0; i < numNodos; ++i) {
        listaNodos[i].setVisitado(false);
        padre[i] = -1;
    }

    Pila pila;
    pila.push(listaNodos[inicio].getNom());
    listaNodos[inicio].setVisitado(true); // Marcar el nodo inicial como visitado

    while (!pila.isEmpty()) {
        string nodoActual = pila.pop();
        int nodo = buscaNodo(nodoActual);

        if (nodo == fin) {
            cout << "Camino encontrado (Busqueda por Profundidad): ";
            imprimirCamino(padre, inicio, fin);
            cout << endl;
            delete[] padre;
            return;
        }

        for (int i = 0; i < numNodos; ++i) {
            if (matAdj[nodo][i] != 0 && !listaNodos[i].getVisitado()) {
                pila.push(listaNodos[i].getNom());
                listaNodos[i].setVisitado(true); // Marcar el nodo como visitado
                padre[i] = nodo;
            }
        }
    }

    cout << "No se encontró camino." << endl;
    delete[] padre;
}


void Grafo::imprimirCamino(int* padre, int inicio, int fin) {
    if (fin == -1) {
        return;
    }

    imprimirCamino(padre, inicio, padre[fin]);
    cout << listaNodos[fin].getNom() << " ";
}