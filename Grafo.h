#ifndef GRAFO_H
#define GRAFO_H
#include "Nodo.h"
#include <fstream>

class Grafo {
    int **matAdj;
    Nodo *listaNodos;
    int numNodos;
    fstream arch;

public:
    Grafo(string nomArch);
    ~Grafo();
    void generaMatriz();
    void generaListaNodos();
    void muestraListaNodos();
    void muestraMatriz();
    int buscaNodo(string nombre);

    void busquedaAnchura();//Algoritmo para busqueda por anchura
    void busquedaProfundidad();//Algoritmo para busqueda por profunidad
    void imprimirCamino(int* padre, int inicio, int fin);

};

#endif // GRAFO_H