#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <ctime> // Biblioteca para medir el tiempo

using namespace std;

int main() {
    string s = "Laberinto.txt";
    Grafo g(s);
    g.generaListaNodos();
    g.generaMatriz();
    cout << " " << endl;

    int opcion;
    do {
        cout << "===== MENU =====" << endl;
        cout << "1. Mostrar lista de nodos" << endl;
        cout << "2. Busqueda por anchura (BFS)" << endl;
        cout << "3. Busqueda por profundidad (DFS)" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << " " << endl;
                cout << "----------Lista de Nodos----------" << endl;
                cout << " " << endl;

                g.muestraListaNodos();
                break;
            }
            case 2: {
                cout << " " << endl;
                cout << "----------Busqueda en Anchura (BFS)----------" << endl;
                cout << " " << endl;
                g.muestraMatriz();

                // Inicia el cronómetro antes de comenzar la búsqueda en anchura (BFS)
                clock_t start_bfs = clock();
                g.busquedaAnchura();
                // Detiene el cronómetro después de que la búsqueda en anchura haya terminado
                clock_t end_bfs = clock();
                // Calcula el tiempo transcurrido en milisegundos
                double elapsed_bfs = double(end_bfs - start_bfs) / CLOCKS_PER_SEC * 1000;
                // Muestra el tiempo de ejecución
                cout << "Tiempo de ejecucion BFS: " << elapsed_bfs << " ms" << endl;
                break;
            }
            case 3: {
                cout << " " << endl;
                cout << "----------Busqueda en Profundidad (DFS)----------" << endl;
                cout << " " << endl;
                g.muestraMatriz();

                // Inicia el cronómetro antes de comenzar la búsqueda en profundidad (DFS)
                clock_t start_dfs = clock();
                g.busquedaProfundidad();
                // Detiene el cronómetro después de que la búsqueda en profundidad haya terminado
                clock_t end_dfs = clock();
                // Calcula el tiempo transcurrido en milisegundos
                double elapsed_dfs = double(end_dfs - start_dfs) / CLOCKS_PER_SEC * 1000;
                // Muestra el tiempo de ejecución
                cout << "Tiempo de ejecucion DFS: " << elapsed_dfs << " ms" << endl;
                break;
            }
            case 4: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default: {
                cout << "Opcion invalida. Por favor, ingrese una opcion valida." << endl;
            }
        }
        cout << endl;
    } while (opcion != 4);

    return 0;
}


