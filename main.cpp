#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <ctime>

using namespace std;

int main() {
    string s = "Laberinto.txt";
    Grafo g(s);
    int opcion;

    do {
        cout << "Menú:" << endl;
        cout << "1. Mostrar matriz de adyacencia vacía" << endl;
        cout << "2. Generar y mostrar lista de nodos" << endl;
        cout << "3. Generar matriz de adyacencia del grafo" << endl;
        cout << "4. Realizar búsqueda en anchura (BFS)" << endl;
        cout << "5. Realizar búsqueda en profundidad (DFS)" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "----------MATRIZ de Adyacencia Vacia----------" << endl;
                g.muestraMatriz();
                cout << endl;
                break;
            case 2:
                cout << "----------Lista de Nodos----------" << endl;
                g.generaListaNodos();
                g.muestraListaNodos();
                cout << endl;
                break;
            case 3:
                cout << "----------Matriz de Adyacencia del Grafo----------" << endl;
                g.generaMatriz();
                cout << endl;
                break;
            case 4:
                cout << "----------Busqueda en Anchura (BFS)----------" << endl;
                clock_t start_bfs = clock();
                g.busquedaAnchura();
                clock_t end_bfs = clock();
                double elapsed_bfs = double(end_bfs - start_bfs) / CLOCKS_PER_SEC * 1000;
                cout << "Tiempo de ejecución BFS: " << elapsed_bfs << " ms" << endl;
                cout << endl;
                break;
            case 5:
                cout << "----------Busqueda en Profundidad (DFS)----------" << endl;
                clock_t start_dfs = clock();
                g.busquedaProfundidad();
                clock_t end_dfs = clock();
                double elapsed_dfs = double(end_dfs - start_dfs) / CLOCKS_PER_SEC * 1000;
                cout << "Tiempo de ejecución DFS: " << elapsed_dfs << " ms" << endl;
                cout << endl;
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
                cout << endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}
