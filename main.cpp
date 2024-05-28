#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <ctime> // Incluimos esta biblioteca para cronometrar el tiempo de ejecución
using namespace std;

void mostrarMenu() {
    cout << "------ MENU ------" << endl;
    cout << "1. Mostrar Matriz de Adyacencia Vacia" << endl;
    cout << "2. Mostrar Lista de Nodos" << endl;
    cout << "3. Generar y Mostrar Matriz de Adyacencia del Grafo" << endl;
    cout << "4. Realizar Busqueda en Anchura (BFS)" << endl;
    cout << "5. Realizar Busqueda en Profundidad (DFS)" << endl;
    cout << "6. Salir" << endl;
    cout << "Elija una opcion: ";
}

int main() {
    string s = "Laberinto.txt";
    Grafo g(s);
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        switch (opcion) {
            case 1:

                cout << "----------MATRIZ de Adyacencia Vacia----------" << endl;
                g.muestraMatriz();
                cout << " " << endl;
                break;

            case 2:

                cout << "----------Lista de Nodos----------" << endl;
                g.generaListaNodos();
                g.muestraListaNodos();
                cout << " " << endl;

                break;
            case 3:

                cout << "----------Matriz de Adyacencia del Grafo----------" << endl;
                g.generaMatriz();
                g.muestraMatriz();
                cout << " " << endl;

                break;
            case 4: {

                cout << "----------Busqueda en Anchura (BFS)----------" << endl;
                g.generaMatriz(); // Se tiene que mandar llamar al metodo genera matriz antes para
                //para que la busqueda BFS se ejecute correctamente

                clock_t start_bfs = clock(); // Incializar tiempo para BFS
                g.busquedaAnchura();

                clock_t end_bfs = clock(); // Finalizar tiempo para BFS
                double elapsed_bfs = double(end_bfs - start_bfs) / CLOCKS_PER_SEC * 1000;
                cout << "Tiempo de ejecucion BFS: " << elapsed_bfs << " ms" << endl;
                cout << " " << endl;
                break;
            }
            case 5: {

                cout << "----------Busqueda en Profundidad (DFS)----------" << endl;
                g.generaMatriz();

                clock_t start_dfs = clock(); // inicializar tiempo para DFS
                g.busquedaProfundidad();

                clock_t end_dfs = clock(); // finalizar tiempo para DFS
                double elapsed_dfs = double(end_dfs - start_dfs) / CLOCKS_PER_SEC * 1000;
                cout << "Tiempo de ejecucion DFS: " << elapsed_dfs << " ms" << endl;
                cout << " " << endl;
                break;
            }
            case 6:

                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opcion no valida. Por favor, intente de nuevo." << endl;
        }
    } while (opcion != 6);
    return 0;
}
