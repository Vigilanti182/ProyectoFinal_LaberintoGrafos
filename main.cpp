#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

int main() {
    string s = "Laberinto.txt";

    cout << "----------MATRIZ de Adyacencia Vacia----------" << endl;
    Grafo g(s);
    g.muestraMatriz();
    cout << " " << endl;

    cout << "----------Lista de Nodos----------" << endl;
    g.generaListaNodos();
    g.muestraListaNodos();
    cout << " " << endl;

    cout << "----------Matriz de Adyacencia del Grafo----------" << endl;
    g.generaMatriz();
    cout << " " << endl;

    cout << "----------Busqueda en Anchura (BFS)----------" << endl;
    g.busquedaAnchura();
    cout << " " << endl;

    cout << "----------Busqueda en Profundidad (DFS)----------" << endl;
    g.busquedaProfundidad();



    return 0;
}