#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <ctime>  // Incluimos la biblioteca ctime

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
    clock_t start_bfs = clock();  // Start time for BFS
    g.busquedaAnchura();
    clock_t end_bfs = clock();  // End time for BFS
    double elapsed_bfs = double(end_bfs - start_bfs) / CLOCKS_PER_SEC * 1000;
    cout << "Tiempo de ejecución BFS: " << elapsed_bfs << " ms" << endl;
    cout << " " << endl;

    cout << "----------Busqueda en Profundidad (DFS)----------" << endl;
    clock_t start_dfs = clock();  // Start time for DFS
    g.busquedaProfundidad();
    clock_t end_dfs = clock();  // End time for DFS
    double elapsed_dfs = double(end_dfs - start_dfs) / CLOCKS_PER_SEC * 1000;
    cout << "Tiempo de ejecución DFS: " << elapsed_dfs << " ms" << endl;

    return 0;
}
